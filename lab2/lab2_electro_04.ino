
const int POT_INPUT = 0;

void setup() {
  // Setup the serial speed.
  Serial.begin(9600);
}

void loop() {

  // Read the value from the POT-meter
  int potValue = analogRead(POT_INPUT);

  // Print the value to the serial monitor
  Serial.println(potValue);

  delay(1000);

}
