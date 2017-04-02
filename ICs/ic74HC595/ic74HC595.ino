// Pins
int latchPin = 10;  // to RCLK DIP pin 12
int clockPin = 11;  // to SER DIP pin 14
int dataPin = 12;   // to SRCLK DIP pin 11

// The output byte
uint8_t counter = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, counter);
  digitalWrite(latchPin, HIGH);
  counter++;
  delay(100);
}
