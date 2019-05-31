
const int dataPin = 7;
const int latchPin = 5;
const int clockPin = 4;

const int numberOfPatterns = 8;

const byte bitPatterns[numberOfPatterns] = {
        B10000000,
        B01000000,
        B00100000,
        B00010000,
        B00001000,
        B00000100,
        B00000010,
        B00000001
};

void setup(){ 
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    Serial.begin(9600);
    Serial.println("reset");
}

void loop() {

    byte bitsToSnd = 0;

    for (int i = 0; i < numberOfPatterns; i++) {
        bitsToSnd = bitPatterns[i];

        // open latch by setting it to low
        digitalWrite(latchPin, LOW);

        // shift the bits out
        shiftOut(dataPin, clockPin, LSBFIRST, bitsToSnd);

        // close latch to write data
        digitalWrite(latchPin, HIGH);

        delay(1000);
    }

    Serial.println("Done with all patterns");
}

