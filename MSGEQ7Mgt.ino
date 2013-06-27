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
  
  eq7Volumes[0] = max(eq7Values[0], max(eq7Values[1], eq7Values[2]));
  eq7Volumes[1] = max(eq7Values[3], eq7Values[4]);
  eq7Volumes[2] = max(eq7Values[5], max(eq7Values[6], eq7Values[7]));
}

struct CRGB getEQColor() {
  struct CRGB ret;
  if(eq7Volumes[2] <= NOISE_LVL) {   // low tones are green
    ret.g = 0;
  } else {
    ret.g = map(eq7Volumes[2], NOISE_LVL, MAX_LVL, 1, 255);
  }
  if(eq7Volumes[1] <= NOISE_LVL) {   // mid tones are red
    ret.r = 0;
  } else {
    ret.r = map(eq7Volumes[1], NOISE_LVL, MAX_LVL, 1, 255);
  }
  if(eq7Volumes[0] <= NOISE_LVL) {   // high tones are blue
    ret.b = 0;
  } else {
    ret.b = map(eq7Volumes[0], NOISE_LVL, MAX_LVL, 1, 255);
  }
  return ret;
}
