#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver muxes = Adafruit_PWMServoDriver(0x40);

unsigned long counter;


int const numberOfMuxs  = 16;
int const sensorsPerMux = 15;



void setup() 
{
  Serial.begin(115200); //to-from pc
  
  Serial1.begin(9600); //to-from RFID
  
  delay(2000); //delay startup to let other devices power up. 
    
  Serial.println("hello");

  InitializePins();

  //Can Freeze Here if not connected to pwm board
  //InitializeMuxes();

 TestPolulateSensorArray();
 PrintSensors();
 CopySensorReadsToSendBuffer();

  //PrintSendBufferRaw();
  //TestPolulateBuffer();
  PrintSendBufferRaw();
  PrintSendBuffer();

  
 
}
  
void loop() {
  
   // ReadAllSensors();
   // PrintSensors();
    
    delay(100);
    counter++;
}




void setMuxBySerial()
{
  if(Serial.available())
  {
      byte in = Serial.read();
      SetMux(in);
      Serial.println(in);
   }
    //Serial.println(digitalRead(9));
}


