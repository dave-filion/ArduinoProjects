#include<LiquidCrystal.h>
#include<Streaming.h>


void printValues(int x, int y);

// bearing/altitude analog stick
const int stickSwitchPin = A5;
const int stickVrXPin = A4;
const int stickVrYPin = A3;

const int deadzoneX = 10;
const int deadzoneY = 10;

const bool invertY = true;
const bool invertX = false;

// Altitude from previous cycle
long prevAltitude = 0;
long targetAltitude = 0;
const long altIncrement = 200;

// heading
int prevHeading = 0;
int targetHeading = 0;

// s1 - heading - 13
// s2 - nav - 12
// s3 - approach - 11
// s4 - backcourse - 10
// s5 - altitude - 9
// s6 - alt sel - 8
// s7 - vertical speed - 7
// s8 - ias - 6

const int 
      headingBtnPin = 22,
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

int calibrateX = 0;
int calibrateY = 0;

// timing values
long lastUpdate = 0;
long updateIncrement = 500; // milli

LiquidCrystal lcd(RWPin, EPin, D4Pin, D5Pin, D6Pin, D7Pin);

void setup() {
    // init input pulldown btns
    for (int i = 0; i < numAllBtns; i++) {
        pinMode(allBtnPins[i], INPUT_PULLUP);
        digitalWrite(allBtnPins[i], HIGH);
    }

    lcd.begin(16, 2);

    Serial.begin(9600);

    // calibrate stick with middle readings
    Serial.println("Taking calibrate reading... (X then Y)");
    calibrateX = analogRead(stickVrXPin);
    delay(100);
    calibrateY = analogRead(stickVrYPin);
    Serial.print("CALIBRATION VALUES: ");
    printValues(calibrateX, calibrateY);

    Serial.println("Starting...");
}

void printValues(int x, int y) {
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.println(y);
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
void increaseHeading() {
    int temp = targetHeading + 1;
    if (temp == 360) {
        // circle back to 0
        targetHeading = 0;
    } else {
        targetHeading = temp;
    }
}

void decreaseHeading() {
    int temp = targetHeading - 1;
    if (temp == -1) {
        targetHeading = 359;
    } else {
        targetHeading = temp;
    }
}


void adjustX(int diff) {
    if (diff < 0) {
        if (invertX) {
            increaseHeading();
        } else {
            decreaseHeading();
        }
    } else {
        // positive
        if (invertX) {
            decreaseHeading();
        } else {
            increaseHeading();
        }
    }
}


void increaseAltitude() {
    long temp = targetAltitude + altIncrement;
    if (temp <= 45000) {
        targetAltitude = temp;
    }
}

void decreaseAltitude() {
    long temp = targetAltitude - altIncrement;
    if (temp >= 0) {
        // dont let altitude go below 0
        targetAltitude = temp;
    }
}

void adjustY(int diff) {
    if (diff < 0) {
        // negative change
        if (invertY) {
            increaseAltitude();
        } else {
            decreaseAltitude();
        }
    } else {
        // positive change
        if (invertY) {
            decreaseAltitude();
        } else {
            increaseAltitude();
        }
    }
}

void loop() {
/*     int stickPush = digitalRead(stickSwitchPin); */
    /* if (!stickPush) { */
    /*     Serial.println("STICK PUSHED"); */
    /* } */
/*  */
    int stickXRead = analogRead(stickVrXPin);
    int stickYRead = analogRead(stickVrYPin);

    int diffx = stickXRead - calibrateX;
    int diffy = stickYRead - calibrateY;

    if (abs(diffx) > deadzoneX) {
        // Adjust X (heading)
        adjustX(diffx);
    }

    if (abs(diffy) > deadzoneY) {
        // Adjust Y (altitude)
        adjustY(diffy);
    }

    if (targetAltitude != prevAltitude) {
        Serial.print("ALT: ");
        Serial.println(targetAltitude);
        prevAltitude = targetAltitude;
    }

    if (targetHeading != prevHeading) {
        Serial.print("HDG: ");
        Serial.println(targetHeading);
        prevHeading =targetHeading;
    }

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

    // see if ready for state update
    long now = millis();
    if ((now - lastUpdate) > updateIncrement) {
        Serial.println("UPDATE");

        lastUpdate = now;

    }

}
