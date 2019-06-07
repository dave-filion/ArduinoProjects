
const int btn0 = 3;
const int btn1 = 4;
const int btn2 = 5;
const int btn3 = 6;
const int btn4 = 7;
const int btn5 = 8;
const int btn6 = 9;
const int btn7 = 10;
const int btn8 = 11;
const int btn9 = 12;

const int btnOn = 2;
int onBtnState = 0;

//const int fnBtns[2] = {btnOn, btnOff};
//const String fnBtnLabels[2] = {"on", "off"};
//int fnBtnState[2] = {0,0};

const int numberBtns[10] = {
    btn0,
    btn1,
    btn2,
    btn3,
    btn4,
    btn5,
    btn6,
    btn7,
    btn8,
    btn9
};

int numBtnState[10] = {0,0,0,0,0,0,0,0,0,0};

void setup() {
//  // init fn btns
//  for (int i = 0; i < 2; i++) {
//    pinMode(fnBtns[i], INPUT_PULLUP);
//  }

    // on btn
    pinMode(btnOn, INPUT_PULLUP);
  
    // init number btns
    for (int i = 0; i < 10; i++) {
        pinMode(numberBtns[i], INPUT_PULLUP);
    }
    Serial.begin(9600);
}

void loop() {
  // check fn btns
//    for (int i = 0; i < 2; i++) {
//        int btnReading = digitalRead(fnBtns[i]);
//        int btnState = fnBtnState[i];
//        if (!btnReading) {
//            if (btnState == 0) {
//              // output message to seriqal port
//              Serial.print("btn_");
//              Serial.print(fnBtnLabels[i]);
//              Serial.println("|!"); // denotes ernd of message
//              fnBtnState[i] = 1;
//            }
//        } else {
//            if (btnState == 1) {
//                //Serial.print(i);
//                //Serial.println(" released");
//                fnBtnState[i] = 0;
//            }
//        }
//    }

  int btnOnReading = digitalRead(btnOn);
  if (!btnOnReading) {
    // btn being pushed
    if (onBtnState == 0) {
      Serial.println("btn_on|!");
      onBtnState = 1;
    }
  } else {
    // not being pushed
    if (onBtnState == 1) {
      onBtnState = 0;
    }
  }
  
  // check digit btns
    for (int i = 0; i < 10; i++) {
        int btnReading = digitalRead(numberBtns[i]);
        int btnState = numBtnState[i];
        if (!btnReading) {
            if (btnState == 0) {
              // output message to seriqal port
              Serial.print("btn_");
              Serial.print(i);
              Serial.println("|!"); // denotes ernd of message
              numBtnState[i] = 1;
            }
        } else {
            if (btnState == 1) {
                //Serial.print(i);
                //Serial.println(" released");
                numBtnState[i] = 0;
            }
        }
    }
}
