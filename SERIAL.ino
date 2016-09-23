
void CheckForSerialRequest()
{
  if(Serial.available())
  {
    flash();
    char startChar = Serial.read();

    if (startChar == '!') 
    {
      if(debug)Serial.println("Sending Data");
      SendSensorData();
    }
    else
    {
      if(debug) 
      {
        Serial.print("I am sorry I dont know what "); 
        Serial.print(startChar); 
        Serial.println(" is."); 
      }
    }
  }
}


void SendSensorData()
{
  //can send a header as 1024 ?
  Serial.write(sensorSendBuffer, 46);
  //can send a footer as 1025 ?
  if(debug) Serial.println("Sent");
}



