#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/*
//TODO

*/

Adafruit_PWMServoDriver muxes = Adafruit_PWMServoDriver(0x40);

long counter;
int const numberOfMuxs  = 16;
int const sensorsPerMux = 15;       

int muxToSet = 0;

boolean debug = true;

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
  //SensorBufferTest();

}
  
void loop() {
  
  if(debug) Serial.println(millis());
    
  for(int i = 0; i<15; i++)
  {
      digitalWrite(13,HIGH); //show us it's working. 
      ReadOne( i);
      digitalWrite(13,LOW); //show us it's working.
      //CheckForSerialRequest();
  }


 if(debug) PrintSensors();
}






