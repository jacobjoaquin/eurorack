/*
simpleSeq4.ino
Coded by Jacob Joaquin

Part of my Eurorack Build Journal
https://github.com/jacobjoaquin/eurorack

NOTE: The width of the output pulse is derived from the width
of the Clock Input pulse
*/

const int nSteps = 4;              // Number of steps
int position = nSteps - 1;         // Current step position
int buttons[] = {13, 14, 15, 16};  // Pins for buttons
int ledsPWM[] = {20, 21, 22, 23};  // Pins for LEDs
int clockInput = 8;                // Pin for Clock Input
int pulseOutput = 6;               // Pin for Pulse Output
int stepStates[] = {1, 0, 0, 0};   // Step states (1 = on, 0 = off)

// Modes
const int nModes = 4;
const int modeWaitForHigh = 0;
const int modeHigh = 1;
const int modeWaitForLow = 2;
const int modeLow = 3;
int mode = modeWaitForHigh;

// Button state debouncing
const uint32_t debounceDelay = 20;
uint32_t lastDebounceTime[] = {0, 0, 0, 0};
int buttonStates[] = {0, 0, 0, 0};
int lastButtonState[] = {0, 0, 0, 0};

// Advances to the next mode
void nextMode() {
  mode = (mode + 1) % nModes;
}

// Updates/debounces buttons and updates step states
// Code is a derivative of:
//     https://www.arduino.cc/en/tutorial/debounce
void updateButton(int index) {
  int reading = digitalRead(buttons[index]);

  if (reading != lastButtonState[index]) {
    lastDebounceTime[index] = millis();
  }

  if ((millis() - lastDebounceTime[index]) > debounceDelay) {
    if (reading != buttonStates[index]) {
      buttonStates[index] = reading;

      if (buttonStates[index] == HIGH) {
        stepStates[index] = !stepStates[index];
      }
    }
  }

  lastButtonState[index] = reading;
}

void setup() {
  // Setup jack input and output
  pinMode(clockInput, INPUT);
  pinMode(pulseOutput, OUTPUT);

  // Setup buttons
  for(int i = 0; i < nSteps; i++) {
    pinMode(buttons[i], INPUT);
  }
}

void loop() {
  // Check for button press
  for (int i = 0; i < nSteps; i++) {
    updateButton(i);
  }

  switch (mode) {
    case modeWaitForHigh:
    if (digitalRead(clockInput) == HIGH) {
      nextMode();
    }
    break;

    case modeHigh:
    // Advance step position
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
    if (stepStates[position]) {
      digitalWrite(pulseOutput, HIGH);
    }
    nextMode();
    break;

    case modeWaitForLow:
    if (digitalRead(clockInput) == LOW) {
      nextMode();
    }
    break;

    case modeLow:
    // Set output to LOW for active step
    digitalWrite(pulseOutput, LOW);
    nextMode();
    break;
  }
}
