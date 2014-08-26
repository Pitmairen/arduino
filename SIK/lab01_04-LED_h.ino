

const int ledPin = 9;
const int MAX_BRIGHTNESS = 255;

void setup()
{

  pinMode(ledPin, OUTPUT);

}

void loop()
{

  digitalWrite(ledPin, HIGH);

  // Time to delay between every change in brightness
  // to make the fading last 4.5 sekonds.
  float step_delay = 4500 / MAX_BRIGHTNESS;

  for(int i=0; i<=MAX_BRIGHTNESS; i++)
  {
    analogWrite(ledPin, MAX_BRIGHTNESS-i);
    delay(step_delay);
  }

  step_delay = 1500 / MAX_BRIGHTNESS;

  for(int i=1; i<=MAX_BRIGHTNESS; i++)
  {
    analogWrite(ledPin, i);
    delay(step_delay);
  }


}

