int SetNewStatus(int Status, int Gewicht4){
  
long ErrorWeg;
  
  if ((Gewicht4 > G_Schwellwert) && (GewichtChange4==true)){
      ErrorWeg = ErrorDist;
      PositionSoll[4] = PosUnten;
      }
  
  else if((Gewicht4 < G_Schwellwert) && (GewichtChange4==true)){
      ErrorWeg = 0;
      PositionSoll[4] = PosMitte;
  }
  
  else {
      GewichtChange4 = false;
      ErrorWeg = 0;
      PositionSoll[4] = PosMitte;
  }
  
  
  switch (Status)
	{
		case 1:
                PositionSoll[1] = PosMitte + (WegW1*2) - ErrorWeg;
                PositionSoll[2] = PosMitte - WegW1 - WegW2;
                PositionSoll[3] = PosMitte - WegW1 + WegW2; 
                MotorOben = 1;                		
		break;

                case 2:
		PositionSoll[1] = PosMitte + (WegW1*2) - ErrorWeg;
                PositionSoll[2] = PosMitte - WegW1 + WegW2;
                PositionSoll[3] = PosMitte - WegW1 - WegW2; 
                MotorOben = 1;
                break;

                case 3:
		PositionSoll[1] = PosMitte + (WegW1*2) - ErrorWeg;
                PositionSoll[2] = PosMitte - WegW1;
                PositionSoll[3] = PosMitte - WegW1; 
                MotorOben = 1;
                break;

                case 4:
                PositionSoll[1] = PosMitte;
                PositionSoll[2] = PosMitte - (WegW2 * 2);
                PositionSoll[3] = PosMitte + (WegW2 * 2) - ErrorWeg;    
                MotorOben = 3;            		
		break;
        
                case 5:
                PositionSoll[1] = PosMitte + WegW1 - ErrorWeg;
                PositionSoll[2] = PosMitte - (WegW1 * 0.5) - (WegW2 * 1.5);
                PositionSoll[3] = PosMitte - (WegW1 * 0.5) + (WegW2 * 1.5) - ErrorWeg;    
                MotorOben = 1;               		
		break;
  
                case 6:
                PositionSoll[1] = PosMitte - (WegW1 * 2);
                PositionSoll[2] = PosMitte + WegW1 - WegW2;
                PositionSoll[3] = PosMitte + WegW1 + WegW2 - ErrorWeg;   
                MotorOben = 3;             		
		break;

                case 7:
                PositionSoll[1] = PosMitte - WegW1*2;
                PositionSoll[2] = PosMitte + WegW1 + WegW2  - ErrorWeg;
                PositionSoll[3] = PosMitte + WegW1 - WegW2;   
                MotorOben = 2;             		
		break;

                case 8:
                PositionSoll[1] = PosMitte - (WegW1 * 2);
                PositionSoll[2] = PosMitte + WegW1 - ErrorWeg;
                PositionSoll[3] = PosMitte + WegW1 - ErrorWeg;                 
                MotorOben = 2;               		
		break;

                case 9:
                PositionSoll[1] = PosMitte;
                PositionSoll[2] = PosMitte + (WegW2 * 2) - ErrorWeg;
                PositionSoll[3] = PosMitte - (WegW2 * 2);                
                MotorOben = 2;                		
		break;

                case 10:
                PositionSoll[1] = PosMitte - WegW1;
                PositionSoll[2] = PosMitte + (WegW1 * 0.5) + (WegW2 * 1.5) - ErrorWeg;
                PositionSoll[3] = PosMitte + (WegW1 * 0.5) - (WegW2 * 1.5);                      
                MotorOben = 2;          		
		break;

                case 11:
                PositionSoll[1] = PosMitte - WegW1;
                PositionSoll[2] = PosMitte + (WegW1*0.5) - (WegW2 * 1.5);
                PositionSoll[3] = PosMitte + (WegW1*0.5) + (WegW2 * 1.5) - ErrorWeg;                   
                MotorOben = 3;             		
		break;
        
                case 12:
                PositionSoll[1] = PosMitte + WegW1 - ErrorWeg;
                PositionSoll[2] = PosMitte - (WegW1 * 0.5) + (WegW2 * 1.5) - ErrorWeg;
                PositionSoll[3] = PosMitte - (WegW1 * 0.5) - (WegW2 * 1.5);                		                
                MotorOben = 1;
		break;

                case 13:
                PositionSoll[1] = PosMitteOben - ErrorWeg;
                PositionSoll[2] = PosMitteUnten;
                PositionSoll[3] = PosMitteUnten;                		
                MotorOben = 1;
		break;

                case 14:
                PositionSoll[1] = PosMitte - ErrorWeg;
                PositionSoll[2] = PosMitte;
                PositionSoll[3] = PosMitte;                		
                MotorOben = 1;
	        break;

        }
        
        
        
        
        for (int i=1; i<=4; i++){
          if (PositionSoll[i] > AnschlagOben) PositionSoll[i] = AnschlagOben; 
          else if (PositionSoll[i] < AnschlagUnten) PositionSoll[i] = AnschlagUnten; 

        }        
}

//-----------------------------------------------------------------------------------------------------------------------

void UpdateMotorCharacter(){
  
  int MotorAnzahl = 3;
  
  long WegMax;        //Zwischenspeichern des längsten Fahrweges als Referenz für die Beschleunigungsberechnung
  long WegRest[5];
  int WegMax_Motor;    //MotorID des Motors mit dem längsten Fahrweg
  long GewichtDiff;   //Differenzgewicht zwischen bewegter Masse nach oben und unten
  
  float FaktorMotor[5];
  
  GewichtDiff = 0;
  WegMax = 0;
  
  if (GewichtChange4 == true) MotorAnzahl = 4;
  else MotorAnzahl = 3;  
  
  for (int i=1; i<=MotorAnzahl; i++){
    if (Richtung[i]==0) GewichtDiff += Gewicht[i];
    else GewichtDiff -= Gewicht[i];
    
    
    WegRest[i] = abs(PositionSoll[i]-Position[i]);
      if (WegRest[i] >= WegMax){
          WegMax = WegRest[i];
          WegMax_Motor = i;
      }
  }
  
  GewichtDiff = abs(GewichtDiff);
 
  for (int i=1;i<=MotorAnzahl;i++){
    FaktorMotor[i] = float(WegRest[i])/float(WegMax);    
    
}
  
  
    a_Ref = (map(GewichtDiff, 0., G_Max, a_Min*10, a_Max*10))/10.;

    
 for (int i=1;i<=MotorAnzahl;i++){
    a_Aktuell[i] = FaktorMotor[i]*(a_Ref);
    if (a_Aktuell[i] < 0.02) {a_Aktuell[i] = 0.02;}
    
    
    b_Value[i] = (pow((3000./((a_Aktuell[i]*BremsFaktor)+11.7)), 2.));
    a_Value[i] = (pow((3000./(a_Aktuell[i]+11.7)), 2.));
    }

      Serial2.println("#1b"+String(a_Value[1]));    //aktualisierte Beschleunigungsrampe setzen
      Serial2.println("#2b"+String(a_Value[2]));    //aktualisierte Beschleunigungsrampe setzen
      Serial2.println("#3b"+String(a_Value[3]));    //aktualisierte Beschleunigungsrampe setzen
      Serial2.println("#4b"+String(a_Value[4]));  //aktualisierte Maximalgeschwindigkeit setzen
      delay(10);
 
      Serial2.println("#1B"+String(b_Value[1]));    //aktualisierte Bremsrampe setzen
      Serial2.println("#2B"+String(b_Value[2]));    //aktualisierte Bremsrampe setzen
      Serial2.println("#3B"+String(b_Value[3]));    //aktualisierte Bremsrampe setzen
      Serial2.println("#4B"+String(b_Value[4]));    //aktualisierte Maximalgeschwindigkeit setzen
      delay(10);
            
      while (Serial2.read() >= 0); //mySerial Buffer leeren
   
  }
  
   
    
  

