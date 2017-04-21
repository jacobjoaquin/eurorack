int timerPin = A0;
int oddsPin = A1;
int randomPin = 13;
int randomFlipPin = 12;
int flip = false;

int odds = 512;
uint32_t lastTriggerTime = 0;

void setup() {
  pinMode(randomPin, OUTPUT);
  pinMode(randomFlipPin, OUTPUT);
}

void loop() {
  uint32_t now = millis();

  if (now >= lastTriggerTime + analogRead(timerPin)) {
    lastTriggerTime = now;
    odds = analogRead(oddsPin);

    if (random(1024) < odds) {
      digitalWrite(randomPin, HIGH);

      // Flip-flop
      digitalWrite(randomFlipPin, flip);
      flip = !flip;
    } else {
      digitalWrite(randomPin, LOW);
    }
  }
}
