/*
 * tinkerBOY's usb_gamepad v1.0
 * 
 */

#include <Joystick.h>

#define PINS 13
#define ENABLE_ANALOG1 true
int X1 = A2;
int Y1 = A1;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, PINS, 0, 
  true, true, false, false, false, false, false, false, false, false, false);

class CButton {
  public:
  int pin = NULL;
  int lastState = 0;
  
  CButton(int p) {
    pin = p;
  }
};

CButton Buttons[PINS] ={3,2,4,5,6,7,8,9,10,15,14,16,21};

void setup() {
  for(int i=0 ; i<PINS ;i++) {
    pinMode(Buttons[i].pin, INPUT_PULLUP);
  }

  Joystick.begin();
  if (ENABLE_ANALOG1) {
    Joystick.setXAxisRange(-512, 512);
    Joystick.setYAxisRange(-512, 512);
  }
}

void JButtonStates() {
  if (ENABLE_ANALOG1) {
    Joystick.setXAxis(512 - analogRead(X1));
    Joystick.setYAxis(512 - analogRead(Y1));
  }
  
  for (int i = 0; i < PINS; i++) {
    int currentState = !digitalRead(Buttons[i].pin);
    
    if (currentState != Buttons[i].lastState) {
      Joystick.setButton(i, currentState);
      Buttons[i].lastState = currentState;
    }
  }  
}

void loop() {
  JButtonStates();
  delay(50);
}
