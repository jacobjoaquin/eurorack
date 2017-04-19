int timerPin = A2;
int randomPin = 13;
uint32_t d = 5;
int odds = 128;

void setup() {
  pinMode(randomPin, OUTPUT);
}

void loop() {
  d = analogRead(timerPin) / 4;
  digitalWrite(randomPin, random(256) < odds ? HIGH : LOW);
  delay(d);
}
