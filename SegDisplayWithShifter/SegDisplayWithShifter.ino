// Rotary encoder data
// has to be 2/3 since these pins allow interrupts
int const encodePin1 = 2;
int const encodePin2 = 3;
int const encodeSwitchPin = 4;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

// 7 segment 4 digit display data
const int dig1 = 13;
const int dig2 = 12;
const int dig3 = 11;
const int dig4 = 10;

int digPinArray[4] = {
    dig1, dig2, dig3, dig4
};

// bit shift data
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


int currentValue = 0;
// four digit number 
int digitsToRender[4] = {
    0, 0, 0, 0
};
// index of which digit to render this loop, max of 3
int currentDigit = 0;

// define functions
void updateEncoder();

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

    pinMode(encodePin1, INPUT_PULLUP);
    pinMode(encodePin2, INPUT_PULLUP);
    pinMode(encodeSwitchPin, INPUT_PULLUP);

    // call updateEncoder when any high/low changed seen on interrupt
    attachInterrupt(digitalPinToInterrupt(encodePin1), updateEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encodePin2), updateEncoder, CHANGE);

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
    shiftOut(dataPin, clockPin, LSBFIRST, bitsToSend);

    // close latch to write data
    digitalWrite(latchPin, HIGH);

    // turn on the one digit
    turnOnOnlyDigit(currentDigit);
}

void updateEncoder() {
    int MSB = digitalRead(encodePin2); // MSB most signifigant bit
    int LSB = digitalRead(encodePin1); // LSB least signifigant bit

    int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single numb
    int sum = (lastEncoded << 2) | encoded; // adding it to previous encoded value
    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
        // increment event
        encoderValue++;
    }

    if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
        // decrement event
        // dont go below 0
        if (encoderValue > 0) {
            encoderValue--;
        }
    }

    lastEncoded = encoded;
}

// Todo figure out how to do this
void breakUpNumber(int number) {
    int i = 3;
    while (number > 0) {
        int digit = number % 10;
        digitsToRender[i] = digit;
        i--;

        number = number - digit;
        number = number / 10;
    }
    // pad with 0's
    if (i == 3) {
        digitsToRender[0] = 0;
        digitsToRender[1] = 0;
        digitsToRender[2] = 0;
        digitsToRender[3] = 0;
    }else if (i == 2) {
        digitsToRender[0] = 0;
        digitsToRender[1] = 0;
        digitsToRender[2] = 0;
    } else if (i == 1) {
        digitsToRender[0] = 0;
        digitsToRender[1] = 0;
    } else if (i == 0) {
        digitsToRender[0] = 0;
    }
}


void loop() {
    if (encoderValue != currentValue) {
        // set digits to encoderValue
        currentValue = encoderValue;
        breakUpNumber(encoderValue);
    }

    if (digitalRead(encodeSwitchPin)) {
        // encoder btn not pushed
    } else {
        // btn pushed
        Serial.println("btn pushed");
    }


    // might need digits off
    renderCurrentDigit();
    // reset at last digit
    if (currentDigit == 3) {
        currentDigit = 0;
    } else {
        currentDigit++;
    }

    // very small delay so display will be clearer
    delay(2);
}
