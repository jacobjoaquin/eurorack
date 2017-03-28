int buttons[] = {13, 14, 15, 16};
int leds[] = {12, 11, 10, 9};
int triggerIn = 8;
// int triggerLED = 7;

int triggerOut = 6;

int position = 0;
int nSteps = 4;

ulong waitTime = 60000 / 120;
ulong nextTrigger = 0;

void wait() {
  while(millis() < nextTrigger) {}

  nextTrigger = millis() + waitTime;
}

void next() {
  // wait();
  while (digitalRead(triggerIn) == LOW) {}

  position = (position + 1) % nSteps;
  for(int i = 0; i < nSteps; i++) {
    digitalWrite(leds[i], LOW);
  }
  digitalWrite(leds[position], HIGH);


  // Turn on output (gate is determined by triggerIn);
  digitalWrite(triggerOut, HIGH);

  while (digitalRead(triggerIn) == HIGH) {};

  // Turn off output
  digitalWrite(triggerOut, LOW);
}

void initIO() {
  pinMode(triggerIn, INPUT);
  pinMode(triggerOut, OUTPUT);
  // pinMode(triggerLed, OUTPUT);

  for(int i = 0; i < nSteps; i++) {
    pinMode(buttons[i], INPUT);
    pinMode(leds[i], OUTPUT);
  }
}

void setup() {
  initIO();
}

void loop() {
  next();
}
