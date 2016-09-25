//#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/*
//TODO

*/

Adafruit_PWMServoDriver muxes = Adafruit_PWMServoDriver(0x40);

long counter;
int const numberOfMuxs  = 16;
int const sensorsPerMux = 15;       

int muxToSet = 0;

boolean debug = false;

void setup() 
{
  Serial.begin(115200); //to-from pc
  
  Serial1.begin(9600); //to-from RFID
  
  delay(2000); //delay startup to let other devices power up. 
  if(debug) Serial.println("Good morning, Dr. Chandra. This is Hal. I am ready for my first lesson.");
  delay(2000); //delay startup to let other devices power up. 
  Serial.println();
  Serial.println();

  //It will Freeze Here if not connected to pwm board
  
  InitializeMuxes();
  InitializePins();
  //TestPolulateSensorArray();
 
}
  
void loop() {
  
//  for(int i = 0; i>15; i++)
//  {
//    ReadOne(i);
//  }

  ReadAllSensors();
  CopySensorReadsToSendBuffer();
  CheckForSerialRequest();
 
  if(debug) PrintSendBuffer();
  if (debug) PrintSensors();
}






