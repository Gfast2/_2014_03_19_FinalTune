void MotorStart(int MotorID){
     if (M_Done[MotorID] == true){
       String MotorIDFS = String(MotorID); 
       Serial2.println("#"+MotorIDFS+"A");
       delay(10);
       while (Serial2.read() >= 0); //mySerial Buffer leeren
     M_Done[MotorID] = false;
     }
}

//------------------------------------------------------------------

void MotorStop(int MotorID){
     if (M_Done[MotorID] == false){
       String MotorIDFS = String(MotorID);      
       Serial2.println("#"+MotorIDFS+"S1");
       delay(10);
       while (Serial2.read() >= 0); //mySerial Buffer leeren
       M_Done[MotorID] = true;
     }
}

//------------------------------------------------------------------


void MotorHardStop(int MotorID){
     if (M_Done[MotorID] == false){
       String MotorIDFS = String(MotorID);      
       Serial2.println("#"+MotorIDFS+"S0");
       delay(10);
       while (Serial2.read() >= 0); //mySerial Buffer leeren
       M_Done[MotorID] = true;
     }
}

//------------------------------------------------------------------

void SetMotorRichtung(int MotorID, int RichtungM){
    Serial2.println("#"+String(MotorID)+"d"+String(RichtungM));
    delay(10);
    while (Serial2.read() >= 0); //mySerial Buffer leeren
    Richtung[MotorID] = RichtungM;
}

//------------------------------------------------------------------

void SetMotor_a(int MotorID, long a_Value){
     Serial2.println("#"+String(MotorID)+"b"+String(a_Value));
     delay(10);   
}


//------------------------------------------------------------------

void SetMotor_vMax(int MotorID, long vMax_Value){
     Serial2.println("#"+String(MotorID)+"o"+String(vMax_Value));
     delay(10);
}

//------------------------------------------------------------------

void notAus() {
  while(Serial.available()) {
    char n = Serial.read();
    if (n == 'a'){
      Serial2.println("#*S1");
      delay(20);
    } 
  }
}

//------------------------------------------------------------------

void SetMotorStartValues(){
  
  Serial2.println("#*S0");
  delay(10);
  Serial2.println("#*i30"); //set motors' performance
  delay(10);
  Serial2.println("#*S"); //motor stop
  delay(10);
  Serial2.println("#*q0"); //Drehencoder direction exchange
  delay(10);
  Serial2.println("#*g32"); //Schrittmodus einstellen (Vollschritt etc.)
  delay(10);
  Serial2.println("#*:ramp_mode=0"); //Trapez-Rampe(0), Sinusrampe(1), Jerkfreerampe(2) Seite37
  delay(10);
  Serial2.println("#*p5"); // '5' - Drehzahlmodus, '2' - "Absolute Positionierung" Seite47
  delay(10);
  Serial2.println("#*u100"); //Minimalfrequenz Seite49
  delay(10);
  Serial2.println("#*o5000"); //Maximalfrequenz Seite50
  delay(10);
  Serial2.println("#*b41649"); //equal to 3Hz/ms, set acceleration Seite51
  delay(10);
  Serial2.println("#1B0");    //aktualisierte Bremsrampe setzen
  delay(10);
  Serial2.println("#*d1");//'0' - links, '1' - rechts
  //delay(300000);
/*
  while(Serial2.available()){
    Serial.print(Serial2.read());
  } 
*/

  while (Serial2.read() >= 0); //mySerial Buffer leeren
  
}

