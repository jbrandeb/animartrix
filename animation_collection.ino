
void Rotating_Blob() {

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.003;    // speed ratios for the oscillators
  timings.ratio[0] = 0.1;          // higher values = faster transitions
  timings.ratio[1] = 0.03;
  timings.ratio[2] = 0.03;
  timings.ratio[3] = 0.03;
  
  
  timings.offset[1] = 10;
  timings.offset[2] = 20;
  timings.offset[3] = 30;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      animation.angle      = polar_theta[x][y] +  move.radial[0];
      animation.dist       = distance[x][y];
      animation.z          = move.linear[0];
      animation.low_limit  = -1;
      float show1          = render_value(animation);
      
      animation.angle      = polar_theta[x][y] - move.radial[1] + show1/512.0;
      animation.dist       = distance[x][y] * show1/255.0;
      animation.low_limit  = 0;
      animation.z          = move.linear[1];
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] - move.radial[2] + show1/512.0;
      animation.dist       = distance[x][y] * show1/220.0;
      animation.z          = move.linear[2];
      float show3          = render_value(animation);

      animation.angle      = polar_theta[x][y] - move.radial[3] + show1/512.0;
      animation.dist       = distance[x][y] * show1/200.0;
      animation.z          = move.linear[3];
      float show4          = render_value(animation);

      // colormapping
      pixel.red   = (show2+show4)/4;
      pixel.green = show3 / 6;
      pixel.blue  = (show2+show4)/2;

      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }

}




void Chasing_Spirals() {

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.01;    // speed ratios for the oscillators
  timings.ratio[0] = 0.1;         // higher values = faster transitions
  timings.ratio[1] = 0.13;
  timings.ratio[2] = 0.16;
  
  timings.offset[1] = 10;
  timings.offset[2] = 20;
  timings.offset[3] = 30;
  
  calculate_oscillators_slow(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.angle      = 3 * polar_theta[x][y] +  move.radial[0] - distance[x][y]/3;
      animation.dist       = distance[x][y];
      animation.scale_z    = 0.01;  
      animation.scale_y    = 0.01;
      animation.scale_x    = 0.01;
      animation.offset_x   = move.linear[0];
      animation.offset_y   = 0;
      animation.offset_z   = 0;
      animation.z          = 0;
      float show1          = render_value(animation);

      animation.angle      = 3 * polar_theta[x][y] +  move.radial[1] - distance[x][y]/3;
      animation.dist       = distance[x][y];
      animation.offset_x   = move.linear[1];
      float show2          = render_value(animation);

      animation.angle      = 3 * polar_theta[x][y] +  move.radial[2] - distance[x][y]/3;
      animation.dist       = distance[x][y];
      animation.offset_x   = move.linear[2];
      float show3          = render_value(animation);

      // colormapping
      float radius = 200;
      float radial_filter = (radius - distance[x][y]) / radius;

      pixel.red   = 3*show1 * radial_filter;
      pixel.green = show2 * radial_filter / 2;
      pixel.blue  = show3 * radial_filter / 4;

      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }

}


void Rings() {

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.01;    // speed ratios for the oscillators
  timings.ratio[0] = 1;         // higher values = faster transitions
  timings.ratio[1] = 1.1;
  timings.ratio[2] = 1.2;
  
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  
  calculate_oscillators_slow(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.angle      = 5;
      animation.scale_x    = 0.2;
      animation.scale_y    = 0.2;
      animation.scale_z    = 1;
      animation.dist       = distance[x][y];
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      float show1          = render_value(animation);

       // describe and render animation layers
      animation.angle      = 10;
      
      animation.dist       = distance[x][y];
      animation.offset_y   = -move.linear[1];
      float show2          = render_value(animation);

       // describe and render animation layers
      animation.angle      = 12;
      
      animation.dist       = distance[x][y];
      animation.offset_y   = -move.linear[2];
      float show3          = render_value(animation);

      // colormapping
      pixel.red   = show1 * 1.2;
      pixel.green = (show2 / 4) * 1.2;
      pixel.blue  = (show3 / 4) * 1.2;

      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }

}

void Waves() {

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.01;    // speed ratios for the oscillators
  timings.ratio[0] = 2;         // higher values = faster transitions
  timings.ratio[1] = 2.1;
  timings.ratio[2] = 1.2;
  
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  
  calculate_oscillators_slow(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.angle      = polar_theta[x][y];
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.scale_z    = 0.1;
      animation.dist       = distance[x][y];
      animation.offset_y   = 0;
      animation.offset_x   = 0;
      animation.z          = 2*distance[x][y] - move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y];
      animation.dist       = distance[x][y];
      animation.z          = 2*distance[x][y] - move.linear[1];
      float show2          = render_value(animation);

  
      // colormapping
      pixel.red   = show1;
      pixel.green = 0;
      pixel.blue  = show2;

      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }

}

void Center_Field() {
  
  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.01;    // speed ratios for the oscillators
  timings.ratio[0] = 1;         // higher values = faster transitions
  timings.ratio[1] = 1.1;
  timings.ratio[2] = 1.2;
  
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  calculate_oscillators_slow(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.angle      = polar_theta[x][y];
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.scale_z    = 0.1;
      animation.dist       = 5*sqrtf(distance[x][y]);
      animation.offset_y   = move.linear[0];
      animation.offset_x   = 0;
      animation.z          = 0;
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y];
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.scale_z    = 0.1;
      animation.dist       = 4*sqrtf(distance[x][y]);
      animation.offset_y   = move.linear[0];
      animation.offset_x   = 0;
      animation.z          = 0;
      float show2          = render_value(animation);

     

  
      // colormapping
      pixel.red   = show1;
      pixel.green = show2;
      pixel.blue  = 0;

      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }

}

void Distance_Experiment() {

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.001;    // speed ratios for the oscillators
  timings.ratio[0] = 0.2;         // higher values = faster transitions
  timings.ratio[1] = 0.13;
  timings.ratio[2] = 0.012;
  
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.dist       = powf(distance[x][y], 0.8);
      animation.angle      = polar_theta[x][y] + move.radial[0];
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.scale_z    = 0.1;
      animation.offset_y   = move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = 0;
      float show1          = render_value(animation);

      animation.dist       = powf(distance[x][y], 0.6);
      animation.angle      = polar_theta[x][y] + move.noise_angle[2];
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.scale_z    = 0.1;
      animation.offset_y   = move.linear[1];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = 0;
      float show2          = render_value(animation);
      
      // colormapping
      pixel.red   = show1+show2;
      pixel.green = show2;
      pixel.blue  = 0;

      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }

}


void Caleido1() {

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.0004;    // speed ratios for the oscillators
  timings.ratio[0] = 0.02;         // higher values = faster transitions
  timings.ratio[1] = 0.03;
  timings.ratio[2] = 0.04;
  timings.ratio[3] = 0.05;
  timings.ratio[4] = 0.6;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.dist       = distance[x][y] * (2 + move.directional[0]) / 3;
      animation.angle      = 3 * polar_theta[x][y] + 3 * move.noise_angle[0] + move.radial[4];
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.scale_z    = 0.1;
      animation.offset_y   = 2 * move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = move.linear[0];
      float show1          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[1]) / 3;
      animation.angle      = 4 * polar_theta[x][y] + 3 * move.noise_angle[1] + move.radial[4];
      animation.offset_x   = 2 * move.linear[1];
      animation.z          = move.linear[1];
      float show2          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[2]) / 3;
      animation.angle      = 5 * polar_theta[x][y] + 3 * move.noise_angle[2] + move.radial[4];
      animation.offset_y   = 2 * move.linear[2];
      animation.z          = move.linear[2];
      float show3          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[3]) / 3;
      animation.angle      = 4 * polar_theta[x][y] + 3 * move.noise_angle[3] + move.radial[4];
      animation.offset_x   = 2 * move.linear[3];
      animation.z          = move.linear[3];
      float show4          = render_value(animation);
      
      // colormapping
      //pixel.red   = show1;
      pixel.red   = show3 * distance[x][y] / 10;
      pixel.green = show3 * distance[x][y] / 10;
      pixel.blue  = (show2 + show4) / 2;

      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }

}

void Caleido2() {

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.0002;    // speed ratios for the oscillators
  timings.ratio[0] = 0.02;         // higher values = faster transitions
  timings.ratio[1] = 0.03;
  timings.ratio[2] = 0.04;
  timings.ratio[3] = 0.05;
  timings.ratio[4] = 0.6;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  
  calculate_oscillators_slow(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.dist       = distance[x][y] * (2 + move.directional[0]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[0] + move.radial[4];
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.scale_z    = 0.1;
      animation.offset_y   = 2 * move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = move.linear[0];
      float show1          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[1]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[1] + move.radial[4];
      animation.offset_x   = 2 * move.linear[1];
      animation.z          = move.linear[1];
      float show2          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[2]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[2] + move.radial[4];
      animation.offset_y   = 2 * move.linear[2];
      animation.z          = move.linear[2];
      float show3          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[3]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[3] + move.radial[4];
      animation.offset_x   = 2 * move.linear[3];
      animation.z          = move.linear[3];
      float show4          = render_value(animation);
      
      // colormapping
      pixel.red   = show1;
      //pixel.green = show3 * distance[x][y] / 10;
      pixel.green = 0;
      pixel.blue  = (show2 + show4) / 2;

      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}

void Caleido3() {

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.0003;    // speed ratios for the oscillators
  timings.ratio[0] = 0.02;         // higher values = faster transitions
  timings.ratio[1] = 0.03;
  timings.ratio[2] = 0.04;
  timings.ratio[3] = 0.05;
  timings.ratio[4] = 0.6;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  
  calculate_oscillators_slow(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.dist       = distance[x][y] * (2 + move.directional[0]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[0] + move.radial[4];
      animation.scale_x    = 0.1;// + (move.directional[0] + 2)/100;
      animation.scale_y    = 0.1;// + (move.directional[1] + 2)/100;
      animation.scale_z    = 0.1;
      animation.offset_y   = 2 * move.linear[0];
      animation.offset_x   = 2 * move.linear[1];
      animation.offset_z   = 0;
      animation.z          = move.linear[0];
      float show1          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[1]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[1] + move.radial[4];
      animation.offset_x   = 2 * move.linear[1];
      animation.offset_y   = show1 / 20.0;
      animation.z          = move.linear[1];
      float show2          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[2]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[2] + move.radial[4];
      animation.offset_y   = 2 * move.linear[2];
      animation.offset_x   = show2 / 20.0;
      animation.z          = move.linear[2];
      float show3          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[3]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[3] + move.radial[4];
      animation.offset_x   = 2 * move.linear[3];
      animation.offset_y   = show3 / 20.0;
      animation.z          = move.linear[3];
      float show4          = render_value(animation);
      
      // colormapping
      float radius = 64;  // radial mask

      pixel.red   = show1 * (y+1) / num_y;
      pixel.green = show3 * distance[x][y] / 20;
      pixel.blue  = (show2 + show4) / 2;
      if (distance[x][y] > radius) {
        pixel.red = 0;
        pixel.green = 0;
        pixel.blue = 0;
      }

      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}

void Lava1() {

get_ready();
rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.0015;    // speed ratios for the oscillators
  timings.ratio[0] = 4;         // higher values = faster transitions
  timings.ratio[1] = 1;
  timings.ratio[2] = 1;
  timings.ratio[3] = 0.05;
  timings.ratio[4] = 0.6;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.dist       = distance[x][y] * 0.8;
      animation.angle      = polar_theta[x][y];
      animation.scale_x    = 0.15;// + (move.directional[0] + 2)/100;
      animation.scale_y    = 0.12;// + (move.directional[1] + 2)/100;
      animation.scale_z    = 0.01;
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = 30;
      float show1          = render_value(animation);

      animation.offset_y   = -move.linear[1];
      animation.scale_x    = 0.15;// + (move.directional[0] + 2)/100;
      animation.scale_y    = 0.12;// + (move.directional[1] + 2)/100;
      animation.offset_x   = show1 / 100;
      animation.offset_y   += show1/100;
     
      float show2          = render_value(animation);

      animation.offset_y   = -move.linear[2];
      animation.scale_x    = 0.15;// + (move.directional[0] + 2)/100;
      animation.scale_y    = 0.12;// + (move.directional[1] + 2)/100;
      animation.offset_x   = show2 / 100;
      animation.offset_y   += show2/100;
     
      float show3         = render_value(animation);

      // colormapping
      float linear = 1; //(y)/(num_y-1.f);  // radial mask

      pixel.red = linear*show2;
      //pixel.green = 0.1*linear*(show2-show3);
      pixel.green = 0;
      pixel.blue = 0;
      
      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }

}

void Scaledemo1() {

get_ready();
rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.00003;    // speed ratios for the oscillators
  timings.ratio[0] = 4;         // higher values = faster transitions
  timings.ratio[1] = 3.2;
  timings.ratio[2] = 10;
  timings.ratio[3] = 0.05;
  timings.ratio[4] = 0.6;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.dist       = 0.3*distance[x][y] * 0.8;
      animation.angle      = 3*polar_theta[x][y] + move.radial[2];
      animation.scale_x    = 0.1 + (move.noise_angle[0])/10;
      animation.scale_y    = 0.1 + (move.noise_angle[1])/10;// + (move.directional[1] + 2)/100;
      animation.scale_z    = 0.01;
      animation.offset_y   = 0;
      animation.offset_x   = 0;
      animation.offset_z   = 100*move.linear[0];
      animation.z          = 30;
      float show1          = render_value(animation);

      animation.angle      = 3;
      float show2          = render_value(animation);

      float dist = (10-distance[x][y])/ 10;
      pixel.red = show1*dist;
      pixel.green = (show1-show2)*dist*0.3;
      pixel.blue = (show2-show1)*dist;

      if (distance[x][y] > 8) {
         pixel.red = 0;
         pixel.green = 0;
         pixel.blue = 0;

      }
      
      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }

}


void Yves() {

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.001;    // speed ratios for the oscillators
  timings.ratio[0] = 3;         // higher values = faster transitions
  timings.ratio[1] = 2;
  timings.ratio[2] = 1;
  timings.ratio[3] = 0.13;
  timings.ratio[4] = 0.15;
  timings.ratio[5] = 0.03;
  timings.ratio[6] = 0.025;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  timings.offset[5] = 500;
  timings.offset[6] = 600;
  
  calculate_oscillators_orig(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] ;
      animation.angle      = polar_theta[x][y] + 2*PI + move.noise_angle[5];
      animation.scale_x    = 0.08;
      animation.scale_y    = 0.08;
      animation.scale_z    = 0.08;
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = 0;
      float show1          = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + 2*PI + move.noise_angle[6];;
      animation.scale_x    = 0.08;
      animation.scale_y    = 0.08;
      animation.scale_z    = 0.08;
      animation.offset_y   = -move.linear[1];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = 0;
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + show1/100 + move.noise_angle[3] + move.noise_angle[4];
      animation.dist       = distance[x][y] + show2/50;
      animation.offset_y   = -move.linear[2];

      animation.offset_y   += show1/100;
      animation.offset_x   += show2/100;

      float show3          = render_value(animation);

      animation.offset_y   = 0;
      animation.offset_x   = 0;

      float show4          = render_value(animation);
      
     
      pixel.green   = show3 * 1.4;
      pixel.red     = show3 * map(proximityb * 8, 100, 12000, 0.4, 6.0);
      //pixel.red = show3*show4/255;
      pixel.blue  = show4/3 * 1.5 * map(proximity * 10, 100, 12000, 0.8, 6.0);;
      
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}

void Spiralus() {

  get_ready();
rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.0011;    // speed ratios for the oscillators
  timings.ratio[0] = 1.5;         // higher values = faster transitions
  timings.ratio[1] = 2.3;
  timings.ratio[2] = 3;
  timings.ratio[3] = 0.05;
  timings.ratio[4] = 0.2;
  timings.ratio[5] = 0.03;
  timings.ratio[6] = 0.025;
  timings.ratio[7] = 0.021;
  timings.ratio[8] = 0.027;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  timings.offset[5] = 500;
  timings.offset[6] = 600;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] ;
      animation.angle      = 2*polar_theta[x][y] + move.noise_angle[5] + move.directional[3] * move.noise_angle[6]* animation.dist/10;
      animation.scale_x    = 0.08;
      animation.scale_y    = 0.08;
      animation.scale_z    = 0.02;
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = move.linear[1];
      float show1          = render_value(animation);

      animation.angle      = 2*polar_theta[x][y] + move.noise_angle[7] + move.directional[5] * move.noise_angle[8]* animation.dist/10;
      animation.offset_y   = -move.linear[1];
      animation.z          = move.linear[2];
            
      float show2          = render_value(animation);

      animation.angle      = 2*polar_theta[x][y] + move.noise_angle[6] + move.directional[6] * move.noise_angle[7]* animation.dist/10;
      animation.offset_y   = move.linear[2];
      animation.z          = move.linear[0];
      float show3          = render_value(animation);
      
      
      float f =  (20-distance[x][y])/20;
     
      pixel.red   = f*(show1+show2);
      pixel.green = f*(show1-show2);
      pixel.blue  = f*(show3-show1);
      
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}

void Spiralus2() {

  get_ready();
rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.0011;    // speed ratios for the oscillators
  timings.ratio[0] = 1.5;         // higher values = faster transitions
  timings.ratio[1] = 2.3;
  timings.ratio[2] = 3;
  timings.ratio[3] = 0.05;
  timings.ratio[4] = 0.2;
  timings.ratio[5] = 0.03;
  timings.ratio[6] = 0.025;
  timings.ratio[7] = 0.021;
  timings.ratio[8] = 0.027;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  timings.offset[5] = 500;
  timings.offset[6] = 600;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] ;
      animation.angle      = 2*polar_theta[x][y] + move.noise_angle[5] + move.directional[3] * move.noise_angle[6]* animation.dist/10;
      animation.scale_x    = 0.08;
      animation.scale_y    = 0.08;
      animation.scale_z    = 0.02;
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = move.linear[1];
      float show1          = render_value(animation);

      animation.angle      = 3*polar_theta[x][y] + move.noise_angle[7] + move.directional[5] * move.noise_angle[8]* animation.dist/10;
      animation.offset_y   = -move.linear[1];
      animation.z          = move.linear[2];
            
      float show2          = render_value(animation);

      animation.angle      = 4*polar_theta[x][y] + move.noise_angle[6] + move.directional[6] * move.noise_angle[7]* animation.dist/10;
      animation.offset_y   = move.linear[2];
      animation.z          = move.linear[0];
      animation.dist       = distance[x][y] *0.8;
      float show3          = render_value(animation);
      
      
      float f =  (20-distance[x][y])/20;
     
      pixel.red   = f*(show1+show2);
      pixel.green = f*(show1-show2);
      pixel.blue  = f*(show3-show1);
      
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}


void Hot_Blob() { // nice one

  get_ready(); 
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  run_default_oscillators();

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] ;
      animation.angle      = polar_theta[x][y];
      
      animation.scale_x    = 0.07 + move.directional[0]*0.002;
      animation.scale_y    = 0.07;
      
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      
      animation.z          = 0;
      animation.low_limit  = -1;
      float show1          = render_value(animation);

      animation.offset_y   = -move.linear[1];
      float show3          = render_value(animation);

      animation.offset_x   = show3/20;
      animation.offset_y   = -move.linear[0]/2 + show1/70;
      animation.low_limit  = 0;
      float show2          = render_value(animation);

      animation.offset_x   = show3/20;
      animation.offset_y   = -move.linear[0]/2 + show1/70;
      animation.z          = 100;
      float show4          = render_value(animation);

      float radius = 66;   // radius of a radial brightness filter
      float radial = (radius-animation.dist)/animation.dist;

      float linear = (y+1)/(num_y-1.f);
      
      pixel.red   = radial  * show2;
      pixel.green   = linear * radial* 0.3* (show2-show4);
      pixel.blue = 0;
      
      
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}

void Zoom() { // nice one

  get_ready();
rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  run_default_oscillators();
  timings.master_speed = 0.003;
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] * distance[x][y];
      animation.angle      = polar_theta[x][y];
      
      animation.scale_x    = 0.01;
      animation.scale_y    = 0.01;
      
      animation.offset_y   = -10*move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      
      animation.z          = 0;
      animation.low_limit  = 0;
      float show1          = render_value(animation);

    
      /*
      animation.offset_x   = 0;
      animation.offset_y   = -move.linear[0]/2;
      animation.low_limit  = 0;
      float show2          = render_value(animation);

     

      float radius = 11;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];
      */
      float linear = (y+1)/(num_y-1.f);
      
      pixel.red   = show1*linear;
      pixel.green   = 0;
      pixel.blue    = 0;
            
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}




void Slow_Fade() { // nice one

  get_ready();
rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  run_default_oscillators();
  timings.master_speed = 0.00005;
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = sqrtf(distance[x][y]) * 0.7 * (move.directional[0] + 1.5);
      animation.angle      = polar_theta[x][y] - move.radial[0] + distance[x][y] / 5;
      
      animation.scale_x    = 0.11;
      animation.scale_y    = 0.11;
      
      animation.offset_y   = -50 * move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      
      animation.z          = move.linear[0];
      animation.low_limit  = -0.1;
      animation.high_limit = 1;
      float show1          = render_value(animation);

      animation.dist       = animation.dist  * 1.1;
      animation.angle      += move.noise_angle[0] / 10;
      float show2          = render_value(animation);

      animation.dist       = animation.dist  * 1.1;
      animation.angle      += move.noise_angle[1] / 10;
      
      float show3          = render_value(animation);

      float radius = 99;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];


    
      
      pixel.red    = radial * show1;
      pixel.green  = radial * (show1 - show2) / 6;
      pixel.blue   = radial * (show1 - show3) / 5;
      
      
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}

void Polar_Waves() { // nice one

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.5;    // master speed

  timings.ratio[0] = 0.0005;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] - animation.dist * 0.25 + move.radial[0];
      animation.z          = (animation.dist * 1.5)-10 * move.linear[0];
      animation.scale_x    = 0.15;
      animation.scale_y    = 0.15;
      animation.offset_x   = move.linear[0];
      
      float show1          = render_value(animation);
      animation.angle      = polar_theta[x][y] - animation.dist * 0.25 + move.radial[1];
      animation.z          = (animation.dist * 1.5)-10 * move.linear[1];
      animation.offset_x   = move.linear[1];

      float show2          = render_value(animation);
      animation.angle      = polar_theta[x][y] - animation.dist * 0.25 + move.radial[2];
      animation.z          = (animation.dist * 1.5)-10 * move.linear[2];
      animation.offset_x   = move.linear[2];

      float show3          = render_value(animation);

      float radius = 150;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      #define INTENSITY 0.75
      pixel.red    = radial * (show1 - show3) * INTENSITY;
      pixel.blue  = radial * (show2) * INTENSITY;
      //pixel.blue   = radial * show3 * 0.2;
      pixel.green = 0;
            

      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}

void RGB_Blobs() { // nice one

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.2;    // master speed

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + move.radial[0] + move.noise_angle[0]+ move.noise_angle[3];
      animation.z          = (sqrtf(animation.dist));// - 10 * move.linear[0];
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.offset_z   = 10;
      animation.offset_x   = 10*move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[1]+ move.noise_angle[1]+ move.noise_angle[4];
      animation.offset_x   = 11*move.linear[1];
      animation.offset_z   = 100;
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[2]+ move.noise_angle[2]+ move.noise_angle[5];
      animation.offset_x   = 12*move.linear[2];
      animation.offset_z   = 300;
      float show3          = render_value(animation);
      

      float radius = 11;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * show1;
      pixel.green  = radial * show2;
      pixel.blue   = radial * show3;
     
      
      
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}


void RGB_Blobs2() { // nice one

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.02;    // master speed

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + move.radial[0] + move.noise_angle[0]+ move.noise_angle[3] + move.noise_angle[1];
      animation.z          = (sqrtf(animation.dist));// - 10 * move.linear[0];
      animation.scale_x    = 0.01; // we like x 0.1
      animation.scale_y    = 0.2; // we like y 0.5
      animation.offset_z   = 10;
      animation.offset_x   = 10*move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[1]+ move.noise_angle[1]+ move.noise_angle[4] + move.noise_angle[2];
      animation.offset_x   = 11*move.linear[1];
      animation.offset_z   = 100;
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[2]+ move.noise_angle[2]+ move.noise_angle[5]+ move.noise_angle[3];
      animation.offset_x   = 12*move.linear[2];
      animation.offset_z   = 300;
      float show3          = render_value(animation);
      
      float radius = 1;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      //pixel.red    = radial * (show1);  // was blank when removed
      //pixel.red    = radial * (show1-show3);
      pixel.green    = radial * (show1-show3) * 1.4;
      pixel.red     = radial * (show1-show3) * 1.4;
      pixel.blue = 0;
      //pixel.green  = radial * (show2-show1);
      //pixel.blue   = radial * (show3-show2);
     
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}

void RGB_Blobs2a() { // nice one - supposed to be sparkles

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.02;    // master speed

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + move.radial[0] + move.noise_angle[0]+ move.noise_angle[3] + move.noise_angle[1];
      animation.z          = (sqrtf(animation.dist));// - 10 * move.linear[0];
      animation.scale_x    = 0.1; // we like x 0.1
      animation.scale_y    = 0.5; // we like y 0.5
      animation.offset_z   = 10;
      animation.offset_x   = 10*move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[1]+ move.noise_angle[1]+ move.noise_angle[4] + move.noise_angle[2];
      animation.offset_x   = 11*move.linear[1];
      animation.offset_z   = 100;
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[2]+ move.noise_angle[2]+ move.noise_angle[5]+ move.noise_angle[3];
      animation.offset_x   = 12*move.linear[2];
      animation.offset_z   = 300;
      float show3          = render_value(animation);
      
      float radius = 1;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      //pixel.red    = radial * (show1);  // was blank when removed
      pixel.red    = radial * (show1-show3);
      pixel.green = 0;
      //pixel.green  = radial * (show2-show1);
      //pixel.blue   = radial * (show3-show2);
      //pixel.blue   = radial * (show1-show3); // got purble
      pixel.blue   = radial * (-show1);
     
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}

void RGB_Blobs3() { // nice one

  get_ready();
rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.12;    // master speed

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] + move.noise_angle[4];
      animation.angle      = polar_theta[x][y] + move.radial[0] + move.noise_angle[0]+ move.noise_angle[3] + move.noise_angle[1];
      animation.z          = (sqrtf(animation.dist));// - 10 * move.linear[0];
      animation.scale_x    = 0.001 ;
      animation.scale_y    = 0.001 ;
      animation.offset_z   = 10;
      animation.offset_x   = 10*move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[1]+ move.noise_angle[1]+ move.noise_angle[4] + move.noise_angle[2];
      animation.offset_x   = 11*move.linear[1];
      animation.offset_z   = 100;
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[2]+ move.noise_angle[2]+ move.noise_angle[5]+ move.noise_angle[3];
      animation.offset_x   = 12*move.linear[2];
      animation.offset_z   = 300;
      float show3          = render_value(animation);
      
      float radius = 66;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * (show1+show3)*0.5 * animation.dist/5;
      pixel.green  = radial * (show2+show1)*0.5 * y/15;
      pixel.blue   = radial * (show3+show2)*0.5 * x/15;
     
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}

void RGB_Blobs4(int inSpeed) { // nice one

  get_ready();
  rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()
  float adjusted_speed = map((float)inSpeed, 1, 4096, 0.02, 0.100);
  //timings.master_speed = 0.02;    // master speed

  timings.master_speed = adjusted_speed;    // master speed


  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] + move.noise_angle[4];
      animation.angle      = polar_theta[x][y] + move.radial[0] + move.noise_angle[0]+ move.noise_angle[3] + move.noise_angle[1];
      animation.z          = 3+sqrtf(animation.dist);
      animation.scale_x    = 0.001;
      animation.scale_y    = 0.001;
      animation.offset_z   = 10;
      animation.offset_x   = 50 * move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[1]+ move.noise_angle[1]+ move.noise_angle[4] + move.noise_angle[2];
      animation.offset_x   = 50 * move.linear[1];
      animation.offset_z   = 100;
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[2]+ move.noise_angle[2]+ move.noise_angle[5]+ move.noise_angle[3];
      animation.offset_x   = 50 * move.linear[2];
      animation.offset_z   = 300;
      float show3          = render_value(animation);
      
      float radius = 88;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * (show1+show3)*0.5 * animation.dist/5;
      pixel.green  = radial * (show2+show1)*0.5 * y/15;
      pixel.blue   = radial * (show3+show2)*0.5 * x/15;
     
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}

void RGB_Blobs5() { // nice one

  get_ready();
rgb24 *buffer = backgroundLayer.backBuffer();                  // for time measurement in report_performance()

  timings.master_speed = 0.02;    // master speed

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] + move.noise_angle[4];
      animation.angle      = polar_theta[x][y] + move.radial[0] + move.noise_angle[0]+ move.noise_angle[3] + move.noise_angle[1];
      animation.z          = 3+sqrtf(animation.dist);
      animation.scale_x    = 0.08;
      animation.scale_y    = 0.08;
      animation.offset_z   = 10;
      animation.offset_x   = 50 * move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[1]+ move.noise_angle[1]+ move.noise_angle[4] + move.noise_angle[2];
      animation.offset_x   = 50 * move.linear[1];
      animation.offset_z   = 100;
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[2]+ move.noise_angle[2]+ move.noise_angle[5]+ move.noise_angle[3];
      animation.offset_x   = 50 * move.linear[2];
      animation.offset_z   = 300;
      float show3          = render_value(animation);
      
      float radius = 66;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * (show1+show3)*0.5 * animation.dist/5;
      pixel.green  = radial * (show2+show1)*0.5 * y/15;
      pixel.blue   = radial * (show3+show2)*0.5 * x/15;
     
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
}

float mapValue(int input) {
  // Ensure the input value is within the expected range
  if (input < 0) input = 1;
  if (input > 255) input = 255;

  // Map the input value to the output range
  float output = ((float)input / 255.0) * 0.665;
  return output;
}
const float changeRate = 0.02;

float perma_w = 0.01;

float colordodge(float &a, float&b) {  

  return (a/(255.f-b)) * 255.f;
}

void Module_Experiment10() { 
  //float thisSpeed;

  //thisSpeed = (float)inSpeed / 10000;
  //thisSpeed = max(thisSpeed, 0.01);
  float prox = proximity;
  float proxb = proximityb;

  get_ready();

  rgb24 *buffer = backgroundLayer.backBuffer();

  timings.master_speed = 0.01;    // master speed 0.031

  //Serial.print("thisSpeed: ");
  //Serial.println(thisSpeed);
  //timings.master_speed = thisSpeed;    // master speed 0.031

  //  float w = 1;
  long inputValue = map(prox, 1, 200, 1, 255); // map the value to 0-255

  float target = mapValue(inputValue);
  target = constrain(target, 0.30, 0.90);
  perma_w += (target - perma_w) * changeRate;
  float w = 0.031;
  //Serial.print("in: ");
  //Serial.print(inSpeed);
  //Serial.print(" perma_w: ");
  //Serial.println(perma_w);
  //float w = 3 ;

  timings.ratio[0] = 0.01;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.011;
  timings.ratio[2] = 0.013;
  timings.ratio[3] = 0.33*w;
  timings.ratio[4] = 0.36*w;            // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[5] = 0.38*w; 
  timings.ratio[6] = 0.0003;  // master rotation

  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  timings.offset[5] = 500;
  timings.offset[6] = 600;
  

  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      //float s = 0.4; // scale
      float s = perma_w; // scale
      float r = constrain(mapValue(proxb), 0.15, 0.90); // scroll speed
      //float r = perma_w;

      animation.dist       = 3+distance[x][y] + 3*sinf(0.25*distance[x][y]-move.radial[3]);
      animation.angle      = polar_theta[x][y] + move.noise_angle[0] + move.noise_angle[6];
      animation.z          = 5;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 10*move.linear[0] ;
      animation.offset_y   = -5 * r * move.linear[0];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      animation.dist       = 4+distance[x][y] + 4*sinf(0.24*distance[x][y]-move.radial[4]);
      animation.angle      = polar_theta[x][y] + move.noise_angle[1] + move.noise_angle[6];
      animation.z          = 5;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 0.1*move.linear[1] ;
      animation.offset_y   = -5 * r * move.linear[1];
      animation.offset_x   = 100;
      animation.low_limit  = 0;
      show2                = render_value(animation);

      animation.dist       = 5+distance[x][y] + 5*sinf(0.23*distance[x][y]-move.radial[5]);
      animation.angle      = polar_theta[x][y] + move.noise_angle[2] + move.noise_angle[6];
      animation.z          = 5;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 0.1*move.linear[2] ;
      animation.offset_y   = -5 * r * move.linear[2];
      animation.offset_x   = 1000;
      animation.low_limit  = 0;
      show3                = render_value(animation);

      show4 = colordodge(show1, show2);

      //float rad = sinf(PI/2+distance[x][y]/14); // better radial filter?!

      //byte a = elapsedMillis()/100;
      byte b = elapsedMillis() % 5000;
      
      // JJJ see if we can limit color pallette
      pixel.red    = (show1 + show2) * 0.2;
      pixel.blue   = (show1 + show2 - (show4 * 0.1)) * 0.2;
      pixel.green  = show3 - show1 * (0.3 * (b));
      //pixel.blue   = (show2-show1) * 0.5;
      
      //CHSV(rad * ((show1 + show2) + show3), 255, 255);
      
      pixel = rgb_sanity_check(pixel);
      
      //buffer[xy(x, y)] = (rgb24)CRGB(CHSV(((a + show1 + show2) + show3 + 225), 200, 200));
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
      /*
      // cool green and purple run
 
      byte a = elapsedMillis()/100;
      byte b = elapsedMillis() % 1000;
      
      // JJJ see if we can limit color pallette
      pixel.red    = (show1 + show2) * 0.2;
      pixel.blue   = (show1 + show2 - (show4 * 0.2)) * 0.2;
      pixel.green  = show3 - show1 * 0.3;
      //pixel.blue   = (show2-show1) * 0.5;
      
      //CHSV(rad * ((show1 + show2) + show3), 255, 255);
      
      pixel = rgb_sanity_check(pixel);

      
      //buffer[xy(x, y)] = (rgb24)CRGB(CHSV(((a + show1 + show2) + show3 + 225), 200, 200));
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.
      */ 
    }
  }
}

void Lava2() {

  get_ready(); 
  rgb24 *buffer = backgroundLayer.backBuffer();                   // for time measurement in report_performance()

  timings.master_speed = 0.0015;    // speed ratios for the oscillators
  timings.ratio[0] = 4;         // higher values = faster transitions
  timings.ratio[1] = 1;
  timings.ratio[2] = 1;
  timings.ratio[3] = 0.05;
  timings.ratio[4] = 0.6;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.dist       = distance[x][y] * 0.8;
      animation.angle      = polar_theta[x][y];
      animation.scale_x    = 0.15;// + (move.directional[0] + 2)/100;
      animation.scale_y    = 0.12;// + (move.directional[1] + 2)/100;
      animation.scale_z    = 0.01;
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = 30;
      float show1          = render_value(animation);

      animation.offset_y   = -move.linear[1];
      animation.scale_x    = 0.15;// + (move.directional[0] + 2)/100;
      animation.scale_y    = 0.12;// + (move.directional[1] + 2)/100;
      animation.offset_x   = show1 / 100;
      animation.offset_y   += show1/100;
     
      float show2          = render_value(animation);

      animation.offset_y   = -move.linear[2];
      animation.scale_x    = 0.15;// + (move.directional[0] + 2)/100;
      animation.scale_y    = 0.12;// + (move.directional[1] + 2)/100;
      animation.offset_x   = show2 / 100;
      animation.offset_y   += show2/100;
     
      float show3         = render_value(animation);

      // colormapping
      float linear = (y)/(num_y-1.f);  // radial mask

      pixel.red = linear*show2;
      pixel.green = 0.1*linear*(show2-show3);
      pixel.blue = 0;
      
      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));

    }
  }
 
}
