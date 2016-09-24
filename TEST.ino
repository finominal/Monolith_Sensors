void TestPolulateSensorArray()
{
  sensorReadArray[0][0] = 1;
  sensorReadArray[2][2] = 1;
  sensorReadArray[3][2] = 1;
  sensorReadArray[5][5] = 1;
  }

  void TestPolulateSendBuffer()
{
  sensorSendBuffer[0] = 1;
  sensorSendBuffer[2] = 3;
  sensorSendBuffer[20] = 8;
  sensorSendBuffer[5] = 512; //later bit
  }

 void SensorBufferTest()
 {
   if(debug) Serial.println("SensorBufferTest");
  
   TestPolulateSensorArray();
   
   PrintSensors();
   
   CopySensorReadsToSendBuffer();

   PrintSendBuffer();
   PrintSendBufferRaw();
 }

 void dontDoAnythingElse()
 {

  while(true) {
    CopySensorReadsToSendBuffer();
    delay(1000);} 
  }
