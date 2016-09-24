
int const sensorsXCount = 10;
int const sensorsYCount = 23;

byte sensorReadArray[sensorsXCount][sensorsYCount]; //?
byte sensorSendBuffer[sensorsYCount*2]; // 0 = HIGH BYTE, 1 = LOW BYTE

void ReadAllSensors()
{
  for(int i = 0; i<15; i++)
  {
      //digitalWrite(13,HIGH); //show us it's working. 
      ReadOne( i);
      //digitalWrite(13,LOW); //show us it's working.
  }
  //CopySensorReadsToSendBuffer();
}

void ReadOne(int muxInput)
{
  
  int m,y = 0;

  m = muxInput < 5? 1 : 0;
  
  SetMux(muxChannelReadOrderIndex[muxInput]);
  delayMicroseconds(300);

  for(; m < 8; m++) //8 not 16! 
  {
      y = ((muxInput/5) + m*3) -1;  //each 5 sensors advance y by 1, Each mux advance Y by three. Minus ONE to start at the second row as ZERO Y. Dont ask. 
     //TODO Read directly into buffer
      sensorReadArray[muxInput%5][y]   = digitalRead( muxInputPinLeft[m]  ) == 0; //reversed output
      sensorReadArray[(muxInput%5)+5][y] = digitalRead( muxInputPinRight[m] ) == 0; //reversed output
  }
}



void CopySensorReadsToSendBuffer()
{
   if(debug) Serial.println("CopyToBuffer");
 //it's easier to store data in a byte array so it can be sent and recieved easily.
 int bufferY;
  for(int y = 0; y < sensorsYCount; y++)
  {
    //flash();
    bufferY = y*2;
    sensorSendBuffer[bufferY] = sensorSendBuffer[bufferY+1] = 0;
    
   //First out, high byte
    sensorSendBuffer[bufferY] |= sensorReadArray[0][y]; 
    sensorSendBuffer[bufferY] = sensorSendBuffer[bufferY] << 1; //move and populate the next bit
    sensorSendBuffer[bufferY] |= sensorReadArray[1][y]; 

    //Second out, Low byte
    sensorSendBuffer[bufferY+1] |= sensorReadArray[2][y] ;//set first place
    for(int x = 3; x < sensorsXCount; x++)
    {
     sensorSendBuffer[bufferY+1] = sensorSendBuffer[bufferY+1] << 1; //move and populate the next bit
     sensorSendBuffer[bufferY+1] |= sensorReadArray[x][y]; 
    }
  }
    if(debug) Serial.println("CopyToBuffer Done");
}

void PrintSendBuffer()
{
  Serial.println(millis()); 
  int bufferY;
  char mask;
  for(int y = 0; y<sensorsYCount;y++)
  {  
    Serial.print(y); Serial.print(":"); 
    mask = 128;
    bufferY = y*2;

    Serial.print((sensorSendBuffer[bufferY] & 2) > 0); 
    Serial.print((sensorSendBuffer[bufferY] & 1) > 0); 
       
    for(int x = 0; x<8;x++) //minus the two above, 10 sensors. 
    {  
      Serial.print((sensorSendBuffer[bufferY+1] & mask) > 0); 
     mask = mask >> 1;
    }
    Serial.println();  
  }
  Serial.println();  
}

void PrintSendBufferRaw()
{
  Serial.println("raw"); 
  
  for(int y = 0; y<sensorsYCount*2;y++)
  {  
    /*
    short mask = 1024;
    Serial.print(y); Serial.print(":"); 
    
    for(int x = 0; x<sensorsXCount;x++)
    {  
       Serial.print((sensorSendBuffer[y] & mask)); 
       mask>>1; 
    }  
    */
    Serial.print(" - "); 
    Serial.print(y); Serial.print(":");  Serial.print(sensorSendBuffer[y], BIN);
    Serial.println();
  }
  
  Serial.println();  
}

void PrintSensors()
{
  Serial.println(millis());
  
  for(int y = 0; y<sensorsYCount; y++)
  { 
    Serial.print(y); 
    if(y < 10) Serial.print(" ");
    Serial.print(":");
    for(byte s = 0; s<sensorsXCount;s++)
    {
      if(s == 5 ) Serial.print(" ");
      Serial.print(sensorReadArray[s][y] );  
    }
    Serial.println();  
  }
  Serial.println();  
}



