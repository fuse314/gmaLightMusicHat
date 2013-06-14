void InitEQ7() {
  pinMode(EQ7IN_PIN, INPUT);
  pinMode(EQ7STROBE_PIN, OUTPUT);
  pinMode(EQ7RESET_PIN, OUTPUT);
  analogReference(DEFAULT);
  digitalWrite(EQ7RESET_PIN, LOW);
  digitalWrite(EQ7STROBE_PIN, HIGH);
}

void GetEQ7() {
  digitalWrite(EQ7RESET_PIN, HIGH);
  digitalWrite(EQ7RESET_PIN, LOW);
  
  for (uint8_t i = 0; i < 7; i++)
  {
    digitalWrite(EQ7STROBE_PIN, LOW);
    delayMicroseconds(30); // to allow analog signal to settle
    eq7Values[i] = analogRead(EQ7IN_PIN); 
    digitalWrite(EQ7STROBE_PIN, HIGH);
  }
  
  digitalWrite(EQ7RESET_PIN, LOW);
  digitalWrite(EQ7STROBE_PIN, HIGH);
  
  
  uint16_t spectrumValue = max(eq7Values[6], eq7Values[5]);   // high tones = blue
  if(spectrumValue <= NOISE_LVL) {
    currEQColor.b = 0;
  } else {
    currEQColor.b = map(spectrumValue, NOISE_LVL, 1024, 1, 255);
  }
  spectrumValue = max(eq7Values[4], eq7Values[3]);    // mid tones = green
  if(spectrumValue <= NOISE_LVL) {
    currEQColor.g = 0;
  } else {
    currEQColor.g = map(spectrumValue, NOISE_LVL, 1024, 1, 255);
  }
  spectrumValue = max(eq7Values[2], eq7Values[1], eq7Values[0]);   // low tones = red
  if(spectrumValue <= NOISE_LVL) {
    currEQColor.r = 0;
  } else {
    currEQColor.r = map(spectrumValue, NOISE_LVL, 1024, 1, 255);
  }
}
