int GetStatus(long Gewicht1, long Gewicht2, long Gewicht3, long Gewicht4){
  
//---------Faktor Waage für Relative Positionierung

            
    WegW1 = abs(Gewicht1 - (Gewicht2 + Gewicht3)) * FaktorGewicht + WegMinimum;
    if (WegW1 > RelativMaxWeg) WegW1 = RelativMaxWeg;   
    
    WegW2 = abs(Gewicht2 - Gewicht3) * FaktorGewicht + WegMinimum;
    if (WegW2 > RelativMaxWeg) WegW2 = RelativMaxWeg;   
        
//---------Ende Faktor Waage für Relative Positionierung


    if ((Gewicht4 > G_Schwellwert) && (GewichtChange4==false)){
      GewichtChange4 = true;
    }
    
    
    if (Gewicht1 - (Gewicht2 * 2) < (G_Schwellwert*-1)){
        
        if (Gewicht1 - (Gewicht3 * 2) < (G_Schwellwert*-1)){
            
            if (Gewicht2 - Gewicht3 > G_Schwellwert){
              return 1;                    //Status 1
            }
      
            else if (Gewicht2 - Gewicht3 < (G_Schwellwert*-1)){
              return 2;                    //Status 2
            }
      
            else {
              return 3;                    //Status 3
            }
      
        }
        
        else if (Gewicht1 - (Gewicht3 * 2) > G_Schwellwert){
            return 4;
        }
        
        else{ 
            return 5;
        }
    }
    
    else if (Gewicht1 - (Gewicht2 * 2) > G_Schwellwert){
        
        if (Gewicht1 - (Gewicht3 * 2) > G_Schwellwert){
            
            if (Gewicht2 - Gewicht3 > G_Schwellwert){
                return 6;
            }
            
            else if (Gewicht2 - Gewicht3 < (G_Schwellwert*-1)){
                return 7;
            }
            
            else{
                return 8;
            }
        
        }
        
        else if (Gewicht1 - (Gewicht3 * 2) < (G_Schwellwert*-1)){
            return 9; 
        }
        
        else {
            return 10;
        }
    }
    
    else {
      
        if (Gewicht2 - Gewicht3 > G_Schwellwert){
            return 11;
        }
    
        else if (Gewicht2 - Gewicht3 < (G_Schwellwert*-1)){
            return 12;
        }
        
        else if ((Gewicht1 > (G_Schwellwert*-1)) && (Gewicht1 < G_Schwellwert*1)) {
            return 13;
        }
        
        else {
         if ( (Gewicht1 >= Minimalgewicht) && (Gewicht2 >= Minimalgewicht) && (Gewicht3 >= Minimalgewicht)){  
            return 14;
         }
         else{
            return 15;
         }
         
        }
      
    }
    
    
    
 
}
