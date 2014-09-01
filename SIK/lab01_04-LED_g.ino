

const int ledPin = 9;
const int MAX_BRIGHTNESS = 255; // Maximum brightness

void setup()
{

  pinMode(ledPin, OUTPUT);

}

void loop()
{

  // Set the led to maximum brightness.
  digitalWrite(ledPin, HIGH);

  // Calculate the time to delay between every change in brightness
  // to make the fading last 4 seconds.
  int step_delay = 4000 / MAX_BRIGHTNESS;

  for(int i=0; i<=MAX_BRIGHTNESS; i++)
  {
    // Lower the brightness by one each time through the loop. Starting at
    // maximum brightness and ending at 0.
    analogWrite(ledPin, MAX_BRIGHTNESS-i);
    delay(step_delay);
  }

  delay(1000);

}

