#include <IRremote.h>
#include <Servo.h>

Servo servo;

int greenLedPin = 5;    // defind pins for green, yellow and red LED
int yellowLedPin = 6;
int redLedPin = 7;

int bluePin = 8;        // define pins for RGB LED
int greenPin = 9;
int redPin = 10;

int button1 = 2;        // Define pins for buttons
int button2 = 3;

int servoPin=13;        // Define a pin for Servo

int lightPin = 0;       // Define a pin for Photo resistor

int irPin = 11;         // Define a pin for IR Receiver
IRrecv irrecv(irPin); 
decode_results results;
 
int choose = 0;         // Game choosing variable

void setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);  
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);   
  pinMode(redPin, OUTPUT);  
  pinMode(greenLedPin, OUTPUT);    
  pinMode(yellowLedPin, OUTPUT);  
  pinMode(redLedPin, OUTPUT);  
  
  irrecv.enableIRIn();        // Start the IR receiver
  
  servo.attach(servoPin);     // Attach the Servo variable to a pin
  servo.write(0);             // Initialize the servo at 0 degrees

  Serial.begin(9600);
}

void loop() {
   servo.write(90);                           // Set the servo at 90 degrees
   Serial.println(choose);
   Serial.println(analogRead(lightPin));      // Write the value of the photoresistor to the serial monitor.

  int appValue = Serial.read();
  if(appValue>0) choose = appValue;           // Assign the value for the current game from the interface
  
  if (irrecv.decode(&results)){               // Assign the value for the current game from the remote control
    if (results.value==0x56EF334B)  choose=1;
    if (results.value==0x528A5222)  choose=2;

    irrecv.resume(); // receive the next value    
    }
    
  if (digitalRead(button1) == LOW) {           // Assign the value for the current game from the buttons
    choose=1; 
    //debouncing software
    delay(200);
    }
  if (digitalRead(button2) == LOW) { 
    choose=2;
    //debouncing software
    delay(200);
    }


  while (choose<1 || choose>2) {
    choose = Serial.read();                     // Assign the value for the current game from the interface
    
    if (irrecv.decode(&results)){               // Assign the value for the current game from the remote control
      if (results.value==0x56EF334B)  choose=1;
      if (results.value==0x528A5222)  choose=2;
  
      irrecv.resume(); // receive the next value    
      }
      
    if (digitalRead(button1) == LOW) {           // Assign the value for the current game from the buttons
      choose=1; 
      //debouncing software
      delay(200);
      }
    if (digitalRead(button2) == LOW) { 
      choose=2;
      //debouncing software
      delay(200);
      }
    }

    //Serial.println("Press "Reset" button for rebooting");
    switch (choose) {
      case 1:
        game1();break;
      case 2:
        game2();break;
        }
    servo.write(0);                               // Set the servo at 0 degrees
}


void game1() {
  for (int i=5; i<11; i++) {
      if ((i%2)==0) digitalWrite(i,HIGH);
      else digitalWrite(i,LOW);
    }
  delay(100);  
  for (int i=5; i<11; i++) {
    if ((i%2)==0) digitalWrite(i,LOW);
    else digitalWrite(i,HIGH); 
    }
  delay(100);
}


void game2() {
  for (int i=5;i<8;i++) {
    digitalWrite(i,HIGH);
    delay(50); 
    }
  setColor(255, 0, 0);
  delay(100);
  setColor(0, 255, 0);
  delay(100);
  setColor(0, 0, 255);
  delay(100);
  for (int i=7;i>4;i--) {
    digitalWrite(i,LOW);
    delay(50); 
    } 
  setColor(0, 255, 255);
  delay(50);
  setColor(255, 255, 255);
}


void setColor( int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

