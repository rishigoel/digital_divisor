#include <Adafruit_MotorShield.h>

// TODO change these:
const int photoResistor1Pin = 1;
const int photoResistor2Pin = 2;
const int userResistorPin = 5;
const int limitSwitch1Pin = 3;
const int limitSwitch2Pin = 4;
const int stoppingValue = 500;
const int motorSpeed = 150;

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
  int difference = pr2 - pr1;
  return difference;
}

int getUserResistance() {
  return analogRead(userResistorPin);
}

// TODO: Map difference to positioning and operate motor
void moveVisor(int difference) {
  int userResistance = getUserResistance();
  Serial.print("difference: "+difference);
  Serial.print("user resistance: " + userResistance);
  if (userResistance <= stoppingValue) {
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
    stopMovingVisor();
  }
  delay(100);
}
