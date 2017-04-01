const byte buttonPin = 2;
const byte resetPin = 12;
const byte clockPin = 13;
const int delayTime = 100;
unsigned long waitTime = 0;

void resetClock() {
  digitalWrite(resetPin, LOW);
  digitalWrite(clockPin, LOW);
  delay(5);
  digitalWrite(clockPin, HIGH);
  digitalWrite(resetPin, HIGH);
}

void setup() {
  Serial.begin(9600);
  pinMode(resetPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), resetClock, RISING);
  digitalWrite(resetPin, HIGH);
}

void loop() {
  digitalWrite(clockPin, HIGH);
  delay(delayTime);
  digitalWrite(clockPin, LOW);
  delay(delayTime);
}
