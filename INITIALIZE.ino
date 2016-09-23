

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

  pinMode(mux0,INPUT);
  pinMode(mux1,INPUT);
  pinMode(mux2,INPUT);
  pinMode(mux3,INPUT);
  
  pinMode(mux4,INPUT);
  pinMode(mux5,INPUT);
  pinMode(mux6,INPUT);
  pinMode(mux7,INPUT);
  
  pinMode(mux8,INPUT);
  pinMode(mux9,INPUT);
  pinMode(mux10,INPUT);
  pinMode(mux11,INPUT);
  
  pinMode(mux12,INPUT);
  pinMode(mux13,INPUT);
  pinMode(mux14,INPUT);
  pinMode(mux15,INPUT);
      

  pinMode(13,OUTPUT);
  digitalWrite(13,LOW); //show us it's working. 
}

void flash()
{
  digitalWrite(13,HIGH); //show us it's working. 
  delayMicroseconds(200);
  digitalWrite(13,LOW); //show us it's working.
  }


