#include <Servo.h>

// ---------------------------------
// GLOBALS -------------------------
// ---------------------------------

// Servo globals
Servo petservo; // initializes servo object

// Ultrasonic sensor globals
static int trigPin = 12; // defines pins for ultrasonic sensor
static int echoPin = 11;

// > Also define servo pin
static int servoPin = 9;

static float distanceThresholdOfFood = 16.0; // In cm

// ---------------------------------
// SETUP ---------------------------
// ---------------------------------
void setup() {
  //// Servo setup
  petservo.attach(servoPin); // attaches servo input in pin 9 to defined petservo
  
  //// Ultrasonic sensor setup
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT); // sets the trigPin as an Output
  
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

// ---------------------------------
// UTILITY->DISTANCE ---------------
// ---------------------------------
long getDistanceCm() {
  
  //// Ultrasonic Sensor loop  
  digitalWrite(trigPin, LOW); // clears trigPin and ensures clean HIGH pulse
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return (duration/2.0) / 29.1; // converts time into distance traveled
}

bool gateShouldBeOpen() {
  return getDistanceCm() > distanceThresholdOfFood;
}

// ---------------------------------
// LOOP ----------------------------
// ---------------------------------
void loop() {
  
  //// Servo loop
  Serial.print(getDistanceCm());
  Serial.print("cm - Servo loop");
  
  if (gateShouldBeOpen()) {
    petservo.write(120); // opens food gate for 5 seconds
    delay(5000);
   
     while (gateShouldBeOpen()) {
      petservo.write(96); // pauses gate
      delay(1000); // repeat 1 second delay until less than 16 cm distance from top of food
    
      Serial.print(getDistanceCm());
      Serial.print("cm - While loop ");
     }
     
    petservo.write(70); // closes gate for 5 seconds
    delay(5000);
  }
  
  Serial.print(getDistanceCm());
  Serial.print("cm - before minute pause ");
  
  petservo.write(96); // pauses gate for 60 seconds
  delay(6000);
  
  Serial.print(getDistanceCm());
  Serial.print("cm - after minute pause ");
}
  
  






