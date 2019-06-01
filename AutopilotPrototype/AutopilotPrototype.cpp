
// s1 - heading - 13
// s2 - nav - 12
// s3 - approach - 11
// s4 - backcourse - 10
// s5 - altitude - 9
// s6 - alt sel - 8
// s7 - vertical speed - 7
// s8 - ias - 6

const int headingBtnPin = 13,
      navBtnPin = 12,
      apprBtnPin = 11,
      backBtnPin = 10,
      altBtnPin = 9,
      altSelBtnPin = 8,
      vsBtnPin = 7,
      iasBtnPin = 6;

const int numAllBtns = 7;
const int allBtnPins[numAllBtns] = {
    headingBtnPin,
    apprBtnPin,
    backBtnPin,
    altBtnPin,
    altSelBtnPin,
    vsBtnPin,
    iasBtnPin
};

void setup() {
    // init input pulldown btns
    for (int i = 0; i < numAllBtns; i++) {
        pinMode(allBtnPins[i], INPUT_PULLUP);
        digitalWrite(allBtnPins[i], HIGH);
    }

    Serial.begin(9600);
    Serial.println("Starting...");
}

void loop() {
    if (!digitalRead(headingBtnPin)) {
        Serial.println("Pushed heading btn");
    }

}
