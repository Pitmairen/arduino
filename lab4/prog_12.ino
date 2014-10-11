
const int LED_PIN = 10;
const int BUTTON_PIN = 4;

// The various state this program can handle:
const int STATE_IDLE = 0;
const int STATE_LED_ON = 1;
const int STATE_LED_BLINKING = 2;

int currentState = STATE_IDLE;

// Store the current timerValue. The value is in milliseconds.
//Used to calculate the time between two time checks.
unsigned long timerValue = 0;

int ledBlinkCount = 0;

void setup() {

  pinMode(LED_PIN, OUTPUT);

}

void loop() {

  // Handle each state
  switch (currentState) {
    case STATE_IDLE:
      handleStateIdle();
      break;
    case STATE_LED_ON:
      handleStateLedOn();
      break;
    case STATE_LED_BLINKING:
      handleStateLedBlinking();
      break;
  }
}


/*
Handles the idle state
*/
void handleStateIdle()
{
  turnLedOff(LED_PIN);
  if (isButtonPressed(BUTTON_PIN)) {
    setCurrentState(STATE_LED_ON);
    resetTimer();
  }
}

/*
Handles the led on state
*/
void handleStateLedOn()
{
  turnLedOn(LED_PIN);
  if (timerHasPassed(2000)){
    setCurrentState(STATE_LED_BLINKING);
    resetLedBlinkCount();
    resetTimer();
  }
}

/*
Handles the led blinking state
*/
void handleStateLedBlinking()
{

  // I could have used a simple loop and turned the led on and off
  // with delays between, but i did it this way to minimize the delay between
  // each time the program goes through the state loop to check for state changes.
  // This has no use in the current code, but it could be usefull later.

  // We only have to do something if it is 150 milliseconds since the
  // last time the led was toggled. Or if this is the first time,
  // then the led should be toggled unaffected by the timer.
  if(ledBlinkCount == 0 || timerHasPassed(150)){

    // If the led has blinked 10 times we are done.
    if(ledHasBlinked(10)){
      setCurrentState(STATE_IDLE);
    }
    else{

      // Toggle the led state and increment the led blink count.
      toggleLedState(LED_PIN);
      ledBlinkCount++;
      resetTimer();
    }
  }


}

/*
Set the current state of the program
*/
void setCurrentState(int state)
{
  currentState = state;
}

/*
Toggles the led on and off. If the led is on
it will be turned off and visa versa.
*/
void toggleLedState(int pin)
{
  digitalWrite(pin, !digitalRead(pin));
}

/*
Reset the current led blink count. The counter is used by the
ledHasBlinked() function to check how many times the led has blinked.
*/
void resetLedBlinkCount()
{
  ledBlinkCount = 0;
}

/*
Check if the led has blinked "count" times since the last call
to resetBlinkCount().
*/
boolean ledHasBlinked(int count)
{
  // Divide the blinkCount by 2 because a blink is counted as off and then on.
  // The counter is incremented one time for each change in state. So by dividing
  // by 2 we get the number of blinks. There is no need to use floats in this calculation
  // because the rounding of the numbers has no effect on the result.
  return (ledBlinkCount/2) >= count;
}

/*
Reset the timer used by the timeHasPassed() function
below to check if a certain time has passed since the last
call to resetTimer();
*/
void resetTimer()
{
  timerValue = millis();
}

/*
Check if time (in milliseconds) has passed since the last
call to resetTimer()
*/
boolean timerHasPassed(unsigned long time)
{
  return (millis() - timerValue) > time;
}

boolean isButtonPressed(int pin)
{
  return digitalRead(pin) == HIGH;
}


void turnLedOn(int pin)
{
  digitalWrite(pin, HIGH);
}

void turnLedOff(int pin)
{
  digitalWrite(pin, LOW);
}

