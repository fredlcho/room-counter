/*
 * PIR sensor tester
 */
 
//int ledPinA = 12;                // choose the pin for the LED
int inputPinA = 13;               // choose the input pin (for PIR sensor)
int pirStateA = LOW;             // we start, assuming no motion detected
int valA = 0;                    // variable for reading the pin status

int ledPinB = 11;                // choose the pin for the LED
int inputPinB = 12;               // choose the input pin (for PIR sensor)
int pirStateB = LOW;             // we start, assuming no motion detected
int valB = 0;                    // variable for reading the pin status
 
void setup() {
//  pinMode(ledPinA, OUTPUT);      // declare LEDA as output
  pinMode(inputPinA, INPUT);     // declare sensorA as input

  pinMode(ledPinB, OUTPUT);     // declare LEDB as output
  pinMode(inputPinB, INPUT);    //declare sensorB as input
  
  Serial.begin(9600);
}
 
void loop(){
  valA = digitalRead(inputPinA);  // read input value
  valB = digitalRead(inputPinB);  // read input value
  
  
  if (valA == HIGH) {            // check if the input is HIGH
    //digitalWrite(ledPinA, HIGH);  // turn LED ON
    if (pirStateA == LOW) {
      // we have just turned on
      Serial.println("Motion (A) detected!");
      // We only want to print on the output change, not state
      pirStateA = HIGH;
    }
  } else {
    //digitalWrite(ledPinA, LOW); // turn LED OFF
    if (pirStateA == HIGH){
      // we have just turned of
      Serial.println("Motion (A) ended!");
      // We only want to print on the output change, not state
      pirStateA = LOW;
    }
  }
  if (valB == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPinB, HIGH);  // turn LED ON
    if (pirStateB == LOW) {
      // we have just turned on
      Serial.println("Motion (B) detected!");
      // We only want to print on the output change, not state
      pirStateB = HIGH;
    }
  } else {
    digitalWrite(ledPinB, LOW); // turn LED OFF
    if (pirStateB == HIGH){
      // we have just turned of
      Serial.println("Motion (B) ended!");
      // We only want to print on the output change, not state
      pirStateB = LOW;
    }
  }
}
