#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4

#include <ESP8266WiFi.h>

const char* ssid = "Pratul";
const char* password = "12345678";
const char* serverIP = "192.168.6.10";

void setup() {
    Serial.begin(9600);
    delay(10);
    
    // Set motor control pins as outputs
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    
    // Connect to Wi-Fi
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
}

void loop() {
    // Establish TCP connection with server
    WiFiClient client;
    if (!client.connect(serverIP, 80)) {
        Serial.println("Connection failed");
        delay(1000); // Retry after a delay
        return;
    }

    while (client.connected()) {
        if (client.available()) {
            String receivedData = client.readStringUntil('\n');
            // Serial.println("Received data: " + receivedData);
            
            int commaIndex = receivedData.indexOf(',');
            if (commaIndex != -1) {
                String float1String = receivedData.substring(0, commaIndex);
                String float2String = receivedData.substring(commaIndex + 1);
                
                float roll = float1String.toFloat();
                float pitch = float2String.toFloat();
                
                // Print the received floats to the Serial Monitor
                Serial.print("Roll: ");
                Serial.print(roll);
                Serial.print(" , Pitch: ");
                Serial.println(pitch);
                // controlCar(roll, pitch);
            }
        }
        
        // if (Serial.available()) {
        //     String request = Serial.readStringUntil('\n');
        //     Serial.println("Sending request: " + request);
        //     client.println(request);
        // }
    }
    
    // client.stop(); // Close the connection when done
}

void controlCar(float roll, float pitch) {
    // Forward/Backward control based on Y-axis acceleration
    if (pitch > 20.0) { // Threshold value for forward motion
        moveForward();
    } else if (pitch < -20.0) { // Threshold value for backward motion
        moveBackward();
    } else {
        stopMoving();
    }
    
    // Left/Right control based on X-axis acceleration
    if (roll > 20.0) { // Threshold value for left turn
        turnRight();
    } else if (roll < -20.0) { // Threshold value for right turn
        turnLeft();
    }
}

void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("Moving Forward");
}

void moveBackward() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("Moving Backward");
}

void turnLeft() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("Turning Left");
}

void turnRight() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("Turning Right");
}

void stopMoving() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    Serial.println("Stop Moving");
}
