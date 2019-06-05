
// actual an on-on toggle switch, directing currrent
// to one pin or the other
const int in1 = A0;
const int in2 = A1;

const int pin1 = 7;
const int pin2 = 8;

void setup() {

    pinMode(pin1, INPUT_PULLUP);
    pinMode(pin2, INPUT_PULLUP);

    Serial.begin(9600);
}



void loop() {

/*     int reading1 = analogRead(in1); */
    /* int reading2 = analogRead(in2); */
    /*  */
    /* Serial.print(reading1); */
    /* Serial.print(" : "); */
    /* Serial.println(reading2); */
/*  */

    int reading = digitalRead(pin1);

    int reading2 = digitalRead(pin2);

    Serial.print(reading);
    Serial.print(" : ");
    Serial.println(reading2);


    delay(100);

}
