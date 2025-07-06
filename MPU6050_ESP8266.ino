#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Servo.h>

// Create MPU6050 and Servo instances
Adafruit_MPU6050 mpu;
Servo myServo;
Servo myServo2;

void setup() {
  Serial.begin(9600);
  
  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // Set up the MPU6050
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  // Initialize the Servo
  myServo.attach(D5); // GPIO14
  myServo.write(90); // Start at the middle position
  myServo2.attach(D7);
  myServo2.write(90);

  
  delay(100);
}

void loop() {
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  // // Print the acceleration values
  // Serial.print("Acceleration X: ");
  // Serial.print(a.acceleration.x);
  // Serial.print(" m/s^2, ");
  // Serial.print("Y: ");
  // Serial.print(a.acceleration.y);
  // Serial.print(" m/s^2, ");
  // Serial.print("Z: ");
  // Serial.print(a.acceleration.z);
  // Serial.println(" m/s^2");
  // Calculate the angle (you can adjust the formula as needed)
  float angle = a.acceleration.y * 10 + 90;
  // Constrain the angle to valid servo positions
  angle = constrain(angle, 0, 180);
  // Print the values (for debugging)
  //Serial.print("Angle: "); Serial.println(angle);
  // Write the angle to the servo
  myServo.write(180-angle);
  float angleX = a.acceleration.x * 10 + 90;
  // Constrain the angle to valid servo positions
  angleX = constrain(angleX, 0, 180);
  // Print the values (for debugging)
  //Serial.print("Angle: "); Serial.println(angle);
  // Write the angle to the servo
  myServo2.write(180-angleX);

  delay(100); // Adjust the delay as needed
}

