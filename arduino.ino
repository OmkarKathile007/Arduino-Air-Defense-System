#include <Servo.h> 

// Defines Trig and Echo pins of the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;
const int ledPin = 13;  // Define pin for the LED

// Variables for the duration and the distance
long duration;
int distance;
Servo myServo; // Creates a servo object for controlling the servo motor

// Define the threshold distance (in centimeters)
const int thresholdDistance = 20;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  pinMode(ledPin, OUTPUT);  // Sets the ledPin as an Output
  
  Serial.begin(9600);
  myServo.attach(12);  // Defines on which pin the servo motor is attached
  digitalWrite(ledPin, LOW); // Make sure LED is initially off
}

void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    distance = calculateDistance();  // Calls function to calculate the distance
    
    int delayTime = determineDelay();  // Calculate delay based on distance
    blinkLED(delayTime);  // Blink LED if servo slows down
    
    delay(delayTime); // Adjust speed based on delay
    
    Serial.print(i);    // Sends the current degree into the Serial Port
    Serial.print(",");   // Sends addition character for indexing
    Serial.print(distance);  // Sends the distance value into the Serial Port
    Serial.print(".");   // Sends addition character for indexing
  }

  // Repeats the previous lines from 165 to 15 degrees
  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    distance = calculateDistance();
    
    int delayTime = determineDelay();  // Calculate delay based on distance
    blinkLED(delayTime);  // Blink LED if servo slows down
    
    delay(delayTime); // Adjust speed based on delay
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);  // Reads the echoPin and returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;    // Converts time to distance (cm)
  return distance;
}

// Function to determine delay based on object distance
int determineDelay() {
  // Slow down if an object is within the threshold distance
  if (distance <= thresholdDistance) {
    return 100;  // Slow down delay when an object is close
  } else {
    return 30;   // Normal delay
  }
}

// Function to blink LED when the servo is slowed down
void blinkLED(int delayTime) {
  if (delayTime == 100) { // LED should blink only when servo is slow
    digitalWrite(ledPin, HIGH);   // Turn LED on
    delay(100);                   // Small delay for blinking effect
    digitalWrite(ledPin, LOW);    // Turn LED off
    delay(100);                   // Small delay for blinking effect
  } else {
    digitalWrite(ledPin, LOW);    // Keep LED off when servo is moving normally
  }
}
