#include "Wire.h" //allows communication over i2c devices
int mic = A0;
//int x;
// Variable to hold analog values from mic
int micOut;
int time;

void setup() {
  Serial.begin(9600);
  Wire.begin(9); //Start I2C as Salve on address 9
  Wire.onReceive(receiveEvent); 
}

void receiveEvent(int numBytes) {
    while (Wire.available() > 0) {
        int receivedChar = Wire.read();

        if (receivedChar > 0) {
          micOut = analogRead(mic);
          float voltage = micOut * (3.3 / 1024.0);
          unsigned long currentTime = millis();
          time = currentTime/1000;
          Serial.print(time);
          Serial.print(", ");
          Serial.println(receivedChar);
      // Print the voltage value to the serial monitor
          //Serial.print("ADC Reading: ");
          //Serial.print(micOut);
          //Serial.print(", Voltage: ");
          //Serial.println(voltage);
        } else {
          Serial.println("Loading");
      }
    }
    }

void loop() {

  // Delay for a short period before taking the next reading
  delay(500);
  // print out the value you read:

}
