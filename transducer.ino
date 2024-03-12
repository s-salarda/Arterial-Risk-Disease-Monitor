#include "Wire.h" //allows communication over i2c devices

const int pressureInput = A0; //select the analog input pin for the pressure transducer
const int pressureZero = 102.4; //analog reading of pressure transducer at 0psi
const int pressureMax = 921.6; //analog reading of pressure transducer at 100psi
const int pressuretransducermaxPSI = 150; //psi value of transducer being used
const int baudRate = 9600; //constant integer to set the baud rate for serial monitor
const int sensorreadDelay = 300; //constant integer to set the sensor read delay in milliseconds
float pressureValue = 0; //variable to store the value coming from the pressure transducer
int prev;

void setup() //setup routine, runs once when system turned on or reset
{
  Wire.begin(); //statrt as master 
  Serial.begin(baudRate); //initializes serial communication at set baud rate bits per second
}

void loop() //loop routine runs over and over again forever
{
  prev = pressureValue;
  pressureValue = analogRead(pressureInput); //reads value from input pin and assigns to variable
  pressureValue = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero); //conversion equation to convert analog reading to psi
  Serial.println(pressureValue); //prints value from previous line to serial

  if (pressureValue < prev) {
    Wire.beginTransmission(9); //transmit to other arduino
    Wire.write(prev); //sends the pressure
    Wire.endTransmission(); //stop transmitting
    Serial.println("down");
  } else if (pressureValue >= prev) {
    Wire.beginTransmission(9); //transmit to other arduino
    Wire.write(10); //sends the pressure
    Wire.endTransmission(); //stop transmitting  
    Serial.println("up");
  }

  delay(sensorreadDelay); //delay in milliseconds between read values
}

