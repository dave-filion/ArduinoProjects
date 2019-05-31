
// for testing 4 digit 7 seg cirtcuit
const int segA = 9;
const int segB = 8;
const int segC = 7;
const int segD = 6;
const int segE = 5;
const int segF = 4;
const int segG = 3;

// digits seem reversed, 1 is rightmost
const int dig1 = 13;
const int dig2 = 12;
const int dig3 = 11;
const int dig4 = 10;

int numberToDisplay = 0;
int digToRenderThisCycle = 0;
int digitVals[4] = {1, 2, 3, 0};


void clearSegments() {
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW);
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
}

void renderSegments(int value) {
    clearSegments();
    if (value == 0) {
        // a b c d e f
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segE, HIGH);
        digitalWrite(segF, HIGH);
    } else if (value == 1) {
        digitalWrite(segB, HIGH);
        digitalWrite(segC, HIGH);

    } else if (value == 2) {
        //a b g e d
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segG, HIGH);
        digitalWrite(segE, HIGH);
        digitalWrite(segD, HIGH);
    } else if (value == 3) {
        // a b g c d
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segG, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segD, HIGH);
    }
}

void setup() {
    pinMode(segA, OUTPUT);
    pinMode(segB, OUTPUT);
    pinMode(segC, OUTPUT);
    pinMode(segD, OUTPUT);
    pinMode(segE, OUTPUT);
    pinMode(segF, OUTPUT);
    pinMode(segG, OUTPUT);

    pinMode(dig1, OUTPUT);
    pinMode(dig2, OUTPUT);
    pinMode(dig3, OUTPUT);
    pinMode(dig4, OUTPUT);

    numberToDisplay = 123;

    Serial.begin(9600);
}

void runThroughSegments() {
    digitalWrite(segA, HIGH);
    delay(500);
    clearSegments();
    digitalWrite(segB, HIGH);
    delay(500);
    clearSegments();
    digitalWrite(segC, HIGH);
    delay(500);
    clearSegments();
    digitalWrite(segD, HIGH);
    delay(500);
    clearSegments();
    digitalWrite(segE, HIGH);
    delay(500);
    clearSegments();
    digitalWrite(segF, HIGH);
    delay(500);
    clearSegments();
    digitalWrite(segG, HIGH);
    delay(500);
    clearSegments();
}

void turnOffAllDigits() {
    digitalWrite(dig1, HIGH);
    digitalWrite(dig2, HIGH);
    digitalWrite(dig3, HIGH);
    digitalWrite(dig4, HIGH);
}

void turnOnDigit(int val) {
    if (val == 0) {
        digitalWrite(dig1, LOW);
    } else if (val == 1) {
        digitalWrite(dig2, LOW);
    } else if (val == 2) {
        digitalWrite(dig3, LOW);
    } else if (val == 3) {
        digitalWrite(dig4, LOW);
    } else {
        Serial.print("cannot do value of: ");
        Serial.println(val);
    }
}

void renderDigit() {
    int digitIndex = digToRenderThisCycle;

    // turn off all digits
    turnOffAllDigits();

    // clear segments
    clearSegments();

    // get val we want to show
    int val = digitVals[digitIndex];

    // display numer in that digits place
    renderSegments(val);

    // turn on one we want
    turnOnDigit(digitIndex);
}

void loop() {

    renderDigit();

    // reset if digit is 3
    if (digToRenderThisCycle == 3) {
        digToRenderThisCycle = 0;
    } else {
        digToRenderThisCycle += 1;
    }

    // need this delay, otherwise becomes a blue
    delay(5);

}


