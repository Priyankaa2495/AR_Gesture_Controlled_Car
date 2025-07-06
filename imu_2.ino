#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

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

  // mpu.setXAccelOffset(-2684);
  // mpu.setYAccelOffset(-2733);
  // mpu.setZAccelOffset(1491);
}




void loop() {
  // Raw accelerometer values
  int16_t ax, ay, az;

  // Get raw acceleration values
  mpu.getAcceleration(&ax, &ay, &az);

  // Convert raw values to 'g' values for accelerometer
  float accX = ax / 16384.0 ; // Assuming the accelerometer range is set to ±2g
  float accY = ay / 16384.0 ;
  float accZ = az / 16384.0 ;

  // Calculate pitch and roll angles
  float roll  = atan2(accY, accZ) * 180 / PI;
  float pitch = atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180 / PI;

  // Serial.print("Roll: "); Serial.print(roll);
  // Serial.print(" Pitch: "); Serial.print(pitch);

  // Convert pitch and roll angles to radians
  float roll_rad  = roll * PI / 180;
  float pitch_rad = pitch * PI / 180;

  // String roll_str = roll_rad.toString();
  // String pitch_str = pitch_rad.toString();

  String dataToSend = String(roll_rad, 2) + "," + String(pitch_rad, 2);



  // Send the string via Serial
  
  // String dataToSend = "Hello World";

  Serial.println(dataToSend);


  // // Serial.print("roll ");
  // Serial.print(roll_str);
  // Serial.print(",");
  // // Serial.print("pitch ");
  // Serial.println(pitch_str);

  delay(5);
}