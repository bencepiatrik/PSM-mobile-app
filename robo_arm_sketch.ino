#include <Servo.h>

Servo myServo; // Create a servo object to control a servo motor

int servoPin = 9; // Define the pin to which the servo is connected
int angle = 0;    // Current angle
bool enableServo = false; // Flag to control if the loop should run

void setup() {
  Serial.begin(9600);        // Start serial communication
  myServo.attach(servoPin);  // Attach the servo on pin 9
  //myServo.write(0);         // Start at center position
  delay(1000);

  // Set this to true if you want the sweep to run
  enableServo = true;
}

void loop() {
  if (enableServo) {
    // Sweep from 0 to 180
    for (angle = 0; angle <= 45; angle++) {
      myServo.write(angle);
      Serial.println(angle);   // Print the current angle to Serial Plotter
      delay(15);
    }

    // Sweep back from 180 to 0
    for (angle = 45; angle >= 0; angle--) {
      myServo.write(angle);
      Serial.println(angle);   // Print the current angle to Serial Plotter
      delay(15);
    }
  }
}
