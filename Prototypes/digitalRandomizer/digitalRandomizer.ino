int randomPin = 13;
uint32_t d = 250;
int odds = 64;

void setup() {
  pinMode(randomPin, OUTPUT);
}

void loop() {
  digitalWrite(randomPin, random(256) < odds ? HIGH : LOW);
  delay(d);
}
