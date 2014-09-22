
const int flexPin = A0;


void setup() {
  // Setup the serial connection
  Serial.begin(9600);
}

void loop() {

  // Read the value from the flex-sensor and store i in flexValue.
  int flexValue = analogRead(flexPin);

  // Print the value in flexValue to the serial monitor.
  Serial.print("Sensor value: ");
  Serial.println(flexValue);

  delay(1000);

}
