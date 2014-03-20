void MotorFahrt(){
 
  for (int i=1;i<=4;i++){
    
    if (M_Done[i]==true){
      
      if ((Position[i]-PositionSoll[i]) > Schwellwert){
       SetMotorRichtung(i, 0);
       MotorStart(i);
      } 
      
      else if ((Position[i]-PositionSoll[i]) < (Schwellwert*-1)){
       SetMotorRichtung(i, 1);
       MotorStart(i);
      } 
      
    
    }
    
    else {
      PositionAlt[i] = Position[i];
    
      GetPosition(i);
      delay(10);      

      if ((Position[i] < AnschlagUnten)||(Position[i] > AnschlagOben)){
          MotorHardStop(i);
          MotorStart(i);
      }

//-----------Druchlaufoption      
      
      
      if (((Position[i]-PositionSoll[i]) > ((Schwellwert))/(Durchlauf[i]+1)) && (Richtung[i] == 1)){      //Bei Bewegung nach oben, dann Ummkehren wenn Motorposition größer ist als SollPosition + Schwellwert 
       SetMotorRichtung(i, 0);
       Durchlauf[i] += 1;   
       }
      
      else if (((Position[i]-PositionSoll[i]) < ((Schwellwert*-1))/(Durchlauf[i]+1)) && (Richtung[i] == 0)){    //Bei Bewegung nach unten, dann Ummkehren wenn Motorposition kleiner ist als SollPosition - Schwellwert
       SetMotorRichtung(i, 1);
       Durchlauf[i] += 1;

       }

      
//-----------Druchlaufoption

      
       else if (((Position[i]-PositionSoll[i]) < (Schwellwert/(Durchlauf[i]+1)) && (Richtung[i] == 0)) && (Durchlauf[i] > 1)){
       // if (((Position[i]-PositionSoll[i]) < Schwellwert) && (Richtung[i] == 0)){ 
            MotorStop(i);
        }

      else if (((Position[i]-PositionSoll[i]) > ((Schwellwert*-1)/(Durchlauf[i]+1))) && (Richtung[i] == 1) && (Durchlauf[i] > 1)){
       // else if (((Position[i]-PositionSoll[i]) > ((Schwellwert*-1))) && (Richtung[i] == 1)){
        
        MotorStop(i);
       }
      
    }
     
    
  }
 
  
}
