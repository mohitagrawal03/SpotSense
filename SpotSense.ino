#include <Servo.h>

const int numSensors = 3;
const int trigPins[numSensors] = {3, 5, 7}; // Trig pins of ultrasonic sensors connected to Arduino pins 4, 7, and 8
const int echoPins[numSensors] = {4, 6, 8}; // Echo pins of ultrasonic sensors connected to Arduino pins 5, 6, and 9

Servo servoMotor;
const int servoPin = 9; // Servo motor signal pin connected to Arduino pin 10

void setup() {
  for (int i = 0; i < numSensors; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }

  servoMotor.attach(servoPin);
  servoMotor.write(0); // Initialize the servo motor at 0 degrees
  Serial.begin(9600);
}

void loop() {
  int detectedSensor = -1; // Initialize with -1 to indicate no sensor detected an object
  for (int i = 0; i < numSensors; i++) {
    if (isObjectDetected(i)) {
      detectedSensor = i;
      break; // Exit loop as soon as the first detected sensor is found
    }
  }

  // Set servo motor rotation angle based on the detected sensor
  if (detectedSensor == 0) {
    servoMotor.write(45);
    Serial.println("Object detected by Sensor 1! Servo motor rotated to 45 degrees.");
  } else if (detectedSensor == 1) {
    servoMotor.write(90);
    Serial.println("Object detected by Sensor 2! Servo motor rotated to 90 degrees.");
  } else if (detectedSensor == 2) {
    servoMotor.write(135);
    Serial.println("Object detected by Sensor 3! Servo motor rotated to 135 degrees.");
  } 

  delay(500); // Adjust the delay as needed to avoid false triggers and smoother operation
}

bool isObjectDetected(int sensorIndex) {
  // Trigger the ultrasonic sensor to send a pulse
  digitalWrite(trigPins[sensorIndex], LOW);
  delayMicroseconds(2);
  digitalWrite(trigPins[sensorIndex], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPins[sensorIndex], LOW);

  // Measure the duration of the pulse to calculate distance
  long duration = pulseIn(echoPins[sensorIndex], HIGH);
  float distance = duration * 0.034 / 2; // Speed of sound in air is ~34 cm/ms

  return (distance <= 100); // 100 cm = 1 meters
}