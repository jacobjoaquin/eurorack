int odds0Pin = A0;  // HIGH or LOW
int odds1Pin = A1;  // Flip-flop
int random0Pin = 12;
int random1Pin = 11;
int flip = false;

int odds = 512;
uint32_t lastTriggerTime = 0;

void setup() {
  pinMode(random0Pin, OUTPUT);
  pinMode(random1Pin, OUTPUT);
}

void loop() {
  uint32_t now = millis();
  // uint32_t timerInput = analogRead(timerPin);
  uint32_t timerInput = 50;

  if (now >= lastTriggerTime + timerInput) {
    lastTriggerTime = now;
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
}
