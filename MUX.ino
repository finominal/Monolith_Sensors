int muxChannelReadOrderIndex[] = {
                              10, 11, 12, 13, 14, 
                               5,  6,  7,  8,  9, 
                               0,  1,  2,  3,  4 
                              };

int muxInputPinLeft[] = {4, 17, 27,22, 5, 6 ,13,26}; //change for teensy
int muxInputPinRight[] = {18, 23, 24, 25, 12, 16, 20, 21}; //change for teensy



void InitializeMuxes()
{
  muxes.begin();
  muxes.setPWMFreq(1000);  // 1400 is max I think. about that. 
   delay(1);
   
  Serial.println("Muxes Ready");

   allMuxOff();
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



void allMuxOn()
{
  for( int i = 0; i<16;i++)
 {
   muxes.setPWM(i, 0, 4095);
 }
 Serial.println("All On");
}

void allMuxOff()
{
  for( int i = 0; i<16;i++)
 {
   muxes.setPWM(i, 4095, 0 );
 }
 Serial.println("All Off");
}

