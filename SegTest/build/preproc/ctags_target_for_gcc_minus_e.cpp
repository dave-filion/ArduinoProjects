# 1 "/home/dave/repo/SegTest/SegTest.ino"
# 1 "/home/dave/repo/SegTest/SegTest.ino"

// for testing 4 digit 7 seg cirtcuit
const int segA = 9;
const int segB = 8;
const int segC = 7;
const int segD = 6;
const int segE = 5;
const int segF = 4;
const int segG = 3;

const int dig1 = 10;
const int dig2 = 11;
const int dig3 = 12;
const int dig4 = 13;

void setup() {
    pinMode(segA, 0x1);
    pinMode(segB, 0x1);
    pinMode(segC, 0x1);
    pinMode(segD, 0x1);
    pinMode(segE, 0x1);
    pinMode(segF, 0x1);
    pinMode(segG, 0x1);

    pinMode(dig1, 0x1);
    pinMode(dig2, 0x1);
    pinMode(dig3, 0x1);
    pinMode(dig4, 0x1);

    Serial.begin(9600);
}

void loop() {

    // turn on all segments, all digits
    digitalWrite(segA, 0x1);
    digitalWrite(segB, 0x1);
    digitalWrite(segC, 0x1);
    digitalWrite(segD, 0x1);
    digitalWrite(segE, 0x1);
    digitalWrite(segF, 0x1);
    digitalWrite(segG, 0x1);

    // turn all digits to high
    digitalWrite(dig1, 0x1);
    digitalWrite(dig2, 0x1);
    digitalWrite(dig3, 0x1);
    digitalWrite(dig4, 0x1);

    delay(2000);

    // turn all digits to low
    digitalWrite(dig1, 0x0);
    digitalWrite(dig2, 0x0);
    digitalWrite(dig3, 0x0);
    digitalWrite(dig4, 0x0);

    delay(2000);

    // turn off all segments, all digits
    digitalWrite(segA, 0x0);
    digitalWrite(segB, 0x0);
    digitalWrite(segC, 0x0);
    digitalWrite(segD, 0x0);
    digitalWrite(segE, 0x0);
    digitalWrite(segF, 0x0);
    digitalWrite(segG, 0x0);
}
