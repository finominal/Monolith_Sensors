#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver muxes = Adafruit_PWMServoDriver(0x40);

unsigned long counter;

#define mux1
#define mux2
#define mux3
#define mux4
#define mux5
#define mux6
#define mux7
#define mux8
#define mux9
#define mux10
#define mux11
#define mux12
#define mux13
#define mux14
#define mux15
#define mux16


int sensorsXCount = 10;
int sensorsYCount = 23;
int numberOfMuxs  = 16;
int sensorsPerMux = 15;

int muxChannelReadOrderIndex[] = {
                              10, 11, 12, 13, 14, 
                               5,  6,  7,  8,  9, 
                               0,  1,  2,  3,  4 
                              };

int muxInputPinLeft[] = {4, 17, 27,22, 5, 6 ,13,26}; //change for teensy
int muxInputPinRight[] = {18, 23, 24, 25, 12, 16, 20, 21}; //change for teensy

byte sensors[sensorsXCount][sensorsYCount]; //?
short sensorSendBuffer[sensorsYCount]; //?
  

void setup() 
{
  Serial.begin(115200); //to-from pc
  
  Serial.begin(9600); //to-from 
  
  delay(3000); //delay startup to let other devices power up. 
    
  Serial.println("hello");

  initializePins();

  muxes.begin();
  muxes.setPWMFreq(1000);  // This is the maximum PWM frequency
  
  delay(1);
  Serial.println("Muxes Ready");

  allOff();
}
  
void loop() {
  
    ReadAllSensors();
    printSensors();
    
    //setBySerial();
    
    delay(100);
    counter++;
}

void setBySerial()
{
  if(Serial.available())
  {
      byte in = Serial.read();
      SetMux(in);
      Serial.println(in);
   }
    //Serial.println(digitalRead(9));
}


  void readAllSensors()
  {
    //itterate through all 16 channels by setting the input selector for all muxes as defined in the sensorReadOrderIndex
    
    for( int s = 0; s < 5; s++) //the first 5 SENSORS ON EACH MUX (SKIP THE FIRST ROW OF THE FIRST TWO MUXS - THEY ARE NOT CONNECTED) 
    {
       //select the first sensor (via index)
       SetMux(s); 
       //delayMicroSeconds(1); 
      
      //for each mux, starting at SECOND ROW of muxes, skipping the first
      for(int m = 1; m < muxInputPinLeft.length; m++) //8 not 16! 
      {
          int y = ((s/5) + (m*3)) -1; //each 5 sensors advance y by 1, Each mux advance Y by three
          sensorArrayXY[s][y].on   = digitalRead( muxInputPinLeft[m]  ) == 0; //reversed output
          sensorArrayXY[s+5][y].on = digitalRead( muxInputPinRight[m] ) == 0; //reversed output
       }
    }
    
  
    for( int s = 5; s < sensorsPerMux; s++) //the remaining 10 sensors read as normal
    {
       //select the first sensor (via index)
       SetMux(s);
       //delayMicroSeconds(1);
      
      //for each mux, starting at SECOND ROW of muxes, skipping the first coz they are not connected
      for(int m = 0; m < muxInputPinLeft.length; m++) //8 not 16! 
      {
          int y = ((s/5) + (m*3)) -1 ; //each 5 sensors advance y by 1, Each mux advance Y by three. Minus ONE to start at the second row as ZERO Y. Dont ask. 
          sensorArrayXY[s][y].on   = digitalRead( muxInputPinLeft[m]  ) == 0; //reversed output
          sensorArrayXY[s+5][y].on = digitalRead( muxInputPinRight[m] ) == 0; //reversed output
       }
    }
  }
  


void PushSensorReadsToSendBuffer()
{
  //it was initially easy to put sensor reads into a byte array, now consolodating bits for a faster transfer
  short resultBuffer;
  
  for(int y = 0; y < sensorsYCount; y++)
  {
    resultBuffer = 0;
    resultBuffer =| sensors[0][y];//set first place
    
    for(int x = 1; x < sensorsXCount; x++)
    {
      resultBuffer << 1; //move and populate the next bit
      resultBuffer =| sensors[x][y]; 
    }
    sensorSendBuffer[y] = resultBuffer;
  }
}
  
  

void SetMux(int s)
{
  byte buf = s;

  for(int i = 0; i<4;i++)//for each 4-lsb bits in the byte
  {
    if(buf&1 > 0)
    { 
      muxes.setPWM(i*4, 0, 4095);
      muxes.setPWM(i*4+1, 0, 4095);
      muxes.setPWM(i*4+2, 0, 4095);
      muxes.setPWM(i*4+3, 0, 4095);
    }
    else
    {
       muxes.setPWM(i*4, 4095, 0);
       muxes.setPWM(i*4+1, 4095, 0);
       muxes.setPWM(i*4+2, 4095, 0);
       muxes.setPWM(i*4+3, 4095, 0);
    }
    buf = buf>>1;
  }
}


void printSensors()
{
  Serial.println(counter); 
      for(int x = 0; x<sensorsYCount;x++)
      {  
        
        
         for(byte s = 0; s<15;s++)
          {
            Serial.print(sensors[b][s]);  
          }
          Serial.println();  
      }
      Serial.println();  
  }

void printSensorsInBuffer()
{
  Serial.println(counter); 
  
  for(int y = 0; y<sensorsYCount;y++)
  {  
    byte mask = 0b1000000000;
    for(int x = 0; x<sensorsXCount;x++)
    {  
       Serial.print((sensorSendBuffer[y] & mask) > 0); 
       mask>>1; 
    }
    Serial.println();  
  }
  
  Serial.println();  
}

void allOn()
{
  for( int i = 0; i<16;i++)
 {
   muxes.setPWM(i, 0, 4095);
 }
 Serial.println("All On");
}

void allOff()
{
  for( int i = 0; i<16;i++)
 {
   muxes.setPWM(i, 4095, 0 );
 }
 Serial.println("All Off");
}


void initializePins()
{

  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  
  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  
  pinMode(14,INPUT_PULLUP);
  pinMode(15,INPUT_PULLUP);
  pinMode(16,INPUT_PULLUP);
  pinMode(17,INPUT_PULLUP);
  
  pinMode(20,INPUT_PULLUP);
  pinMode(21,INPUT_PULLUP);
  pinMode(22,INPUT_PULLUP);
  pinMode(23,INPUT_PULLUP);
      

  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH); //show us it's working. 
}
