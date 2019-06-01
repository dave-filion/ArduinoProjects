
const int dig1 = 13;
const int dig2 = 12;
const int dig3 = 11;
const int dig4 = 10;

int digPinArray[4] = {
    dig1, dig2, dig3, dig4
};

const int dataPin = 7;
const int latchPin = 8;
const int clockPin = 9;

// A B C D E F G
const byte decimalBits[10] = {
    B11111100, //0
    B01100000, //1
    B11011010, //2
    B11110010, //3
    B01100110, //4
    B10110110, //5
    B10111110, //6
    B11100000, //7
    B11111110, //8
    B11100110, //9
}; 

// four digit number 
int digitsToRender[4] = {
    0, 1, 2, 3
};
// index of which digit to render this loop, max of 3
int currentDigit = 0;

void setup() {
    // register
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    // display
    pinMode(dig1, OUTPUT);
    pinMode(dig2, OUTPUT);
    pinMode(dig3, OUTPUT);
    pinMode(dig4, OUTPUT);

    digitalWrite(dig1, HIGH);
    digitalWrite(dig2, HIGH);
    digitalWrite(dig3, HIGH);
    digitalWrite(dig4, HIGH);

    Serial.begin(9600);
    Serial.println("reset");
}

void digitsOff() {
    // LOW is on
    digitalWrite(dig1, HIGH);
    digitalWrite(dig2, HIGH);
    digitalWrite(dig3, HIGH);
    digitalWrite(dig4, HIGH);
}

// turn off all digits, then turn on the one specified by digit index
void turnOnOnlyDigit(int digitIndex) {
    digitsOff();
    int digitPin = digPinArray[digitIndex];
    digitalWrite(digitPin, LOW);
}

void renderCurrentDigit() {
    int val = digitsToRender[currentDigit];
    byte bitsToSend = decimalBits[val];

    // open latch by setting it to low
    digitalWrite(latchPin, LOW);

    // shift the bits out
    shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // close latch to write data
    digitalWrite(latchPin, HIGH);

    // turn on the one digit
    turnOnOnlyDigit(currentDigit);
}

void loop() {
    digitsOff();
    renderCurrentDigit();

    // reset at last digit
    if (currentDigit == 3) {
        currentDigit = 0;
    } else {
        currentDigit++;
    }

    // very small delay so display will be clearer
    delay(4);

}
