/*
simpleSeq4.ino
Coded by Jacob Joaquin

Part of my Eurorack Build Journal
https://github.com/jacobjoaquin/eurorack
*/

const int nSteps = 4;               // Number of steps
int position = nSteps - 1;          // Current step position
int buttons[] = {13, 14, 15, 16};   // Pins for buttons
int buttonStates[] = {1, 1, 1, 1};  // Button states
int ledsPWM[] = {20, 21, 22, 23};   // Pins for LEDs
int triggerIn = 8;                  // Pin for Clock Input
int triggerOut = 6;                 // Pin for Pulse Output


// Flips the state of the button
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

void setup() {
  // Setup jack input and output
  pinMode(triggerIn, INPUT);
  pinMode(triggerOut, OUTPUT);

  // Setup buttons and LEDs
  for(int i = 0; i < nSteps; i++) {
    pinMode(buttons[i], INPUT);
    pinMode(leds[i], OUTPUT);
  }

  // Attach interrupts that flips button states
  attachInterrupt(digitalPinToInterrupt(buttons[0]), updateButtonState0, RISING);
  attachInterrupt(digitalPinToInterrupt(buttons[1]), updateButtonState1, RISING);
  attachInterrupt(digitalPinToInterrupt(buttons[2]), updateButtonState2, RISING);
  attachInterrupt(digitalPinToInterrupt(buttons[3]), updateButtonState3, RISING);
}

void loop() {
  // Wait for clock in pulse
  while (digitalRead(triggerIn) == LOW) {}

  // Advance clock
  position = (position + 1) % nSteps;

  // Clear LEDs
  for(int i = 0; i < nSteps; i++) {
    // digitalWrite(leds[i], LOW);
    analogWrite(ledsPWM[i], 0);
  }

  // digitalWrite(leds[position], HIGH);

  // Adust brightness of active LED
  if (buttonStates[position]) {
    // Bright if played
    analogWrite(ledsPWM[position], 255);
  } else {
    // Dim if current position but not played
    analogWrite(ledsPWM[position], 8);
  }

  // Set output to HIGH for active step
  if (buttonStates[position] == HIGH) {
    digitalWrite(triggerOut, HIGH);
  }

  // Wait for clock in signal to go to low
  while (digitalRead(triggerIn) == HIGH) {};

  // Set output to LOW for active step
  digitalWrite(triggerOut, LOW);

  // NOTE: The width of the output pulse is derived from the width
  // of the Clock Input pulse
}
