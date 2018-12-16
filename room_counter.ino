#include <QueueArray.h>


#include <SPI.h>
#include <WiFi101.h>

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

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "iPhone";        // your network SSID (name)
char pass[] = "gasoline";  //our network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
//WiFiClient client;

QueueArray <char> abqueue;

int totalcount = 0;
int currentlyinroomcount = 0;

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

  //configure pins for Adafruit ATWINC1500 Feather
  WiFi.setPins(8,7,4,2);
  
  Serial.begin(19200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // print the network name (SSID);
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP(ssid);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  }

  // wait 10 seconds for connection:
  delay(10000);

  // start the web server on port 80
  server.begin();

  // you're connected now, so print out the status
  printWiFiStatus();
  
}
 
void loop(){
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println("Refresh: 5");
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<body> <h1> ROOM COUNTER </h1>");

            server.print("People currently in room = ");
            server.print(currentlyinroomcount);
            client.println("<br>");
            server.print("Total number of people entered = ");
            server.print(totalcount);

            delay(2000);

            client.println("</body>");
            // The HTTP response ends with another blank line:
            client.println("</html>");
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }

  
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
         //if(Apushed   == false){
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
        //Serial.println("decrement");
        if(currentlyinroomcount != 0){
            currentlyinroomcount -= 1;
        }
      }else if (frontitem == 'a' && seconditem == 'b'){
        //Serial.println("increment");
        currentlyinroomcount += 1;
        totalcount += 1;
      }
      Serial.println("currentlyinroomcount: ");
      Serial.println(currentlyinroomcount);
      Serial.println("total times entered today: ");
      Serial.println(totalcount);
      while(!abqueue.isEmpty()){
        abqueue.pop();
      }
    }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
    
    // VV below is old initial algorithm code VV 
    
    
    
    
    
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
      
    
