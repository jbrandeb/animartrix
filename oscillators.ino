
void calculate_oscillators(oscillators &timings) {

  float prox_scaled, proxb_scaled;

  float prox = min(proximity, 350.0);
  float proxb = min(proximityb, 350.0);
  prox = max(30, prox);
  proxb = max(30, proxb);
  prox_scaled =  map((float)prox,  1, 350, 1.0, 1.3);
  proxb_scaled = map((float)proxb, 1, 350, 1.0, 1.3);

  double runtime = millis() * (prox_scaled * proxb_scaled) * timings.master_speed;  // global anaimation speed

  for (int i = 0; i < num_oscillators; i++) {
    
    move.linear[i]      = (runtime + timings.offset[i]) * timings.ratio[i];     // continously rising offsets, returns              0 to max_float
    
    move.radial[i]      = fmodf(move.linear[i], 2 * PI);                        // angle offsets for continous rotation, returns    0 to 2 * PI
    
    move.directional[i] = sinf(move.radial[i]);                                 // directional offsets or factors, returns         -1 to 1
    
    move.noise_angle[i] = PI * (1 + pnoise(move.linear[i], 0, 0));              // noise based angle offset, returns                0 to 2 * PI
    
  }
}


