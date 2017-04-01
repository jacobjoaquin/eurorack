const byte buttonPin = 2;
const byte resetPin = 8;
const byte clockPin = 9;
const int delayTime = 200;
unsigned long waitTime = 0;

void resetClock() {
  digitalWrite(clockPin, LOW);
  digitalWrite(resetPin, LOW);
  delay(5);
  digitalWrite(clockPin, HIGH);
  digitalWrite(resetPin, HIGH);
}

void setup() {
  pinMode(resetPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), resetClock, RISING);
  digitalWrite(resetPin, HIGH);
  resetClock();
}

void loop() {
  digitalWrite(clockPin, HIGH);
  delay(delayTime);
  digitalWrite(clockPin, LOW);
  delay(delayTime);
}
