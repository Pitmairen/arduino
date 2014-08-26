

const int ledPin = 9;
const int MAX_BRIGHTNESS = 255; // Maximum brightness

void setup()
{

  pinMode(ledPin, OUTPUT);

}

void loop()
{


  analogWrite(ledPin, 0.20 * MAX_BRIGHTNESS);

  delay(1000);

  digitalWrite(ledPin, 0);

  delay(1000);

}

