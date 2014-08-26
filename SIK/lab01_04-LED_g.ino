

const int ledPin = 9;
const int MAX_BRIGHTNESS = 255; // Maximum brightness

void setup()
{

  pinMode(ledPin, OUTPUT);

}

void loop()
{

  digitalWrite(ledPin, HIGH);

  // Time to delay between every change in brightness
  // to make the fading last 4 sekonds.
  float step_delay = 4000 / MAX_BRIGHTNESS;

  for(int i=0; i<=MAX_BRIGHTNESS; i++)
  {
    analogWrite(ledPin, MAX_BRIGHTNESS-i);
    delay(step_delay);
  }

  delay(1000);

}

