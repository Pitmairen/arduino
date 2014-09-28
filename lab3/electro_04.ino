
const int potPin = A0;


void setup() {

  // Setup the serial connection
  Serial.begin(9600);

}



void loop() {

  float potVoltage = readVoltage(potPin);

  Serial.print("Potmeter Voltage: ");
  Serial.println(potVoltage);

  delay(1000);

}


float readVoltage(int pin)
{
  // Convert the value from analogRead into the real voltage.
  return analogRead(pin) * (5.0/1023.0);
}


