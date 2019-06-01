
// has to be 2/3 since these pins allow interrupts
int const encodePin1 = 2;
int const encodePin2 = 3;
int const encodeSwitchPin = 4;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

// define functions
void updateEncoder();

void setup() {
    Serial.begin(9600);

    pinMode(encodePin1, INPUT_PULLUP);
    pinMode(encodePin2, INPUT_PULLUP);
    pinMode(encodeSwitchPin, INPUT_PULLUP);

    // call updateEncoder when any high/low changed seen on interrupt
    attachInterrupt(digitalPinToInterrupt(encodePin1), updateEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encodePin2), updateEncoder, CHANGE);
}

void loop()
{
    Serial.println(encoderValue);
    if (digitalRead(encodeSwitchPin)) {
        // button not pushed
    } else {
        // button pushed
        Serial.println("btn pushed");
    }
    delay(100); // just to slow down the output
}

void updateEncoder() {
    int MSB = digitalRead(encodePin2); // MSB most signifigant bit
    int LSB = digitalRead(encodePin1); // LSB least signifigant bit

    int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single numb
    int sum = (lastEncoded << 2) | encoded; // adding it to previous encoded value
    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
        // increment event
        encoderValue++;
        Serial.println("turning clockwise");
    }

    if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
        // decrement event
        encoderValue--;
        Serial.println("turning counter-clockwise");
    }

    lastEncoded = encoded;
}

