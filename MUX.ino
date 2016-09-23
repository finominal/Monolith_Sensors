
int muxChannelReadOrderIndex[] = {
                              10, 11, 12, 13, 14, 
                               5,  6,  7,  8,  9, 
                               0,  1,  2,  3,  4 
                              };

int muxInputPinLeft[]  = { mux0, mux1, mux2,  mux3,  mux4,  mux5,  mux6,  mux7  }; //change for teensy
int muxInputPinRight[] = { mux8, mux9, mux10, mux11, mux12, mux13, mux14, mux15 }; //change for teensy

void InitializeMuxes()
{
 
  muxes.begin();
  muxes.setPWMFreq(1000);  // 1600 is max I think. about that. 
  delay(1);
   
  if(debug) Serial.println("Muxes Ready");

  allMuxOff();
}




void SetMux(byte s)
{
  //Serial.print("Set:");Serial.println(s);
  byte buf = s; 
  byte mask = 1;
  
  for(int i = 0; i<4;i++)//for each 4-lsb bits in the byte
  {
    if(buf & mask > 0)
    { 
      muxes.setPWM(i*4,   0, 4095);
      muxes.setPWM(i*4+1, 0, 4095);
      muxes.setPWM(i*4+2, 0, 4095);
      muxes.setPWM(i*4+3, 0, 4095);
    }
    else
    {
       muxes.setPWM(i*4,   4095, 0);
       muxes.setPWM(i*4+1, 4095, 0);
       muxes.setPWM(i*4+2, 4095, 0);
       muxes.setPWM(i*4+3, 4095, 0);
    }
    buf = buf>>1;
  }
}



void allMuxOn()
{
  for( int i = 0; i<16;i++)
 {
   muxes.setPWM(i, 0, 4095);
 }
  if(debug)Serial.println("All On");
}

void allMuxOff()
{
  for( int i = 0; i<16;i++)
 {
   muxes.setPWM(i, 4095, 0 );
 }
  if(debug)Serial.println("All Off");
}






/* 
 *  Set mux long handed
 *  
void SetMux(byte s)
{
  Serial.print("Setting "); Serial.println(s); 
   switch(s)
   {
    case 0:
      setPWM(0, 0);
      setPWM(1, 0);
      setPWM(2, 0);
      setPWM(3, 0);
      Serial.print("Set "); Serial.println(s);
    break;
    case 1:
      setPWM(0, 1);
      setPWM(1, 0);
      setPWM(2, 0);
      setPWM(3, 0);
      Serial.print("Set "); Serial.println(s);
    break;
    case 2:
      setPWM(0, 0);
      setPWM(1, 1);
      setPWM(2, 0);
      setPWM(3, 0);
      Serial.print("Set "); Serial.println(s);
    break;
    case 3:
      setPWM(0, 1);
      setPWM(1, 1);
      setPWM(2, 0);
      setPWM(3, 0);
      Serial.print("Set "); Serial.println(s);
    break;
    case 4:
      setPWM(0, 0);
      setPWM(1, 0);
      setPWM(2, 1);
      setPWM(3, 0);
      Serial.print("Set "); Serial.println(s);
    break;
    case 5:
      setPWM(0, 1);
      setPWM(1, 0);
      setPWM(2, 1);
      setPWM(3, 0);
      Serial.print("Set "); Serial.println(s);
    break;
    case 6:
      setPWM(0, 0);
      setPWM(1, 1);
      setPWM(2, 1);
      setPWM(3, 0);
      Serial.print("Set "); Serial.println(s);
    break;
    case 7:
      setPWM(0, 1);
      setPWM(1, 1);
      setPWM(2, 1);
      setPWM(3, 0);
      Serial.print("Set "); Serial.println(s);
    break;
    case 8:
      setPWM(0, 0);
      setPWM(1, 0);
      setPWM(2, 0);
      setPWM(3, 1);
      Serial.print("Set "); Serial.println(s);
    break;
    case 9:
      setPWM(0, 1);
      setPWM(1, 1);
      setPWM(2, 1);
      setPWM(3, 1);
      Serial.print("Set "); Serial.println(s);
    break;
    case 10:
      setPWM(0, 0);
      setPWM(1, 1);
      setPWM(2, 0);
      setPWM(3, 1);
      Serial.print("Set "); Serial.println(s);
    break;
    case 11:
      setPWM(0, 1);
      setPWM(1, 1);
      setPWM(2, 0);
      setPWM(3, 1);
      Serial.print("Set "); Serial.println(s);
    break;
    case 12:
      setPWM(0, 0);
      setPWM(1, 0);
      setPWM(2, 1);
      setPWM(3, 1);
      Serial.print("Set "); Serial.println(s);
    break;
    case 13:
      setPWM(0, 1);
      setPWM(1, 0);
      setPWM(2, 1);
      setPWM(3, 1);
      Serial.print("Set "); Serial.println(s);
    break;
    case 14:
      setPWM(0, 0);
      setPWM(1, 1);
      setPWM(2, 1);
      setPWM(3, 1);
      Serial.print("Set "); Serial.println(s);
    break;
    case 15:
      setPWM(0, 1);
      setPWM(1, 1);
      setPWM(2, 1);
      setPWM(3, 1);
      Serial.print("Set "); Serial.println(s);
    break;
   }
}

void setPWM(int channel, int OnOff)
{
  if(OnOff == 1)
  {
    muxes.setPWM(channel*4, 0, 4095);
    muxes.setPWM(channel*4+1, 0, 4095);
    muxes.setPWM(channel*4+2, 0, 4095);
    muxes.setPWM(channel*4+3, 0, 4095);
  }
  else
  {
    
    Serial.println("-0");
    muxes.setPWM(channel*4, 4095, 0 );
      Serial.println("-1");
    muxes.setPWM(channel*4+1, 4095, 0 );
     Serial.println("-2");
    muxes.setPWM(channel*4+2, 4095, 0 );
     Serial.println("-3");
    muxes.setPWM(channel*4+3, 4095, 0 );
     Serial.println(millis());
  }      
}
*/
