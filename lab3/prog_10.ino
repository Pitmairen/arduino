

// Include the servo library
#include <Servo.h>

// The pins used int the code
const int flexPin = A0;
const int servoPin = 9;


// The minimal and maximal position of the servo.
// I use 15 as the minimum position becase if the value is lower
// the servo starts to make a weird noice.
const int servoMinPosition = 15;
const int servoMaxPosition = 180;

// This value is used to make the movement of the servo more smooth.
// This number is the number of reads to make to the flex-sensor and then we
// take the average of the result.
// It must be above zero and should not be too high because it creates
// a delay between the movement in the flex-sensor and the response in the servo.
// And also if the value is above 64 it can make some variables "roll over" and
// create unexpected results.
const int servoSmoothing = 40; // range: 1-64

// Global servo object used to control the servo.
Servo servo;


void setup() {

  // Setup the serial connection
  Serial.begin(9600);

  // Attach the servoPin to the servo object.
  servo.attach(servoPin);
  // Set the servos initial position
  servo.write(servoMinPosition);

  // There is no need to set the servoPin to OUTPUT mode because this is
  // done by the servo.attach method.

}

void loop() {

  // Used to store the value read from the flex-sensor.
  // Use unsigned to get a bigger upper range for the numbers to prevent
  // it from rolling over because of the "smoothing" used below.
  unsigned int flexValue = 0;

  // Read the the flex-sensor multiple-times with one millisecond delay
  // to smooth the movement of the servo.
  for(int i=0; i<servoSmoothing; i++)
  {
    flexValue += analogRead(flexPin);
    delay(1);
  }

  // Print the value read from the flex-sensor.
  Serial.print("Sensor value: ");
  Serial.println(flexValue);

  // Map the flexValue to the servo range. Multiply the fromValue by
  // servoSmooting to make it map the average values from the multiple
  // readings to the sensor. The values 770 and 900 are the numbers obetained
  // by testing the sensor and finding the minimum and maximum readings
  // from the sensor. Use "L" at the end of the constants to prevent
  // "roll over" if the servoSmoothing number is big.
  int servoPosition = map(flexValue, 770L*servoSmoothing, 900L*servoSmoothing,
                          servoMinPosition, servoMaxPosition);

  // Constrain the position to the min and max position.
  servoPosition = constrain(servoPosition, servoMinPosition, servoMaxPosition);

  // Set the servo position
  servo.write(servoPosition);

}
