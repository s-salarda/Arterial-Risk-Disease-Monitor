int mic = A0;

// Variable to hold analog values from mic
int micOut;

void setup() {
  Serial.begin(9600);
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
}
void receiveEvent(int bytes) {
  x = Wire.read();
}

void loop() {
    if (x > 0) {
      char receivedChar = Serial.read();
      Serial.print("Received: ");
      Serial.println(receivedChar);
        // read the input on analog pin 0:
      micOut = analogRead(mic);

      float voltage = micOut * (3.3 / 1024.0);

      // Print the voltage value to the serial monitor
      Serial.print("ADC Reading: ");
      Serial.print(micOut);
      Serial.print(", Voltage: ");
      Serial.println(voltage);
    }


  // Delay for a short period before taking the next reading
  delay(500);
  // print out the value you read:

}
