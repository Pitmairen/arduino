
const int ledPins[] = {2,3,4,5,6,7,8,9};
const int LED_COUNT = sizeof(ledPins)/sizeof(int);
const int POT_PIN = A0;

void setup()
{
  // Loop through all the pins and set them to
  // OUTPUT mode
  for(int index = 0; index <= 7; index++)
  {
    pinMode(ledPins[index],OUTPUT);
  }

}


void loop()
{


  int potValue = analogRead(POT_PIN);

  // Divide the value from the POT by 170 and use the result to choose
  // which animation to run. Use constrain to remove the trim off the 6 which
  // we get when the potValue is close to 1023.
  switch(constrain(potValue/170, 0, 5))
  {
    case 0:
      oneAfterAnotherNoLoop();
      break;
    case 1:
      myCoolAnimation();
      break;
    case 2:
      oneOnAtATime();
      break;
    case 3:
      pingPong();
      break;
    case 4:
      marquee();
      break;
    case 5:
      randomLED();
      break;
  }

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


/*
oneAfterAnotherNoLoop()

This function will light one LED, delay for delayTime, then light
the next LED, and repeat until all the LEDs are on. It will then
turn them off in the reverse order.

This function does NOT use a for() loop. We've done it the hard way
to show you how much easier life can be when you use for() loops.
Take a look at oneAfterAnotherLoop() further down, which does
exactly the same thing with much less typing.
*/

void oneAfterAnotherNoLoop()
{
  int delayTime = 100; // time (milliseconds) to pause between LEDs
                       // make this smaller for faster switching

  // turn all the LEDs on:

  digitalWrite(ledPins[0], HIGH);  //Turns on LED #0 (pin 2)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[1], HIGH);  //Turns on LED #1 (pin 3)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[2], HIGH);  //Turns on LED #2 (pin 4)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[3], HIGH);  //Turns on LED #3 (pin 5)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[4], HIGH);  //Turns on LED #4 (pin 6)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[5], HIGH);  //Turns on LED #5 (pin 7)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[6], HIGH);  //Turns on LED #6 (pin 8)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[7], HIGH);  //Turns on LED #7 (pin 9)
  delay(delayTime);                //wait delayTime milliseconds

  // turn all the LEDs off:

  digitalWrite(ledPins[7], LOW);   //Turn off LED #7 (pin 9)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[6], LOW);   //Turn off LED #6 (pin 8)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[5], LOW);   //Turn off LED #5 (pin 7)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[4], LOW);   //Turn off LED #4 (pin 6)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[3], LOW);   //Turn off LED #3 (pin 5)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[2], LOW);   //Turn off LED #2 (pin 4)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[1], LOW);   //Turn off LED #1 (pin 3)
  delay(delayTime);                //wait delayTime milliseconds
  digitalWrite(ledPins[0], LOW);   //Turn off LED #0 (pin 2)
  delay(delayTime);                //wait delayTime milliseconds
}


/*
oneAfterAnotherLoop()

This function does exactly the same thing as oneAfterAnotherNoLoop(),
but it takes advantage of for() loops and the array to do it with
much less typing.
*/

void oneAfterAnotherLoop()
{
  int index;
  int delayTime = 100; // milliseconds to pause between LEDs
                       // make this smaller for faster switching

  // Turn all the LEDs on:

  // This for() loop will step index from 0 to 7
  // (putting "++" after a variable means add one to it)
  // and will then use digitalWrite() to turn that LED on.

  for(index = 0; index <= 7; index++)
  {
    digitalWrite(ledPins[index], HIGH);
    delay(delayTime);
  }

  // Turn all the LEDs off:

  // This for() loop will step index from 7 to 0
  // (putting "--" after a variable means subtract one from it)
  // and will then use digitalWrite() to turn that LED off.

  for(index = 7; index >= 0; index--)
  {
    digitalWrite(ledPins[index], LOW);
    delay(delayTime);
  }
}


/*
oneOnAtATime()

This function will step through the LEDs,
lighting only one at at time.
*/

void oneOnAtATime()
{
  int index;
  int delayTime = 100; // milliseconds to pause between LEDs
                       // make this smaller for faster switching

  // step through the LEDs, from 0 to 7

  for(index = 0; index <= 7; index++)
  {
    digitalWrite(ledPins[index], HIGH);  // turn LED on
    delay(delayTime);                    // pause to slow down
    digitalWrite(ledPins[index], LOW);   // turn LED off
  }
}


/*
pingPong()

This function will step through the LEDs,
lighting one at at time in both directions.
*/

void pingPong()
{
  int index;
  int delayTime = 100; // milliseconds to pause between LEDs
                       // make this smaller for faster switching

  // step through the LEDs, from 0 to 7

  for(index = 0; index <= 7; index++)
  {
    digitalWrite(ledPins[index], HIGH);  // turn LED on
    delay(delayTime);                    // pause to slow down
    digitalWrite(ledPins[index], LOW);   // turn LED off
  }

  // step through the LEDs, from 7 to 0

  for(index = 7; index >= 0; index--)
  {
    digitalWrite(ledPins[index], HIGH);  // turn LED on
    delay(delayTime);                    // pause to slow down
    digitalWrite(ledPins[index], LOW);   // turn LED off
  }
}


/*
marquee()

This function will mimic "chase lights" like those around signs.
*/

void marquee()
{
  int index;
  int delayTime = 200; // milliseconds to pause between LEDs
                       // Make this smaller for faster switching

  // Step through the first four LEDs
  // (We'll light up one in the lower 4 and one in the upper 4)

  for(index = 0; index <= 3; index++) // Step from 0 to 3
  {
    digitalWrite(ledPins[index], HIGH);    // Turn a LED on
    digitalWrite(ledPins[index+4], HIGH);  // Skip four, and turn that LED on
    delay(delayTime);                      // Pause to slow down the sequence
    digitalWrite(ledPins[index], LOW);     // Turn the LED off
    digitalWrite(ledPins[index+4], LOW);   // Skip four, and turn that LED off
  }
}


/*
randomLED()

This function will turn on random LEDs. Can you modify it so it
also lights them for random times?
*/

void randomLED()
{
  int index;
  int delayTime;

  // The random() function will return a semi-random number each
  // time it is called. See http://arduino.cc/en/Reference/Random
  // for tips on how to make random() even more random.

  index = random(8);	// pick a random number between 0 and 7
  delayTime = 100;

  digitalWrite(ledPins[index], HIGH);  // turn LED on
  delay(delayTime);                    // pause to slow down
  digitalWrite(ledPins[index], LOW);   // turn LED off
}


