#include "Wire.h" //allows communication over i2c devices

int mic = A0;
int micOut;
int consecutiveCount = 0; // Counter for consecutive receivedChar > 15
bool printMicOut = false; // Flag to track when to print micOut
unsigned long prevTime = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(9); //Start I2C as Salve on address 9
  Wire.onReceive(receiveEvent); 
}

void receiveEvent(int numBytes) {
    while (Wire.available() > 0) {
        int receivedChar = Wire.read();

        if (receivedChar > 15) {
          consecutiveCount++; // Increment counter
        } else {
          consecutiveCount = 0; // Reset counter if receivedChar <= 15
        }
      
        if (consecutiveCount >= 3) {
          printMicOut = true; // Set the flag to true after three consecutive receivedChar > 15
        }
        if (printMicOut) {
          micOut = analogRead(mic);
          Serial.println(micOut);
        } else {
          Serial.println(0);          
        }
    }
}
void loop() {

}
  delay(500);
  // print out the value you read:

}
