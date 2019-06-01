#include<LiquidCrystal.h>

// s1 - heading - 13
// s2 - nav - 12
// s3 - approach - 11
// s4 - backcourse - 10
// s5 - altitude - 9
// s6 - alt sel - 8
// s7 - vertical speed - 7
// s8 - ias - 6

const int 
      headingBtnPin = 13,
      navBtnPin = 12,
      apprBtnPin = 11,
      backBtnPin = 10,
      altBtnPin = 9,
      altSelBtnPin = 8,
      vsBtnPin = 7,
      iasBtnPin = 6;

const int numAllBtns = 8;
const int allBtnPins[numAllBtns] = {
    headingBtnPin,
    navBtnPin,
    apprBtnPin,
    backBtnPin,
    altBtnPin,
    altSelBtnPin,
    vsBtnPin,
    iasBtnPin
};

// Array to track the prev state of each btn to see if its been toggled
int btnPressStates[numAllBtns] = {
    0,0,0,0,0,0,0
};

// keeps track if btn is actually toggld or not
int btnToggleStates[numAllBtns] = { 0,0,0,0,0,0,0,0};

String btnLabels[numAllBtns] = {
    "HDG",
    "NAV",
    "APPR",
    "BACK",
    "ALT",
    "ALTSEL",
    "VS",
    "IAS"
};

// lcd pins
const int D4Pin = 5, D5Pin = 4, D6Pin = 3, D7Pin = 2;
const int EPin = A1;
const int RWPin = A0;

LiquidCrystal lcd(RWPin, EPin, D4Pin, D5Pin, D6Pin, D7Pin);

void setup() {
    // init input pulldown btns
    for (int i = 0; i < numAllBtns; i++) {
        pinMode(allBtnPins[i], INPUT_PULLUP);
        digitalWrite(allBtnPins[i], HIGH);
    }

    lcd.begin(16, 2);

    Serial.begin(9600);
}

void toggleBtn(int btnIndex, String btnLabel) {
    int toggleState = btnToggleStates[btnIndex];
    if (toggleState == 1) {
        // toggle off
        Serial.print(btnLabel);
        Serial.println(" TOGGLED OFF");
        btnToggleStates[btnIndex] = 0;
    } else {
        // toggle on
        Serial.print(btnLabel);
        Serial.println(" TOGGLED ON");
        btnToggleStates[btnIndex] = 1;

/*         lcd.clear(); */
        /* lcd.print(btnLabel); */
    }
}

void loop() {
    for (int i = 0; i < numAllBtns; i++) {
        int btnPin = allBtnPins[i];
        int prevState = btnPressStates[i];
        String label = btnLabels[i];

        if (!digitalRead(btnPin)) {
            if (prevState != 1) {
                // on press
                btnPressStates[i] = 1;
/*                 Serial.print(label); */
                /* Serial.println(" PRESSED"); */
                toggleBtn(i, label);
            }
        } else {
            if (prevState != 0) {
                // release
                btnPressStates[i] = 0;
/*                 Serial.print(label); */
                /* Serial.println(" RELEASED"); */
            }
        }
    }

}
