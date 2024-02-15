#include "Wire.h" //allows communication over i2c devices


const int pressureInput = A0; //select the analog input pin for the pressure transducer
const int pressureZero = 102.4; //analog reading of pressure transducer at 0psi
const int pressureMax = 921.6; //analog reading of pressure transducer at 100psi
const int pressuretransducermaxPSI = 150; //psi value of transducer being used
const int baudRate = 9600; //constant integer to set the baud rate for serial monitor
const int sensorreadDelay = 500; //constant integer to set the sensor read delay in milliseconds
int x;
float pressureValue = 0; //variable to store the value coming from the pressure transducer

void setup() //setup routine, runs once when system turned on or reset
{
  Wire.begin(); //statrt as master 
  Serial.begin(baudRate); //initializes serial communication at set baud rate bits per second
}

void loop() //loop routine runs over and over again forever
{
  pressureValue = analogRead(pressureInput); //reads value from input pin and assigns to variable
  pressureValue = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero); //conversion equation to convert analog reading to psi [CONVERT TO MMHG]
  pressureValue = 80;

//loop for when to start and end the 2nd arduino aka. sound sensor
  if (20 <= pressureValue && pressureValue <= 180 ) {
    x = 1; //Start Arduino2
  } else {
    x = 0; //Stop Arduino2
  }

  Serial.println(x); //prints value from previous line to serial
  Wire.beginTransmission(9); //transmit to other arduino
  Wire.write(x); //sends x
  Wire.endTransmission(); //stop transmitting
  delay(sensorreadDelay); //delay in milliseconds between read values
}

