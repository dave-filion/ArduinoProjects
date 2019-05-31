#include <Arduino.h>
#line 1 "/home/dave/repo/SegTest/SegTest.ino"
#line 1 "/home/dave/repo/SegTest/SegTest.ino"

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

#line 16 "/home/dave/repo/SegTest/SegTest.ino"
void setup();
#line 33 "/home/dave/repo/SegTest/SegTest.ino"
void loop();
#line 16 "/home/dave/repo/SegTest/SegTest.ino"
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

    Serial.begin(9600);
}

void loop() {

    // turn on all segments, all digits
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, HIGH);
    digitalWrite(segG, HIGH);

    // turn all digits to high
    digitalWrite(dig1, HIGH);
    digitalWrite(dig2, HIGH);
    digitalWrite(dig3, HIGH);
    digitalWrite(dig4, HIGH);
    
    delay(2000);

    // turn all digits to low
    digitalWrite(dig1, LOW);
    digitalWrite(dig2, LOW);
    digitalWrite(dig3, LOW);
    digitalWrite(dig4, LOW);
 
    delay(2000);

    // turn off all segments, all digits
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW);
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
}

