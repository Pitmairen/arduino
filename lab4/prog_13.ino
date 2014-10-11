

const int BUTTON_PIN = 4;

const int LED_PIN_RED = 10;
const int LED_PIN_YELLOW = 9;
const int LED_PIN_GREEN = 8;


//The various state this program can handle:
const int STATE_IDLE = 0;
const int STATE_TURNING_RED = 1;
const int STATE_STOPPING_CARS = 2;
const int STATE_TURNING_GREEN = 3;

int currentState = STATE_IDLE;

// Store the current timerValue. The value is in milliseconds.
//Used to calculate the time between two time checks.
unsigned long timerValue = 0;


void setup() {

  pinMode(LED_PIN_YELLOW, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);

  // Setup serial connection
  Serial.begin(9600);


  // Set the traffic ligts to the current state (idle)
  setTrafficLights(currentState);

}

void loop() {

  // Handle each state
  switch (currentState) {
    case STATE_IDLE:
      handleStateIdle();
      break;
    case STATE_TURNING_RED:
      handleStateTurningRed();
      break;
    case STATE_TURNING_GREEN:
      handleStateTurningGreen();
      break;
    case STATE_STOPPING_CARS:
      handleStateStoppingCars();
      break;
  }
}


/*
Handles the idle state.
Only the green light should be on in this state.
It should be in this state until the button is pressed.
*/
void handleStateIdle()
{

  if (isButtonPressed(BUTTON_PIN)) {
    setTrafficLights(STATE_TURNING_RED);
    setCurrentState(STATE_TURNING_RED);
    resetTimer();
  }
}

/*
Handles the turning red state.
In this state only the yellow light should be on.
It should be in this state for 2 seconds before it continues to
the stopping car state.
*/
void handleStateTurningRed()
{

  if (timerHasPassed(2000)){
    setTrafficLights(STATE_STOPPING_CARS);
    setCurrentState(STATE_STOPPING_CARS);
    resetTimer();
  }
}

/*
Handles the stopping car state.
In this state only the red light should be on.
It should be on for 5 seconds before it continues to the
Turning green state.
*/
void handleStateStoppingCars()
{

  if (timerHasPassed(5000)){
    setTrafficLights(STATE_TURNING_GREEN);
    setCurrentState(STATE_TURNING_GREEN);
    resetTimer();
  }

}


/*
Handles the turning green state.
In this state both the red and the yellow light
should be on. It should be in this state in 1 second
before it continues to the idle state.
*/
void handleStateTurningGreen()
{

  if (timerHasPassed(1000)){
    setTrafficLights(STATE_IDLE);
    setCurrentState(STATE_IDLE);
  }
}



/*
Light up the correct LEDs for the specified state.
*/
void setTrafficLights(int state)
{

  // Turn off all the lights
  turnLedOff(LED_PIN_GREEN);
  turnLedOff(LED_PIN_YELLOW);
  turnLedOff(LED_PIN_RED);

  // Turn on the correct lights for each state
  switch(state)
  {
    case STATE_IDLE:
      turnLedOn(LED_PIN_GREEN);
      break;
    case STATE_TURNING_RED:
      turnLedOn(LED_PIN_YELLOW);
      break;
    case STATE_STOPPING_CARS:
      turnLedOn(LED_PIN_RED);
      break;
    case STATE_TURNING_GREEN:
      turnLedOn(LED_PIN_RED);
      turnLedOn(LED_PIN_YELLOW);
      break;
  }
}



/*
Set the current state of the program
*/
void setCurrentState(int state)
{

  Serial.print("State changed from ");
  printState(currentState);
  Serial.print(" to ");
  printState(state);
  Serial.println("");

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
  return (millis() - timerValue) >= time;
}


/* Returns true if button connected to pin is pressed */
boolean isButtonPressed(int pin)
{
  return digitalRead(pin) == HIGH;
}


/* Returns the string representation of the state */
const char* stateToString(int state)
{
  switch(state)
  {
     case STATE_IDLE:
       return "IDLE";
     case STATE_TURNING_RED:
       return "TURNING_RED";
     case STATE_TURNING_GREEN:
       return "TURNING_GREEN";
     case STATE_STOPPING_CARS:
       return "STOPPING_CHARS";
     default:
       return "UNKNOWN STATE";
  }
}

/* Prints the string representation of state as a string to the serial monitor */
void printState(int state)
{
   Serial.print(stateToString(state));
}

void turnLedOn(int pin)
{
  digitalWrite(pin, HIGH);
}

void turnLedOff(int pin)
{
  digitalWrite(pin, LOW);
}


