

const int ledPin = 9;
const int MAX_BRIGHTNESS = 255; // Maximum brightness

void setup()
{

  pinMode(ledPin, OUTPUT);

}

void loop()
{

  // Set the LED to 20% of maximum brightness.
  analogWrite(ledPin, 0.20 * MAX_BRIGHTNESS);

  delay(1000);

  // Turn it off.
  digitalWrite(ledPin, 0);

  delay(1000);

}

