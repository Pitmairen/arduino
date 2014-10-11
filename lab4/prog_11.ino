
const int LED_PIN = 6;
const int BUTTON_PIN = 8;

// The various state this program can handle:
const int STATE_IDLE = 0;
const int STATE_LED_ON = 1;

int currentState = STATE_IDLE;

// Store the current timerValue. The value is in milliseconds.
//Used to calculate the time between two time checks.
unsigned long timerValue = 0;


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
    setCurrentState(STATE_IDLE);
  }
}



void setCurrentState(int state)
{
  currentState = state;
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

