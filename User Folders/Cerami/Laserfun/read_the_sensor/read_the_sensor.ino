
int sensorPin = A0;    // select the input pin for the potentiometer
double sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
Serial.begin(9600);}

void loop() {
  // put your main code here, to run repeatedly:
sensorValue = analogRead(sensorPin);
Serial.println(sensorValue);

}
