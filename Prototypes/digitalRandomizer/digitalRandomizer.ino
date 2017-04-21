int timerPin = A0;
int oddsPin = A1;
int randomPin = 13;

int odds = 512;
uint32_t lastTriggerTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(randomPin, OUTPUT);
}

void loop() {
  uint32_t now = millis();

  if (now >= lastTriggerTime + analogRead(timerPin)) {
    odds = analogRead(oddsPin);
    Serial.println(odds);
    digitalWrite(randomPin, random(1024) < odds ? HIGH : LOW);
    lastTriggerTime = now;
  }
}
