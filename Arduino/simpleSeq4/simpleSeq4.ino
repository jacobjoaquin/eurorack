int buttons[] = {13, 14, 15, 16};
int buttonStates[] = {1, 1, 0, 0};

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
  if (buttonStates[position] == HIGH) {
    digitalWrite(triggerOut, HIGH);
  }

  while (digitalRead(triggerIn) == HIGH) {};

  // Turn off output
  digitalWrite(triggerOut, LOW);
}

void updateButtonState(int button) {

  buttonStates[button] = !buttonStates[button];
}

void updateButtonState0() {
  updateButtonState(0);
}
void updateButtonState1() {
  updateButtonState(1);
}
void updateButtonState2() {
  updateButtonState(2);
}
void updateButtonState3() {
  updateButtonState(3);
}

void initIO() {
  pinMode(triggerIn, INPUT);
  pinMode(triggerOut, OUTPUT);
  // pinMode(triggerLed, OUTPUT);

  for(int i = 0; i < nSteps; i++) {
    pinMode(buttons[i], INPUT);
    pinMode(leds[i], OUTPUT);
  }
  attachInterrupt(digitalPinToInterrupt(buttons[0]), updateButtonState0, RISING);
  attachInterrupt(digitalPinToInterrupt(buttons[1]), updateButtonState1, RISING);
  attachInterrupt(digitalPinToInterrupt(buttons[2]), updateButtonState2, RISING);
  attachInterrupt(digitalPinToInterrupt(buttons[3]), updateButtonState3, RISING);
}


void setup() {
  // Serial.begin(9600);
  initIO();
}

void loop() {
  next();
}
