/*
simpleSeq4.ino
Coded by Jacob Joaquin

Part of my Eurorack Build Journal
https://github.com/jacobjoaquin/eurorack

NOTE: The width of the output pulse is derived from the width
of the Clock Input pulse
*/

const int nSteps = 4;                            // Number of steps
const uint32_t minStateDelay = 50;               // Minimum wait time before state change
int position = nSteps - 1;                       // Current step position
int buttons[] = {13, 14, 15, 16};                // Pins for buttons
int ledsPWM[] = {20, 21, 22, 23};                // Pins for LEDs
int clockInput = 8;                              // Pin for Clock Input
int pulseOutput = 6;                             // Pin for Pulse Output
volatile int stepStates[] = {1, 0, 1, 0};        // Step states (1 = on, 0 = off)
volatile uint32_t stateTimers[] = {0, 0, 0, 0};  // Time since last state changes

// Modes
const int nModes = 4;
const int modeWaitForHigh = 0;
const int modeHigh = 1;
const int modeWaitForLow = 2;
const int modeLow = 3;
int mode = modeWaitForHigh;

// Advances to the next mode
void nextMode() {
  mode = (mode + 1) % nModes;
}


// int lastButtonState[] = {0, 0, 0, 0}
// int buttonStates[] = {0, 0, 0, 0}
// uint32_t lastDebounceTime[] = {0, 0, 0, 0};
// uint32_t debounceDelay = 50;
//
// void updateButton(int index) {
//   // Buttons and Debouncing
//   // read the state of the switch into a local variable:
//   int reading = digitalRead(buttons[index]);
//
//   // check to see if you just pressed the button
//   // (i.e. the input went from LOW to HIGH),  and you've waited
//   // long enough since the last press to ignore any noise:
//
//   // If the switch changed, due to noise or pressing:
//   if (reading != lastButtonState[index]) {
//     // reset the debouncing timer
//     lastDebounceTime[index] = millis();
//   }
//
//   if ((millis() - lastDebounceTimelastDebounceTime[index]) > debounceDelay) {
//     // whatever the reading is at, it's been there for longer
//     // than the debounce delay, so take it as the actual current state:
//
//     // if the button state has changed:
//     if (reading != buttonStates[index]) {
//       buttonStates[index] = reading;
//
//       // only toggle the LED if the new button state is HIGH
//       if (buttonStates[index] == HIGH) {
//         stepStates[index] = !stepStates[index];
//       }
//     }
//   }
// }

// // Toggles step state
// void toggleState(int index) {
//   if (millis() >= stateTimers[index]) {
//     // Toggle if pressed
//     if (digitalRead(buttons[index]) == HIGH) {
//       stepStates[index] = !stepStates[index];
//     }
//   }
//
//   // Attempts to debounce button
//   stateTimers[index] = millis() + minStateDelay;
// }
//
// void toggleState0() {
//   toggleState(0);
// }
// void toggleState1() {
//   toggleState(1);
// }
// void toggleState2() {
//   toggleState(2);
// }
// void toggleState3() {
//   toggleState(3);
// }

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
  // updateButtons();

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
