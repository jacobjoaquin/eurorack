int odds0Pin = A0;  // HIGH or LOW
int odds1Pin = A1;  // Flip-flop
int random0Pin = 12;
int random1Pin = 11;
int flip = false;

int odds = 512;

int clockInputPin = 10;
int lastClockInput = LOW;

void setup() {
  pinMode(random0Pin, OUTPUT);
  pinMode(random1Pin, OUTPUT);
  pinMode(clockInputPin, INPUT);
}

void loop() {
  int clockInput = digitalRead(clockInputPin);

  if (clockInput == HIGH && clockInput != lastClockInput) {
    uint32_t odds0 = analogRead(odds0Pin);
    uint32_t odds1 = analogRead(odds1Pin);

    // HIGH or LOW
    if (random(1024) < odds0) {
      digitalWrite(random0Pin, HIGH);

    } else {
      digitalWrite(random0Pin, LOW);
    }

    // Flip-flop
    if (random(1024) < odds1) {
      digitalWrite(random1Pin, flip);
      flip = !flip;
    }
  }
  
  lastClockInput = clockInput;
}
