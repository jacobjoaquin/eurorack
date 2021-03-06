const int triggerInputPin = 10;  // Clock input
const int odds0Pin = A0;         // HIGH or LOW input
const int odds1Pin = A1;         // Flip-flop input
const int random0Pin = 12;       // HIGH or LOW pin output
const int random1Pin = 11;       // Flip-flop pin out
int flip = false;                // Current state of random1
int lastTriggerInput = LOW;      // Last clock input

void setup() {
  pinMode(random0Pin, OUTPUT);
  pinMode(random1Pin, OUTPUT);
  pinMode(triggerInputPin, INPUT);
}

void loop() {
  int triggerInput = digitalRead(triggerInputPin);

  // Trigger next random check when on pulse in.
  if (triggerInput == HIGH && triggerInput != lastTriggerInput) {
    uint32_t odds0 = analogRead(odds0Pin);
    uint32_t odds1 = analogRead(odds1Pin);

    // HIGH or LOW Output
    if (random(1024) < odds0) {
      digitalWrite(random0Pin, HIGH);
    } else {
      digitalWrite(random0Pin, LOW);
    }

    // Flip-flop Output
    if (random(1024) < odds1) {
      digitalWrite(random1Pin, flip);
      flip = !flip;
    }
  }

  lastTriggerInput = triggerInput;
}
