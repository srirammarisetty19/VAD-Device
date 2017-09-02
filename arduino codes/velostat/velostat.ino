// Analog input pin that the Velostat is connected to
const int analogInPin = A0;  

// value read from the Velostat
int sensorValue = 0;        

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  //init Analog Pin as PULLUP
  //(meaning it sends out voltage)
  digitalWrite(analogInPin, HIGH);

}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  // print the results to the serial monitor:
  //Serial.print("sensor = " );
  Serial.println(sensorValue);
  delay(1000);
}
