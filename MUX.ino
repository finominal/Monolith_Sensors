

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

  #ifdef TWBR    
  // save I2C bitrate
  
  if(debug) Serial.println("FastI2C Enables");
  uint8_t twbrbackup = TWBR;
  // must be changed after calling Wire.begin() (inside pwm.begin())
  TWBR = 12; // upgrade to 400KHz!
#endif

   
  if(debug) Serial.println("Muxes Ready");

  allMuxOff();
}

void SetMux(byte s)
{
  InitializeMuxes();
  byte buf = s; 
  
  //Serial.print("Set:");Serial.println(buf, BIN);
  byte mask = 1;
  
  for(int i = 0; i<4;i++)//for each 4-lsb bits in the byte
  {
    if(buf & mask > 0)
    { 
      Serial.print(i); Serial.print("-On ");
      muxes.setPWM(i*4,   0, 4095);Serial.print(".");
      muxes.setPWM(i*4+1, 0, 4095);Serial.print(".");
      muxes.setPWM(i*4+2, 0, 4095);Serial.print(".");
      muxes.setPWM(i*4+3, 0, 4095);Serial.print(".");
    }
    else
    {
      Serial.print(i); Serial.print("-Off ");
       muxes.setPWM(i*4,   4095, 0);Serial.print(".");
       muxes.setPWM(i*4+1, 4095, 0);Serial.print("."); 
       muxes.setPWM(i*4+2, 4095, 0);Serial.print(".");
       muxes.setPWM(i*4+3, 4095, 0);Serial.print(".");
    }
    buf = buf>>1;
  }
  Serial.println("SetOK");
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


