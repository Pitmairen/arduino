
const int outVoltagePin = A0;
const int diodeVoltagePin = A1;

// The resistans of the series resistor in kOhm
const float seriesResistor = 0.236;


void setup() {

  // Setup serial connection
  Serial.begin(9600);

}


void loop() {

  float outVoltage = readVoltage(outVoltagePin);
  float diodeVoltage = readVoltage(diodeVoltagePin);

  float current = calculateCurrent(outVoltage - diodeVoltage, seriesResistor);

  Serial.print("Current: ");
  Serial.print(current);
  Serial.print(" - Voltage: ");
  Serial.println(diodeVoltage);


  delay(1000);
}


// Calculate current from voltagedrop and resistance
float calculateCurrent(float voltageDrop, float resistance)
{
  return voltageDrop / resistance;
}

float readVoltage(int pin)
{
  // Convert the value from analogRead into the real voltage.
  return analogRead(pin) * (5.0/1023.0);
}




