#include "Wire.h" //allows communication over i2c devices

int mic = A0;
int micOut;
unsigned long prevTime = 0; // Variable to hold the previous timestamp

void setup() {
  Serial.begin(9600);
  Wire.begin(9); //Start I2C as Salve on address 9
  Wire.onReceive(receiveEvent); 
}

void receiveEvent(int numBytes) {
    while (Wire.available() > 0) {
        int receivedChar = Wire.read();

        if (receivedChar < 9) {
          micOut = analogRead(mic);
          float voltage = micOut * (3.3 / 1024.0);
          unsigned long currentTime = millis();
          unsigned long elapsedTime = currentTime - prevTime; // Calculate elapsed time
          prevTime = currentTime; // Update previous timestamp
          float samplingFrequency = 1000.0 / elapsedTime;
          //Serial.print(currentTime);
          //Serial.print(" ");
          Serial.print(receivedChar);
          Serial.print(" ");
          Serial.print(micOut);
          Serial.println(); // Calculate sampling frequency in Hz
          // Serial.print("Sampling Frequency: ");
          // Serial.print(samplingFrequency);
          // Serial.print(" Hz, ");
          // Serial.print("ADC Reading: ");
          // Serial.print(micOut);
          // Serial.print(", Voltage: ");
          // Serial.println(voltage);
        } else {
          Serial.print(receivedChar);
          Serial.print(" ");
          Serial.println(0);
      }
    }
}

void loop() {
  // Delay for a short period before taking the next reading
  delay(100);
}
  delay(500);
  // print out the value you read:

}
