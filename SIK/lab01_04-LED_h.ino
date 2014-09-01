

const int ledPin = 9;
const int MAX_BRIGHTNESS = 255;

void setup()
{

  pinMode(ledPin, OUTPUT);

}

void loop()
{

  digitalWrite(ledPin, HIGH);

  // Calculate the time to delay between every change in brightness
  // to make the fading last 4 seconds.
  int step_delay = 4500 / MAX_BRIGHTNESS;

  for(int i=0; i<=MAX_BRIGHTNESS; i++)
  {
    // Lower the brightness by one each time through the loop. Starting at
    // maximum brightness and ending at 0.
    analogWrite(ledPin, MAX_BRIGHTNESS-i);

    delay(step_delay);
  }

  // Calculate the time to delay between every change in brightness
  // to make the fading last 1.5 seconds.
  step_delay = 1500 / MAX_BRIGHTNESS;

  for(int i=1; i<=MAX_BRIGHTNESS; i++)
  {
    // Lower the brightness by one each time through the loop. Starting at
    // maximum brightness and ending at 0.
    analogWrite(ledPin, i);

    delay(step_delay);
  }


}

