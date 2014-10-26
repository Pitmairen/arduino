
#include <LiquidCrystal.h>

// Constants refering to the arduino pins
const int BUTTON_PIN_1 = 9;
const int BUTTON_PIN_2 = 8;
const int LED_PIN = 10;
const int TEMP_SENSOR_PIN = A0;

// States for the current button state
const int BUTTONS_IDLE = 0;
const int BUTTON_1_PRESSED = 1;
const int BUTTON_2_PRESSED = 2;

// constant for the degrees symbol. The value of byte(0) is chosen
// based on the documentation for the lcd library. 0 Means the first
// self defined symbol.
const byte DEGREES_SYMBOL = byte(0);


// Constant to represent various timers. Each constant will be a
// index to the timerValue in the timers array below:
const int TEMP_UPDATE_TIMER = 0; // Timer for the temperature update interval
const int BUTTONS_TIMER = 1; // Timer for autorepeat

// Array used to store the timerValues.
unsigned long timers[2]; // The size must be the same as the number of timers

// Temperature limit before the alert LED should
// be turned on in degrees Celcius
float alertLimit = 20.0;

// The current temperature read from the sensor in degrees Celcius
float degreesC = 0.0;

// The state of the buttons
int buttonState = BUTTONS_IDLE;

// Delay before the alertLimit should be automatically incremented or
// decremented when the buttons are pushed and hold down longer than this limit.
// When this is 0 the auto repeat is not active. So this value has to be set
// to a value above 0 for the auto repeat to be activated.
int autoRepeat = 0;

// The lcd object
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {

  pinMode(LED_PIN, OUTPUT);

  // Setup the lcd and specify the number of columns and lines.
  lcd.begin(16, 2);
  lcd.clear();

  // Data for the degrees symbol. Used with lcd.createChar to be able to
  // print the degrees symbol.
  byte degrees_symbol_data[8] = {
    B00111,
    B00101,
    B00111,
    B00000,
    B00000,
    B00000,
    B00000,
  };

  // create the degrees symbol.
  lcd.createChar(DEGREES_SYMBOL, degrees_symbol_data);


  resetAllTimers();
  resetAutoRepeat();

  // Update the display with initial values
  updateDisplayLimit(alertLimit);
  updateDisplayTemperature(readCelcius(TEMP_SENSOR_PIN));
}


void loop() {

  // Only update the temperature every 2 seconds to prevent
  // the value from constantly fluctuating
  if(timerHasPassed(TEMP_UPDATE_TIMER, 2000)){

    float degreesC = readCelcius(TEMP_SENSOR_PIN);

    if(degreesC > alertLimit){
      digitalWrite(LED_PIN, HIGH);
    }
    else{
      digitalWrite(LED_PIN, LOW);
    }

    updateDisplayTemperature(degreesC);
    resetTimer(TEMP_UPDATE_TIMER);


  }


  if(isButtonPressed(BUTTON_PIN_1) || isButtonPressed(BUTTON_PIN_2))
  {
    // One of the buttons are now pushed down.

    // If previously no button was pushed
    if(buttonStateIs(BUTTONS_IDLE)){

      resetTimer(BUTTONS_TIMER);
      resetAutoRepeat();

      // Set which button is being pushed
      if(isButtonPressed(BUTTON_PIN_1))
        setButtonState(BUTTON_1_PRESSED);
      else
        setButtonState(BUTTON_2_PRESSED);

    }

    // If 20 ms has passed since the button was pushed and autorepeat has not
    // been set, we register a single push on the current button.
    // A delay of 20 ms is used to prevent accidental triggering of the
    // buttons.
    else if(timerHasPassed(BUTTONS_TIMER, 20) && !isAutoRepeatActivated()){

       // increment or decrement depending on the button pushed.
       if(buttonStateIs(BUTTON_1_PRESSED)){
         incrementAlarmLimit();
       }else{
         decrementAlarmLimit();
       }

       // Set the autorepeat to 500ms. If the button is not released before the
       // 500 ms has passed the autorepeat will activate.
       setAutoRepeat(500);
       resetTimer(BUTTONS_TIMER);
    }
    else if(isAutoRepeatActivated() && timerHasPassed(BUTTONS_TIMER, autoRepeat)){

       // If autorepeat is activated and the autoRepeat delay has passed
       // we automatically increment or decrement the alart limit.
       if(buttonStateIs(BUTTON_1_PRESSED)){
         incrementAlarmLimit();
       }else{
         decrementAlarmLimit();
       }

       // Make delay before the next auto repeat smaller so that the
       // repeat happens at a faster rate.
       setAutoRepeat(120);
       resetTimer(BUTTONS_TIMER);
    }


    updateDisplayLimit(alertLimit);

  }
  else{

    // If no buttons are pushed the button state is IDLE
    setButtonState(BUTTONS_IDLE);
  }

}


/*
 Updates the temperature in the lcd display
*/
void updateDisplayTemperature(float degreesC)
{

  // Print the current temperature in celcius in the upper
  // right corner of the screen
  lcd.setCursor(calculateCursorPosition(degreesC)-3, 0);
  lcd.print("T: ");
  lcd.print(degreesC,1);
  lcd.write(DEGREES_SYMBOL);
  lcd.print("C");

  // Print the current temperature in farenheit in the lower
  // right corner of the screen.
  float degreesF = convertToFarenheit(degreesC);
  lcd.setCursor(calculateCursorPosition(degreesF), 1);
  lcd.print(degreesF, 1);
  lcd.write(DEGREES_SYMBOL);
  lcd.print("F");

}


/*
 Updates the temperature limit in the lcd display
*/
void updateDisplayLimit(float limit)
{

  lcd.setCursor(0, 0);
  lcd.print("Lim:");
  // Print the alert limit in the lower left corner.
  lcd.setCursor(0, 1);
  lcd.print(limit, 1);
  lcd.write(DEGREES_SYMBOL);
  lcd.print("C ");

}



/*
  Calculates the starting column for the cursor to
  make the number with the unit fit on the right side of the display.

  24'C => (total cols on lcd) - (cols needed for number + unit) = 16 - 4 = 10;
*/
int calculateCursorPosition(float number)
{
  if(number >= 10 && number < 100)
    return 10;
  else if(number < 10 && number >= 0)
    return 11;
  else if(number >= 1000 || number <= -100)
    return 8;
  else if(number >= 100 || number <= -10)
    return 9;
  else
    return 10;
}


/*
  Increments the limit by 0.5
*/
float incrementAlarmLimit()
{
  alertLimit = constrain(alertLimit + 0.5, -99, 999);
  return alertLimit;
}

/*
  Decrements the limit by 0.5
*/
float decrementAlarmLimit()
{
  alertLimit = constrain(alertLimit - 0.5, -99, 999);
  return alertLimit;
}

/*
  Resets and deactivated the auto repeat
*/
void resetAutoRepeat()
{
  autoRepeat = 0;
}

/*
  Checks if the auto repeat is activated
*/
boolean isAutoRepeatActivated()
{
  return autoRepeat > 0;
}

/*
  Activates and sets the auto repeat delay
*/
void setAutoRepeat(int delay)
{
  autoRepeat = delay;
}


/*
  Sets the current button state
*/
void setButtonState(int state)
{
  buttonState = state;
}

/*
  Checks if the current button is equal to "state"
*/
boolean buttonStateIs(int state)
{
  return buttonState == state;
}

/*
  Checks if a button in pushed
*/
boolean isButtonPressed(int pin)
{
  return digitalRead(pin) == HIGH;
}

/*
  Reads the voltage from a pin
*/
float getVoltage(int pin)
{
  // Convert the value from analogRead to the real voltage
  return (analogRead(pin) * (5.0/1023));
}

/*
  Reads the current temperatur from a sensor and returns the
  value in calcius
*/
float readCelcius(int pin)
{

  float degreesC = (getVoltage(pin) - 0.5) * 100.0;
  return constrain(degreesC, -273, 999);
}

/*
  Converts from degrees Celcius to Farenheit
*/
float convertToFarenheit(float degreesC)
{
   return degreesC * (9.0/5.0) + 32.0;
}

/*
  Resets the timer represented by timerId
*/
unsigned long resetTimer(int timerId)
{
  return timers[timerId] = millis();
}

/*
  Reset all the defined timers
*/
unsigned long resetAllTimers()
{
  int timerCount = sizeof(timers)/sizeof(unsigned long);
  for(int i=0; i<timerCount; ++i){
    timers[i] = millis();
  }
}

/*
  Checks if a timer has passed a limit
*/
boolean timerHasPassed(int timerId, int limit)
{
  return (millis() - timers[timerId]) > limit;
}


