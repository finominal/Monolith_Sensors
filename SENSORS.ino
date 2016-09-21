
int const sensorsXCount = 10;
int const sensorsYCount = 23;

byte sensorReadArray[sensorsXCount][sensorsYCount]; //?
short sensorSendBuffer[sensorsYCount]; //?

  

void ReadAllSensors()
{
  //itterate through all 16 channels by setting the input selector for all muxes as defined in the sensorReadOrderIndex
  
  for( int s = 0; s < 5; s++) //the first 5 SENSORS ON EACH MUX (SKIP THE FIRST ROW OF THE FIRST TWO MUXS - THEY ARE NOT CONNECTED) 
  {
     //select the first sensor (via index)
     SetMux(s); 
     //delayMicroSeconds(1); 
    
    //for each mux, starting at SECOND ROW of muxes, skipping the first
    for(int m = 1; m < sizeof(muxInputPinLeft); m++) //8 not 16! 
    {
        int y = ((s/5) + (m*3)) -1; //each 5 sensors advance y by 1, Each mux advance Y by three
        sensorReadArray[s][y]   = digitalRead( muxInputPinLeft[m]  ) == 0; //reversed output
        sensorReadArray[s+5][y] = digitalRead( muxInputPinRight[m] ) == 0; //reversed output
     }
  }
  

  for( int s = 5; s < sensorsPerMux; s++) //the remaining 10 sensors read as normal
  {
     //select the first sensor (via index)
     SetMux(s);
     //delayMicroSeconds(1);
    
    //for each mux, starting at SECOND ROW of muxes, skipping the first coz they are not connected
    for(int m = 0; m < sizeof(muxInputPinLeft); m++) //8 not 16! 
    {
        int y = ((s/5) + (m*3)) -1 ; //each 5 sensors advance y by 1, Each mux advance Y by three. Minus ONE to start at the second row as ZERO Y. Dont ask. 
        sensorReadArray[s][y]   = digitalRead( muxInputPinLeft[m]  ) == 0; //reversed output
        sensorReadArray[s+5][y] = digitalRead( muxInputPinRight[m] ) == 0; //reversed output
     }
  }
}


void CopySensorReadsToSendBuffer()
{
  Serial.println("CopyToBuffer");
  //it was initially easy to put sensor reads into a byte array, now consolodating bits for a faster transfer
  short resultBuffer;
  
  for(int y = 0; y < sensorsYCount; y++)
  {
    resultBuffer = 0;
    resultBuffer |= sensorReadArray[0][y] == 1;//set first place
    Serial.print("0,");Serial.print(y);Serial.print(" = ");
    Serial.println(resultBuffer,BIN);
    
    for(int x = 1; x < sensorsXCount; x++)
    {
      resultBuffer << 1; //move and populate the next bit
      resultBuffer |= sensorReadArray[x][y]; 
        Serial.print(x);Serial.print(",");Serial.print(y);Serial.print(" = ");
    Serial.println(resultBuffer,BIN);
 
    }
    sensorSendBuffer[y] = resultBuffer;
  }
}


void PrintSendBuffer()
{
  Serial.println("SendBuffer"); 
  for(int y = 0; y<sensorsYCount;y++)
  {  
    Serial.print(y); Serial.print(":"); 
    short mask = 1024;
    
    for(int x = 0; x<sensorsXCount;x++)
    {  
       Serial.print((sensorSendBuffer[y] & mask) > 0); 
       mask>>1; 
    }
    Serial.println();  
  }
  Serial.println();  
}


void PrintSendBufferRaw()
{
  Serial.println("raw"); 
  
  for(int y = 0; y<sensorsYCount;y++)
  {  
    short mask = 1024;
    Serial.print(y); Serial.print(":"); 
    
    for(int x = 0; x<sensorsXCount;x++)
    {  
       Serial.print((sensorSendBuffer[y] & mask) > 0); 
       mask>>1; 
    }  

    
    Serial.print(" - "); 
    Serial.print(y); Serial.print(":");  Serial.print(sensorSendBuffer[y], BIN);
    Serial.println();
  }
  Serial.println();  
}


void PrintSensors()
{
  Serial.println(counter); 
  
  for(int y = 0; y<sensorsYCount; y++)
  { 
    Serial.print(y); Serial.print(":");
    for(byte s = 0; s<sensorsXCount;s++)
    {
      Serial.print(sensorReadArray[s][y] == 1);  
    }
    Serial.println();  
  }
  Serial.println();  
}



