#include <QueueArray.h>

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


int inputPinC = 10;   
int pirStateC = LOW; 
int valC = 0; 

int inputPinD = 9;   
int pirStateD = LOW; 
int valD = 0; 

bool Apushed;
bool Bpushed;

QueueArray <char> abqueue;



void setup() {
//  pinMode(ledPinA, OUTPUT);      // declare LEDA as output
  pinMode(inputPinA, INPUT);     // declare sensorA as input

  pinMode(ledPinB, OUTPUT);     // declare LEDB as output
  pinMode(inputPinB, INPUT);    //declare sensorB as input

// pinMode(ledPinC, OUTPUT);     // declare LEDB as output
  pinMode(inputPinC, INPUT);    //declare sensorB as input

 // pinMode(ledPinD, OUTPUT);     // declare LEDB as output
  pinMode(inputPinD, INPUT);    //declare sensorB as input

  bool Apushed = false;
  bool Bpushed = false;
  
  Serial.begin(19200);
}
 
void loop(){
  valA = digitalRead(inputPinA);  // read input value
  valB = digitalRead(inputPinB);  // read input value
  valC = digitalRead(inputPinC);  // read input value
  valD = digitalRead(inputPinD);  // read input value
   
    if (valA == HIGH) {            // check if the input is HIGH
    //digitalWrite(ledPinA, HIGH);  // turn LED ON
      if (pirStateA == LOW) {
          // we have just turned on
          Serial.println("Motion (A) detected!");
          // We only want to print on the output change, not state
          pirStateA = HIGH;
         //if(Apushed == false){
            Serial.println("a push success");
            abqueue.enqueue('a');
           // Apushed = true;
            //Bpushed = false;
          //}
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
    //digitalWrite(ledPinA, HIGH);  // turn LED ON
      if (pirStateB == LOW) {
          // we have just turned on
          Serial.println("Motion (B) detected!");
          // We only want to print on the output change, not state
          pirStateB = HIGH;
         //if(Bpushed == false){
            Serial.println("b push success");
            abqueue.enqueue('b');
            //Bpushed = true;
            //Apushed = false;
            //}
          }
        
      } else {
          //digitalWrite(ledPinA, LOW); // turn LED OFF
          if (pirStateB == HIGH){
          // we have just turned of
          Serial.println("Motion (B) ended!");
          // We only want to print on the output change, not state
          pirStateB = LOW;
        }
    }


    if(abqueue.count() >=2){
      char frontitem = abqueue.front();
      abqueue.pop();
      char seconditem = abqueue.front();
      Serial.println(frontitem);
      Serial.println(seconditem);
      abqueue.pop();
      if(frontitem == 'b' && seconditem == 'a'){
        Serial.println("decrement");
      }else if (frontitem == 'a' && seconditem == 'b'){
        Serial.println("increment");
      }
      while(!abqueue.isEmpty()){
        abqueue.pop();
      }
    }
    /*if(Bstatus){
      if(Astatus){
        Serial.println("decrement");
        Astatus= false;
        Bstatus = false;
      }
    }
    
    if (Astatus){
      if (Bstatus){
        Serial.println("increment");
        Astatus = false;
        Bstatus = false;
      }
    }*/
    
    
    
   /* if (pirStateA == HIGH)
    {
      if(valB == HIGH)
          {
          if (pirStateB == LOW) 
              {
              // we have just turned on
              Serial.println("increment");
              // We only want to print on the output change, not state
              pirStateB = HIGH; 
              }
          }else 
          {
            if (pirStateB == HIGH){
              // we have just turned of
              Serial.println("Motion (Bjj) ended!");
              // We only want to print on the output change, not state
              pirStateB = LOW;
            }
          }
    }
    //else if (valA == HIGH){
    //}
    */
    
    
    
    
  /*  if (valB == HIGH && pirStateA == HIGH) {            // check if the input is HIGH
         digitalWrite(ledPinB, HIGH);  // turn LED ON
         if (pirStateB == LOW) {
            // we have just turned on
            Serial.println("increment");
            // We only want to print on the output change, not state
            pirStateB = HIGH; 
            }
   } else {
            digitalWrite(ledPinB, LOW); // turn LED OFF
            if (pirStateB == HIGH){
              // we have just turned of
              Serial.println("Motion (Bjj) ended!");
              // We only want to print on the output change, not state
              pirStateB = LOW;
          }
      }

    if (valA == HIGH && pirStateB == HIGH) {            // check if the input is HIGH
         //digitalWrite(ledPinB, HIGH);  // turn LED ON
         if (pirStateA == LOW) {
            // we have just turned on
            Serial.println("deeecrement");
            // We only want to print on the output change, not state
            pirStateA = HIGH; 
            }
         } else {
            //digitalWrite(ledPinB, LOW); // turn LED OFF
            if (pirStateA == HIGH){
              // we have just turned of
              Serial.println("Motion (xx) ended!");
              // We only want to print on the output change, not state
              pirStateA = LOW;
          }
      }*/
      
    
}
