/*
simpleSeq4.ino
Coded by Jacob Joaquin

Part of my Eurorack Build Journal
https://github.com/jacobjoaquin/eurorack
*/

const int nSteps = 4;                       // Number of steps
int position = nSteps - 1;                  // Current step position
int buttons[] = {13, 14, 15, 16};           // Pins for buttons
int ledsPWM[] = {20, 21, 22, 23};           // Pins for LEDs
int triggerIn = 8;                          // Pin for Clock Input
int triggerOut = 6;                         // Pin for Pulse Output
volatile int stepStates[] = {1, 1, 1, 1};   // Step states (1 = on, 0 = off)

// Flips the state of the button
void toggleButtonState(int button) {
  stepStates[button] = !stepStates[button];
}

void toggleButtonState0() {
  toggleButtonState(0);
}
void toggleButtonState1() {
  toggleButtonState(1);
}
void toggleButtonState2() {
  toggleButtonState(2);
}
void toggleButtonState3() {
  toggleButtonState(3);
}

void setup() {
  // Setup jack input and output
  pinMode(triggerIn, INPUT);
  pinMode(triggerOut, OUTPUT);

  // Setup buttons
  for(int i = 0; i < nSteps; i++) {
    pinMode(buttons[i], INPUT);
  }

  // Attach interrupts that flips step states
  attachInterrupt(digitalPinToInterrupt(buttons[0]), toggleButtonState0, RISING);
  attachInterrupt(digitalPinToInterrupt(buttons[1]), toggleButtonState1, RISING);
  attachInterrupt(digitalPinToInterrupt(buttons[2]), toggleButtonState2, RISING);
  attachInterrupt(digitalPinToInterrupt(buttons[3]), toggleButtonState3, RISING);
}

void loop() {
  // Wait for clock in pulse
  while (digitalRead(triggerIn) == LOW) {}

  // Advance clock
  position = (position + 1) % nSteps;

  // Clear LEDs
  for(int i = 0; i < nSteps; i++) {
    analogWrite(ledsPWM[i], 0);
  }

  // Adust brightness of active LED
  if (stepStates[position]) {
    // Bright if played
    analogWrite(ledsPWM[position], 255);
  } else {
    // Dim if current position but not played
    analogWrite(ledsPWM[position], 8);
  }

  // Set output to HIGH for active step
  if (stepStates[position] == HIGH) {
    digitalWrite(triggerOut, HIGH);
  }

  // Wait for clock in signal to go to low
  while (digitalRead(triggerIn) == HIGH) {};

  // Set output to LOW for active step
  digitalWrite(triggerOut, LOW);

  // NOTE: The width of the output pulse is derived from the width
  // of the Clock Input pulse
}
