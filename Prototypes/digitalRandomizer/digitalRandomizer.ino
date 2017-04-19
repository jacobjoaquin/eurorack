int timerPin = A2;
int randomPin = 13;
uint32_t d = 5;
int odds = 128;

uint32_t lastTriggerTime = 0;

void setup() {
  pinMode(randomPin, OUTPUT);
}

void loop() {
  // d = analogRead(timerPin) / 4;

  uint32_t now = millis();
  if (now >= lastTriggerTime + analogRead(timerPin)) {
    digitalWrite(randomPin, random(256) < odds ? HIGH : LOW);
    lastTriggerTime = now;
  }
}
