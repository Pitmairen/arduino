
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;


int DISPLAY_TIME = 100;


void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}


void loop()
{
  showSpectrum();
}



void showSpectrum()
{
  int x;

  for (x = 0; x <= 768; x++)
  {
    // Reverse the direction from the original. This will go from 768 to 0.
    showRGB(768 - x);
    delay(10);
  }

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
