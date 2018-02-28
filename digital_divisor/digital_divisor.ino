// TODO change these:
const int photoResistor1Pin = 1;
const int photoResistor2Pin = 2;
 
void setup() {
  Serial.begin(9600);
  pinMode(photoResistor1Pin, OUTPUT);
  pinMode(photoResistor2Pin, OUTPUT);

}

int getResistanceDifference() {
  int pr1 = analogRead(photoResistor1Pin);
  int pr2 = analogRead(photoResistor2Pin);
  int difference = pr2 - p1;
  return difference;
}

// TODO: Map difference to positioning and operate motor
void moveVisor(int difference) {
  
}

void loop() {
  // put your main code here, to run repeatedly:
  moveVisor(getResistanceDifference());
  delay(100);
}
