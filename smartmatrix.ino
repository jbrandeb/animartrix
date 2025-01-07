void get_ready() {  // wait until new buffer is ready, measure time

  a = micros(); 
  while(backgroundLayer.isSwapPending());
  b = micros(); 
}

void show_frame(){  // swap buffers, measure time, output current performance

  backgroundLayer.swapBuffers(false);  
  c = micros();                               // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report 
}
