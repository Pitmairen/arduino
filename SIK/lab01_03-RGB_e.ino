
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;


void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}


void loop()
{
  mainColorsForLoop();
}


void mainColorsForLoop()
{

  // All LEDs off
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  delay(1000);

  // Red(0), Green(256) and Blue(512)
  for(int i=0; i<3; i++)
  {
    showRGB(i*256);
    delay(1000);
  }

  // Yellow(128), Cyan(384) and Purple(640)
  // These colors should be the same as in the original mainColors() function,
  // only with half the brightness because of limitations of the showRGB
  // function.
  for(int i=0; i<3; i++)
  {
    showRGB(128 + i*256);
    delay(1000);
  }


  // All LEDs on (White)
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);

  delay(1000);
}


// The original showRGB function:
void showRGB(int color)
{
  int redIntensity;
  int greenIntensity;
  int blueIntensity;


  // In each of these zones, we'll calculate the brightness
  // for each of the red, green, and blue LEDs within the RGB LED.

  if (color <= 255)          // zone 1
  {
    redIntensity = 255 - color;    // red goes from on to off
    greenIntensity = color;        // green goes from off to on
    blueIntensity = 0;             // blue is always off
  }
  else if (color <= 511)     // zone 2
  {
    redIntensity = 0;                     // red is always off
    greenIntensity = 255 - (color - 256); // green on to off
    blueIntensity = (color - 256);        // blue off to on
  }
  else // color >= 512       // zone 3
  {
    redIntensity = (color - 512);         // red off to on
    greenIntensity = 0;                   // green is always off
    blueIntensity = 255 - (color - 512);  // blue on to off
  }

  // Now that the brightness values have been set, command the LED
  // to those values

  analogWrite(RED_PIN, redIntensity);
  analogWrite(BLUE_PIN, blueIntensity);
  analogWrite(GREEN_PIN, greenIntensity);
}
