// TODO change these:
const int photoResistor1Pin = 1;
const int photoResistor2Pin = 2;
const int limitSwitch1Pin = 3;
const int limitSwitch2Pin = 4;
 
void setup() {
  Serial.begin(9600);
  pinMode(photoResistor1Pin, OUTPUT);
  pinMode(photoResistor2Pin, OUTPUT);

}

int getResistanceDifference() {
  int pr1 = analogRead(photoResistor1Pin);
  int pr2 = analogRead(photoResistor2Pin);
  int difference = pr2 - pr1;
  return difference;
}

// TODO: Map difference to positioning and operate motor
void moveVisor(int difference) {
  
}

void stopMovingVisor() {
  
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
