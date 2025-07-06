#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;


String receivedData;
float roll;
float pitch;// const int ENA = 9;   // Enable pin for motor A
const int IN1 = 2;   // Control pin 1 for motor A
const int IN2 = 3;   // Control pin 2 for motor A
// const int ENB = 10;  // Enable pin for motor B
const int IN3 = 4;   // Control pin 1 for motor B
const int IN4 = 5;   // Control pin 2 for motor B

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
    while (1);
  }
  // pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  // pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // digitalWrite(ENA, HIGH);  // Enable motor A
  // digitalWrite(ENB, HIGH);  // Enable motor B
}

void loop() {
  if (Serial.available() > 0) {
     receivedData = Serial.readStringUntil('\n');
    
    // Find the comma separator
    int commaIndex = receivedData.indexOf(',');
    
    // Extract the two float variables from the string
    if (commaIndex != -1) {
      roll = receivedData.substring(0, commaIndex).toFloat();
      pitch = receivedData.substring(commaIndex + 1).toFloat();
      
      // Print the received float variables
      Serial.print("Received Float 1: ");
      Serial.println(roll);
      Serial.print("Received Float 2: ");
      Serial.println(pitch);
    
    controlCar(roll,pitch);}
  }
}

void controlCar(float roll, float pitch) {
  // Forward/Backward control based on Y-axis acceleration
  if (pitch > 0.2) { // Threshold value for forward motion
    moveForward();
  } else if (pitch < -0.2) { // Threshold value for backward motion
    moveBackward();
  } else {
    stopMoving();
  }
  
  // Left/Right control based on X-axis acceleration
  if (roll > 1.1) { // Threshold value for left turn
    turnRight();
  } else if (roll < 0.5) { // Threshold value for right turn
    turnLeft();
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMoving() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}