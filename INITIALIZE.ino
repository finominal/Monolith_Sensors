

#define mux0  2
#define mux1  3
#define mux2  4
#define mux3  5

#define mux4  9
#define mux5  10
#define mux6  11
#define mux7  12

#define mux8  14
#define mux9  15
#define mux10 16
#define mux11 17

#define mux12 20
#define mux13 21
#define mux14 22
#define mux15 23


void InitializePins()
{

  pinMode(mux0,INPUT_PULLUP);
  pinMode(mux1,INPUT_PULLUP);
  pinMode(mux2,INPUT_PULLUP);
  pinMode(mux3,INPUT_PULLUP);
  
  pinMode(mux4,INPUT_PULLUP);
  pinMode(mux5,INPUT_PULLUP);
  pinMode(mux6,INPUT_PULLUP);
  pinMode(mux7,INPUT_PULLUP);
  
  pinMode(mux8,INPUT_PULLUP);
  pinMode(mux9,INPUT_PULLUP);
  pinMode(mux10,INPUT_PULLUP);
  pinMode(mux11,INPUT_PULLUP);
  
  pinMode(mux12,INPUT_PULLUP);
  pinMode(mux13,INPUT_PULLUP);
  pinMode(mux14,INPUT_PULLUP);
  pinMode(mux15,INPUT_PULLUP);
      

  pinMode(13,OUTPUT);
  digitalWrite(13,LOW); //show us it's working. 
}

void flash()
{
  digitalWrite(13,HIGH); //show us it's working. 
  delayMicroseconds(100);
  digitalWrite(13,LOW); //show us it's working.
  }


