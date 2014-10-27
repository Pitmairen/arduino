
#include <LiquidCrystal.h>

// Constants refering to the arduino pins
const int BUTTON_PIN_1 = 9;
const int BUTTON_PIN_2 = 8;
const int LED_PIN = 10;
const int TEMP_SENSOR_PIN = A0;


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
// be turned on in degrees Celsius
float alertLimit = 20.0;

// The current temperature read from the sensor in degrees Celsius
float degreesC = 0.0;

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
  updateDisplayTemperature(updateCurrentTemperature(TEMP_SENSOR_PIN));
}


void loop() {

  // Only update the temperature every 2 seconds to prevent
  // the value from constantly fluctuating
  if(timerHasPassed(TEMP_UPDATE_TIMER, 2000)){

    updateCurrentTemperature(TEMP_SENSOR_PIN);
    updateDisplayTemperature(degreesC);
    updateAlertLed(degreesC, alertLimit);
    resetTimer(TEMP_UPDATE_TIMER);

  }


  // Check if one of the buttons are pushed, but not both at the same time.
  if((isButtonPressed(BUTTON_PIN_1) || isButtonPressed(BUTTON_PIN_2)) &&
     !(isButtonPressed(BUTTON_PIN_1) && isButtonPressed(BUTTON_PIN_2)))
  {
    // Only one of the buttons are now pushed down.

    // If 20 ms has passed since the button was pushed and autorepeat has not
    // been set, we register a single push on the current button.
    // A delay of 20 ms is used to prevent accidental triggering of the
    // buttons.
    if(timerHasPassed(BUTTONS_TIMER, 20) && !isAutoRepeatActivated()){

       // increment or decrement depending on the button pushed.
       if(isButtonPressed(BUTTON_PIN_1)){
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
       if(isButtonPressed(BUTTON_PIN_1)){
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
    updateAlertLed(degreesC, alertLimit);

  }
  else{

    // If no buttons are pushed reset the timer and autorepeat to
    // be ready for the next button push.
    resetAutoRepeat();
    resetTimer(BUTTONS_TIMER);
  }


}


/*
 Updates the temperature in the lcd display
*/
void updateDisplayTemperature(float degC)
{

  // Print the current temperature in celsius in the upper
  // right corner of the screen
  // -4 is for the " T: " before the temperature.
  lcd.setCursor(calculateCursorPosition(degC)-4, 0);
  // The space preceding the T is used to remove the letter that will be left
  // if the number of digits in the temperature decreases by one.
  lcd.print(" T: ");
  lcd.print(degC,1);
  lcd.write(DEGREES_SYMBOL);
  lcd.print("C");

  // Print the current temperature in farenheit in the lower
  // right corner of the screen.
  float degreesF = convertToFarenheit(degC);
  lcd.setCursor(calculateCursorPosition(degreesF)-1, 1);
  // The space is used to remove the any characters that will be left
  // if the number of digits in the temperature decreases by one.
  lcd.print(" ");
  lcd.print(degreesF, 1);
  lcd.write(DEGREES_SYMBOL);
  lcd.print("F");

  // Even if i try to prevent ghost characters being left when the number
  // of digits in the temperature changes it can still happen if the number of
  // digits changes by more than one digit between two updates. But this should
  // never happen in normal conditions.
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
 Reads the current temperature from the sensor at pin
 and updates the global variable degreesC
*/
float updateCurrentTemperature(int pin)
{
  degreesC = readCelsius(pin);
  degreesC = constrain(degreesC, -273, 999);
  return degreesC;
}



/*
  Turns on or off the alert led depending the current temp and the alert limit.
*/
void updateAlertLed(float currentTempC, float alertLimit)
{
  if(currentTempC > alertLimit){
    digitalWrite(LED_PIN, HIGH);
  }
  else{
    digitalWrite(LED_PIN, LOW);
  }
}



/*
  Calculates the starting column for the cursor to
  make the number with the unit fit on the right side of the display.

  Basicly it calculates the number of digits in the number + two for the unit
  and subtracts this number from the total number og columns in the lcd display.

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
float readCelsius(int pin)
{
  return (getVoltage(pin) - 0.5) * 100.0;
}

/*
  Converts from degrees Celsius to Farenheit
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


