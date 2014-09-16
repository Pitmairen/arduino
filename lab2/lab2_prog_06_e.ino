
const int ledPins[] = {2,3,4,5,6,7,8,9};

const int LED_COUNT = sizeof(ledPins)/sizeof(int);

void setup()
{
  // Loop through all the pins and set them to
  // OUTPUT mode
  for(int index = 0; index < LED_COUNT; index++)
  {
    pinMode(ledPins[index], OUTPUT);
  }
}


void loop()
{
  // Start my animation:
  myCoolAnimation();
}



// Turn on and off one LED at a time from both sides, when it reaches the middle
// stop and blink the two middle LEDS before continuing turning on and off one LED
// at the time until reaching the end.
void myCoolAnimation()
{
  for(int i=0; i < LED_COUNT; i++)
  {
    // Turn on pin nr. "i" from left side.
    digitalWrite(ledPins[i], HIGH);
    // Turn on pin nr "i" from the right side
    // The first round will be:
    // LED_COUNT - 1 - i = 8 - 1 - 0 = 7
    digitalWrite(ledPins[LED_COUNT-1-i], HIGH);


    // If this is not the first round, we turn
    // off the LEDs that was turned on in the previous round.
    if(i >= 1){
      // Turn off the previous LED from the left
      digitalWrite(ledPins[i-1], LOW);
      // Turn off the previous LED from the right
      digitalWrite(ledPins[LED_COUNT-i], LOW);
    }


    // Set a delay for the first 4 rounds
    if(i<4)
      delay(150);
    // Then go a little quicker on the way back
    else
      delay(50);

    if(i == 4){
      // We have reached the two middle LEDS

      // Blink the two middle LEDs 5 times.
      for(int j=0; j<5; j++)
      {
        // Turn on the first middel LED from the left
        digitalWrite(ledPins[LED_COUNT-1-i], HIGH);
        // Turn on the first middel LED from the right
        digitalWrite(ledPins[i], HIGH);

        // Keep them on for a little while
        delay(50);

        // Then turn them off
        digitalWrite(ledPins[LED_COUNT-1-i], LOW);
        digitalWrite(ledPins[i], LOW);
        delay(50);
      }
    }

  }


}


