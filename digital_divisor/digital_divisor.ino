#include <Wire.h>
#include <Adafruit_MotorShield.h>

// TODO change these:
const int photoResistor1Pin = A0;
const int photoResistor2Pin = A1;
const int userResistorPin = A2; //need a new way of doing user resistance
const int limitSwitch1Pin = 3;
const int limitSwitch2Pin = 4;
const int stoppingValue = 500;
const int motorSpeed = 100;
const int equivalentLight = 30;
const int resistorOffset = 50; //allows us to manage differences in resistor construction

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
 
void setup() {
  Serial.begin(9600);
  pinMode(photoResistor1Pin, INPUT);
  pinMode(photoResistor2Pin, INPUT);
  pinMode(userResistorPin, INPUT);
  AFMS.begin();  // create with the default frequency 1.6KHz -> change by passing in frequency as parameter in Hz
  myMotor->setSpeed(motorSpeed);
}

int getResistanceDifference() {
  int pr1 = analogRead(photoResistor1Pin);
  int pr2 = analogRead(photoResistor2Pin);
  int difference = pr2 - pr1 - resistorOffset;
  return difference;
}

int getUserResistance() {
  return analogRead(userResistorPin);
}

// TODO: Map difference to positioning and operate motor
void moveVisor(int difference) {
  int userResistance = getUserResistance();
  Serial.print("difference = ");
  Serial.println(difference);
  if (abs(difference+userResistance) <= equivalentLight) {
    stopMovingVisor();
  } else if (difference > 0) {
    myMotor->run(FORWARD);
  } else {
    myMotor->run(BACKWARD);
  }
}

void stopMovingVisor() {
  myMotor->run(RELEASE);
}

void loop() {
  // put your main code here, to run repeatedly:
  moveVisor(getResistanceDifference());
  delay(50);
  if (digitalRead(limitSwitch1Pin)==LOW || digitalRead(limitSwitch2Pin)==LOW) {
    //stopMovingVisor();
  }
  delay(100);
}
