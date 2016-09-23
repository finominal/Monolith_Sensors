
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
        muxToSet = startChar-49;
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



