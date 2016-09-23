
int const sensorsXCount = 10;
int const sensorsYCount = 23;

byte sensorReadArray[sensorsXCount][sensorsYCount]; //?
byte sensorSendBuffer[sensorsYCount*2]; // 0 = HIGH BYTE, 1 = LOW BYTE

 
void ReadAllSensors()
{
  //itterate through all 16 channels by setting the input selector for all muxes as defined in the sensorReadOrderIndex
  Serial.println("ReadingSensors");
  for( byte s = 0; s < 5; s++) //the first 5 SENSORS ON EACH MUX (SKIP THE FIRST ROW OF THE FIRST TWO MUXS - THEY ARE NOT CONNECTED) 
  {
     //select the first sensor (via index)
     Serial.print("s:");Serial.println(s);
     SetMux(s);
    
    
    //for each mux, starting at SECOND ROW of muxes, skipping the first
    for(int m = 1; m < 8; m++) //8 not 16! 
    {
        int y =  map(s,0,14,0,2) + (m*3); //each 5 sensors advance y by 1, Each mux advance Y by three
        // Serial.println(y);
         
        sensorReadArray[s][y]   = digitalRead( muxInputPinLeft[m]  ) == 0; //reversed output
        sensorReadArray[s+5][y] = digitalRead( muxInputPinRight[m] ) == 0; //reversed output
     }
  }
  
  for( byte s = 5; s < 15; s++) //the remaining 10 sensors read as normal
  {
     //select the first sensor (via index)
     Serial.print("s:");Serial.println(s);
     SetMux(s);
  
    for(int m = 0; m < 8; m++) //8 not 16! 
    {
        int y = map(s,0,14,0,2) + (m*3)  ; //each 5 sensors advance y by 1, Each mux advance Y by three. Minus ONE to start at the second row as ZERO Y. Dont ask. 
        //Serial.println(y);
        sensorReadArray[s][y]   = digitalRead( muxInputPinLeft[m]  ) == 0; //reversed output
        sensorReadArray[s+5][y] = digitalRead( muxInputPinRight[m] ) == 0; //reversed output
     }
  }

  Serial.println("SensorReadFinished");
}

void ReadOne(int muxInput)
{
  int yStart = 0;
  if(muxInput <5)yStart++;

  SetMux(muxInput);
  
    for(int m = 0; m < 8; m++) //8 not 16! 
    {
        int y = map(muxInput,0,14,0,2) + (m*3)  ; //each 5 sensors advance y by 1, Each mux advance Y by three. Minus ONE to start at the second row as ZERO Y. Dont ask. 
        //Serial.println(y);
        sensorReadArray[muxInput][y]   = digitalRead( muxInputPinLeft[m]  ) == 0; //reversed output
        sensorReadArray[muxInput+5][y] = digitalRead( muxInputPinRight[m] ) == 0; //reversed output
     }
  
  }



void CopySensorReadsToSendBuffer()
{
   if(debug) Serial.println("CopyToBuffer");
  //it was initially easy to put sensor reads into a byte array, now consolodating bits for a faster transfer
  
  for(int y = 0; y < sensorsYCount*2; y+=2)
  {
    flash();
    sensorSendBuffer[y] = sensorSendBuffer[y+1] = 0;

    //Second out, Low byte
    sensorSendBuffer[y+1] |= sensorReadArray[0][y] ;//set first place
    for(int x = 1; x < 8; x++)
    {
     sensorSendBuffer[y+1] = sensorSendBuffer[y] << 1; //move and populate the next bit
     sensorSendBuffer[y+1] |= sensorReadArray[x][y]; 
    }

    //First out, high byte
    sensorSendBuffer[y] |= sensorReadArray[9][y]; 
    sensorSendBuffer[y] = sensorSendBuffer[y] << 1; //move and populate the next bit
    sensorSendBuffer[y] |= sensorReadArray[8][y]; 
  }
    if(debug) Serial.println("CopyToBuffer Done");
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
       mask = mask>>1; 
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
       Serial.print((sensorSendBuffer[y] & mask)); 
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



