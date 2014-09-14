
const int POT_INPUT = 0;
const int RESISTOR_PIN = 9;

void setup() {
  // Setup the serial speed
  Serial.begin(9600);
  // Set resistorpin to output mode
  pinMode(RESISTOR_PIN, OUTPUT);
}

void loop() {

  int potValue = analogRead(POT_INPUT);

  // The value from the potmeter is in the range 0-1023, but the value that
  // we write to the resistor pin must be in the range 0-255.
  // The builtin map function will convert the potValue from the 0-1023 range
  // to the 0-255 range suitable for the resistor pin output.
  int outValue = map(potValue, 0, 1023, 0, 255);

  // Print the potValue and the converted value to the serial monitor.
  Serial.print(potValue);
  Serial.print(" - ");
  Serial.println(outValue);

  analogWrite(RESISTOR_PIN, outValue);

  delay(1000);

}
