/*
  ___        _            ___  ______ _____    _      
 / _ \      (_)          / _ \ | ___ \_   _|  (_)     
/ /_\ \_ __  _ _ __ ___ / /_\ \| |_/ / | |_ __ ___  __
|  _  | '_ \| | '_ ` _ \|  _  ||    /  | | '__| \ \/ /
| | | | | | | | | | | | | | | || |\ \  | | |  | |>  < 
\_| |_/_| |_|_|_| |_| |_\_| |_/\_| \_| \_/_|  |_/_/\_\

by Stefan Petrick 2023.

High quality LED animations for your next project.

This is a Shader and 5D Coordinate Mapper made for realtime 
rendering of generative animations & artistic dynamic visuals.

This is also a modular animation synthesizer with waveform 
generators, oscillators, filters, modulators, noise generators, 
compressors... and much more.

VO.42 beta version
 
This code is licenced under a Creative Commons Attribution 
License CC BY-NC 3.0

*/

#include <MatrixHardware_Teensy4_ShieldV5.h> // Include the hardware configuration for SmartLED Shield (V5)
#include <SmartMatrix.h>
#include <FastLED.h>
// Proximity Sensor setup
#include <Adafruit_VCNL4200.h>
#include <Wire.h>
//#include <Twowire.h>

#define num_x  64                       // how many LEDs are in one row?
#define num_y  128                      // how many rows?
#define brightness 255                 // please be aware that reducing brightness also reduces color resolution, use only in emergency

#define COLOR_DEPTH 24                  // Choose the color depth used for storing pixels in the layers: 24 or 48 (24 is good for most sketches - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24)
const uint16_t kMatrixWidth   = num_x;  // Set to the width of your display, must be a multiple of 8
const uint16_t kMatrixHeight  = num_y;  // Set to the height of your display
const uint8_t  kRefreshDepth  = 30;     // Tradeoff of color quality vs refresh rate, max brightness, and RAM usage.  36 is typically good, drop down to 24 if you need to.  On Teensy, multiples of 3, up to 48: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48.  On ESP32: 24, 36, 48
const uint8_t  kDmaBufferRows = 8;      // known working: 2-4, use 2 to save RAM, more to keep from dropping frames and automatically lowering refresh rate.  (This isn't used on ESP32, leave as default)
const uint8_t  kPanelType              = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;   // Choose the configuration that matches your panels.  See more details in MatrixCommonHub75.h and the docs: https://github.com/pixelmatix/SmartMatrix/wiki
const uint32_t kMatrixOptions          = (SM_HUB75_OPTIONS_NONE);        // see docs for options: https://github.com/pixelmatix/SmartMatrix/wiki
const uint8_t  kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

#define NUM_LEDS num_x * num_y

float polar_theta[num_x][num_y];        // look-up table for polar angles
float distance[num_x][num_y];           // look-up table for polar distances

unsigned long a, b, c;                  // for time measurements

struct render_parameters {

  float center_x = (num_x / 2) - 0.5;   // center of the matrix
  float center_y = (num_y / 2) - 0.5;
  float dist, angle;                
  float scale_x = 0.01;                  // smaller values = zoom in
  float scale_y = 0.01;
  float scale_z = 0.01;       
  float offset_x, offset_y, offset_z;     
  float z;  
  float low_limit  = 0;                 // getting contrast by highering the black point
  float high_limit = 1;                                            
};

render_parameters animation;     // all animation parameters in one place

#define num_oscillators 10

struct oscillators {

  float master_speed;            // global transition speed
  float offset[num_oscillators]; // oscillators can be shifted by a time offset
  float ratio[num_oscillators];  // speed ratios for the individual oscillators                                  
};

oscillators timings;             // all speed settings in one place

struct modulators {  

  float linear[num_oscillators];        // returns 0 to FLT_MAX
  float radial[num_oscillators];        // returns 0 to 2*PI
  float directional[num_oscillators];   // returns -1 to 1
  float noise_angle[num_oscillators];   // returns 0 to 2*PI        
};

modulators move;                 // all oscillator based movers and shifters at one place

struct rgb {

  float red, green, blue;
};

float show1, show2, show3, show4, show5, show6, show7, show8, show9, show0;

rgb pixel;

Adafruit_VCNL4200 vcnl4200;
Adafruit_VCNL4200 vcnl4200b;


//******************************************************************************************************************


void setup() {
  
  // FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LEDS);
  
  //FastLED.addLeds<APA102, 11, 13, BGR, DATA_RATE_MHZ(12)>(leds, NUM_LEDS);   

  //FastLED.setMaxPowerInVoltsAndMilliamps( 5, 2000); // optional current limiting [5V, 2000mA] 

  Serial.begin(115200);                 // check serial monitor for current fps count

  // set up the onboard LED
  pinMode(13, OUTPUT);

  // Button setup
  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);

  // Initialize I2C communication
  Wire.begin();

  // Initialize the second sensor (it defaults to) pins 16 and 17
  Wire1.begin();

  if (!vcnl4200.begin()) {
    Serial.println("Could not find a valid VCNL4200 sensor, check wiring!");
    while (1) {
      // flash the LED to show failure (slow flash for sensor A)
      digitalToggle(13);
      delay(500);
    }
  }
  Serial.println("VCNL4200 found!");
  
  // second i2c bus
  if (!vcnl4200b.begin(VCNL4200_I2CADDR_DEFAULT, &Wire1)) {
    Serial.println("Could not find a valid VCNL4200 sensor, check wiring!");
    while (1) {
      // flash the LED to show failure (fast flash for sensor B)
      digitalToggle(13);
      delay(200);
    }
  }
  Serial.println("VCNL4200B found!");


  vcnl4200.setALSshutdown(true);
  vcnl4200.setProxShutdown(false);
  vcnl4200.setProxHD(false);
  vcnl4200.setProxLEDCurrent(VCNL4200_LED_I_200MA);
  vcnl4200.setProxIntegrationTime(VCNL4200_PS_IT_8T);

  vcnl4200b.setALSshutdown(true);
  vcnl4200b.setProxShutdown(false);
  vcnl4200b.setProxHD(false);
  vcnl4200b.setProxLEDCurrent(VCNL4200_LED_I_200MA);
  vcnl4200b.setProxIntegrationTime(VCNL4200_PS_IT_8T);

 
  render_polar_lookup_table((num_x / 2) - 0.5, (num_y / 2) - 0.5);          // precalculate all polar coordinates 
                                                                            // polar origin is set to matrix centre
  matrix.addLayer(&backgroundLayer);
  matrix.setBrightness(brightness);
  matrix.begin();
}

//*******************************************************************************************************************

// Global variables (these stick around)
int buttonState27 = LOW;
int buttonState28 = LOW;
int displayProgramNum = 0;  // start the display at this offset in the switch statement
elapsedMillis timeElapsed;
uint8_t cur_brightness = brightness;

// Use this function when using a temporary button
int handleTempButton(int button)
{
  if (button != buttonState27) {
      
    buttonState27 = button;
    Serial.print("button pin 27 pressed: ");
    Serial.println(button);
    
    // This means I'm holding it down
    if (button == LOW)
      return 0;
    
    return 1;
  }

  return 0;
}

// Use this button when the button sticks a state (like the guitar buttons)
int handleClickButton(int button, int *buttonState)
{
  if (button != *buttonState) {
    // save the button state
    *buttonState = button;
    Serial.print("button click pressed: ");
    Serial.println(button);

    return 1;
  }

  return 0;
}

float proximity = 0, proximityb = 0;
// define an array of functions to call
static void (*animationFunctions[])() = {
  //Spiralus2,
  //Polar_Waves,
  //RGB_Blobs5,
  Module_Experiment10, // 0
  RGB_Blobs2a,
  RGB_Blobs2,
  Slow_Fade,
  Hot_Blob,
  Spiralus, // 5
  Yves,
  Lava1,
  Caleido3,
  Caleido2,
  Caleido1, // 10
  Distance_Experiment,
  Center_Field,
  Waves,
  Chasing_Spirals,
  Rotating_Blob, // 15
  Rings
};

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

void fadeOutScreen(int steps, int delayTime) {
  get_ready();

  for (int step = 0; step < steps; step++) {
    rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

    for (int y = 0; y < kMatrixHeight; y++) {
      for (int x = 0; x < kMatrixWidth; x++) {
        int index = y * kMatrixWidth + x;
        buffer[index].red = buffer[index].red * (steps - step) / steps;
        buffer[index].green = buffer[index].green * (steps - step) / steps;
        buffer[index].blue = buffer[index].blue * (steps - step) / steps;
      }
    }
    show_frame();
    delay(delayTime);
  }
}

void incDisplayProgramNum() {
  if (++displayProgramNum > ARRAY_SIZE(animationFunctions) - 1) {
    displayProgramNum = 0;
  }
}

void loop() {

  int curButtonState = digitalRead(27);
  int cur28 = digitalRead(28);
  char incomingData = '0';
  bool switchedProg = false;


  if (Serial.available() > 0) { // Check if there's any data available to read
    incomingData = Serial.read(); // Read the incoming byte
    Serial.print("Received: "); // Print received message
    Serial.println(incomingData); // Print the received byte
  }

  /// NOTE NOTE NOTE - this cycles the programs every ten seconds, comment out to stop
  //EVERY_N_MILLIS(10000) incomingData = '\n';

  if ((incomingData != '0') ||
      // Jesse's buttons are Temporary High/steady Low
      //(handleTempButton(curButtonState))) {
      (handleClickButton(curButtonState, &buttonState27)) ||
      (handleClickButton(cur28, &buttonState28))) {
  //if (handleTempButton(curButtonState)) {
  // Comment out above and uncomment below for guitar button
  // if (handleClickButton(curButtonState)) {

    // loop over all the programs, if the number included below, in the switch,
    // changes then update this number
    incDisplayProgramNum();
    Serial.print("ProgNum: ");
    Serial.println(displayProgramNum, DEC);

    // since we are switching programs, fade the screen to black
    fadeOutScreen(50, 10);

    // reset the program parameters struct so they don't influence each other
    animation = render_parameters();
    timings = oscillators();
    move = modulators();
    // note we switched so we can fade in later
    switchedProg = true;
  }

  //static float smoothingFactor = 0.02; // 02 seemed like too slow to respond

  static float smoothingFactor = 0.04; // Adjust this value between 0.0 and 1.0
                                       // for the desired smoothing effect (0.1
                                       // is an example value)

  // proximity read
  //proximity = vcnl4200.readProxData();
  proximity = (smoothingFactor *  ((float)vcnl4200.readProxData())) + ((1 - smoothingFactor) * proximity);
  //Serial.print("Prox Data: ");
  //Serial.println(proximity);

 // proximity read
  //proximityb = vcnl4200b.readProxData();

  // Apply the low-pass filter formula
  proximityb = (smoothingFactor * ((float)vcnl4200b.readProxData())) + ((1 - smoothingFactor) * proximityb);

//Serial.print("Prox Data B: ");
  //Serial.println(proximityb);
 
  // call the function indicated by the displayProgramNum variable
  animationFunctions[displayProgramNum]();

  // implement fade in logic if we're switching, using brightness
  if (switchedProg)
    cur_brightness = 0;

  matrix.setBrightness(cur_brightness);

  // call the matrix specific draw function
  show_frame();

  // increase brightness to max each loop the program runs after switching
  if (cur_brightness != brightness)
    cur_brightness++;
} 

