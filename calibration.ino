void calibration(){

LEDSerial.print("lt E0;");  
delay(1000);
LEDSerial.print("stt A B C D;");

SetMotorStartValues();
  
for (int i=1;i<=4;i++){
    weightRead(i);
    delay(5);
    }


    //---------------------------------------


    for (int i=1; i<=4;i++){
      EndSchalter[i]=digitalRead(EndSchalterPin[i]);
      if (EndSchalter[i] == 1){
        MotorStart(i);
      }
    }
    
    while((EndSchalter[1] == 1)||(EndSchalter[2] == 1)||(EndSchalter[3] == 1)||(EndSchalter[4] == 1)) {
      for (int i=1;i<=4;i++){
      EndSchalter[i] = digitalRead(EndSchalterPin[i]);
      if (EndSchalter[i] == 0) {
        MotorHardStop(i);
      }
      }
    }


    // -------------------------------------------------------------------------------------------------------------------------------
    // Motoren jetzt ganz oben
    // -------------------------------------------------------------------------------------------------------------------------------

    Serial2.println("#*o7000"); //Maximalfrequenz Seite50
    delay(10);
    Serial2.println("#*D0"); //Drehüberwachung Reset
    delay(10);

    for (int i = 1; i<=4; i++){
    SetMotorRichtung(i, 0);
    KippStatus[i] == 0;
    MotorStart(i);
    }




//-->     Serial.println("Motoren jetzt los nach unten");
    // -------------------------------------------------------------------------------------------------------------------------------
    // Motoren jetzt ganz unten und ausgeleert
    // -------------------------------------------------------------------------------------------------------------------------------

    while((Position[1] > kippPosUnten) || (Position[2] > kippPosUnten) || (Position[3] > kippPosUnten) || (Position[4] > kippPosUnten))
    {
//-->      Serial.println(Position[1]);
      
      for (int i=1; i<=4; i++){
        GetPosition(i);
        delay(10);
        if ((Position[i] <= kippPosition) && (KippStatus[i] == 0)) {
          KippStatus[i] = 1; 
          digitalWrite(MagnetPin[i],HIGH);
        }
      
        if (Position[i] <= kippPosUnten){
          MotorHardStop(i);
        }
      }
    }
    
    delay(100);

//-->     Serial.println("UNTEN");
    
    //GetPosition(i);
    //delay(10);

for (int i=1;i<=4;i++){
    SetMotorRichtung(i, 1);
    MotorStart(i);
}
    
//--> Serial.println("Wieder hoch!");


    while ((Position[1] < PosOben) || (Position[2] < PosOben) || (Position[3] < PosOben) || (Position[4] < PosOben)){
      
      for (int i=1; i<=4;i++){
        GetPosition(i);
        delay(10);
        if (Position[i] >= PosOben){
          MotorHardStop(i);
        }

        if ((Position[i] >= kippPosition) && (KippStatus[i] == 1)){
          KippStatus[i] = 0;
          digitalWrite(MagnetPin[i],LOW);
        }
      }
    }


    // -------------------------------------------------------------------------------------------------------------------------------
    // Motoren jetzt in der jeweiligen StartPosition
    // -------------------------------------------------------------------------------------------------------------------------------
 
 
    Serial2.println("#1o4000"); //Maximalfrequenz Seite50
    delay(10);
    Serial2.println("#2o4000"); //Maximalfrequenz Seite50
    delay(10);
    Serial2.println("#3o4000"); //Maximalfrequenz Seite50
    delay(10);
    Serial2.println("#4o4000"); //Maximalfrequenz Seite50
    delay(10);  

    for (int i=1;i<=4;i++){
    SetMotorRichtung(i, 0);  //runter
    MotorStart(i);
}

    while ((M_Done[1] == false) || (M_Done[2] == false) || (M_Done[3] == false) || (M_Done[4] == false)){
      
      for (int i=1; i<=4;i++){
        GetPosition(i);       
        /*if (abs(Position[i]-StartPosition[i]) < Schwellwert){
          MotorHardStop(i);
        }
        else if ((Position[i]<StartPosition[i])&&(Richtung[i] == 0)){
          SetMotorRichtung(i, 1);
        }
        
        else if ((Position[i]>StartPosition[i])&&(Richtung[i] == 1)){
          SetMotorRichtung(i, 0);
        }
        */
        if (Position[i] < StartPosition[i]){
          MotorHardStop(i);
          }
        delay(10);
//        Serial.print(".");

      }
    }
    
    
  
  delay(10);
  Serial2.println("#*o20000"); //Maximalfrequenz Seite50

  delay(1000);                 //Ausschwingzeit vor Nullreset Wägezellen      
        for (int i=1; i<=4;i++){
        delay(10);
        zero(i);
        //delay(10);
        while(Serial3.available() > 0){
          Serial3.read();
          }
        }
        
        StartWert = 0;
        StatusNeu = 13;
        StatusAlt = 13;

LEDSerial.print("kerze;");  
Waagezeit_inaktiv = millis();
Serial.println("Calibration finished");
   
}

