void weightRead(int TransmitterNum){
	int SignGewicht[5];
	int waageID = TransmitterNum;
	
	digitalWrite(chipDriver, HIGH); //send the command to weight transmitter asking the "netto weight"
	switch(waageID){
		case 1:
		//the XOR CRC code (here is 75) should be calculated.
		Serial3.write("$01t75\r"); //to send the command, on Baud 38400 takes nearly 2ms, than wait 1 to 2ms come answer.
		break;
		case 2:
		Serial3.write("$02t76\r");
		break;
		case 3:
		Serial3.write("$03t77\r");
		break;
		case 4:
		Serial3.write("$04t70\r");
		break;
		default:
		Serial.println("Weight Transmitter address not readable");
	}
	delay(1); //wait till the command to be totally send (in 11520 baud it should be 1 misc, 38400 c.a. 3 misc)
	digitalWrite(chipDriver, LOW); // receive the command from weight transmitter
	
	//parsing the answer
	/*
	* there should be three different possible answer from weight transmitter Seite.37
	* 1. Normal answer: &aaxxxxxxt\ckckCR a:address of WT, CK:CRC code
	* 2. Error answer: &aassO-Lst\ckck or &aassO-Fst\ckck s:space(32 ASCII) to indicate value can't be read
	**/
	while(Serial3.available() > 0){
		if (Serial3.read()==38){ //'&'
			waageID = ((Serial3.read()-48)*10);              //10er Stelle ID
			waageID = waageID + (Serial3.read()-48);         // total address
			
			SignGewicht[waageID] = Serial3.read();  //"-" bei negativem Wert, " " bei Error, andere sind normal
			if (SignGewicht[waageID] == 32){ // "space"
				GewichtStatus[waageID] = 2;
				Serial.println("Gewicht zu hoch!");
				Serial3.flush();
			}
			else if (SignGewicht[waageID] == 45) { //'-'
				SignGewicht[waageID] = -1;
				Gewicht[waageID] = ((Serial3.read()-48)*10000);
				Gewicht[waageID] += ((Serial3.read()-48)*1000);
				Gewicht[waageID] += ((Serial3.read()-48)*100);
				Gewicht[waageID] += ((Serial3.read()-48)*10);
				Gewicht[waageID] = -(Gewicht[waageID]+((Serial3.read()-48)));
				Serial3.flush();
				if (Serial3.read() == 't') {
					GewichtStatus[waageID] = 0;
				}
				else{
					GewichtStatus[waageID] = 1;
					Serial.println("Read value not correct");
				}
			}
			else if (SignGewicht[waageID] > 47 && SignGewicht[waageID] < 58) {
				Gewicht[waageID] = (SignGewicht[waageID]-48) * 100000; //this bit belongs to the read value too, when it isn't the '-'
				Gewicht[waageID] += ((Serial3.read()-48)*10000);
				Gewicht[waageID] += ((Serial3.read()-48)*1000);
				Gewicht[waageID] += ((Serial3.read()-48)*100);
				Gewicht[waageID] += ((Serial3.read()-48)*10);
				Gewicht[waageID] += ((Serial3.read()-48));
				Serial3.flush();
				if (Serial3.read() == 't'){
					GewichtStatus[waageID] = 0;
				}
				else {
					GewichtStatus[waageID] = 1;
					Serial.println("read value not correct");
				}
			}
			else{
				GewichtStatus[waageID] = 3;
				Serial.println("Read weight transmitter ERROR");
				Serial3.flush();
			}
		}
	}
}

void zero(int TransmitterNum){
  digitalWrite(chipDriver, HIGH);
  switch(TransmitterNum)
  {
  case 1:
    Serial3.write("$01ZERO03\r");
    break;
  case 2:
    Serial3.write("$02ZERO00\r");
    break;
  case 3:
    Serial3.write("$03ZERO01\r");
    break;
  case 4:
    Serial3.write("$04ZERO06\r");
  default:
    Serial.println("Zero setting address not readable");	
  }
  delay(5);
  digitalWrite(chipDriver, LOW);
  
} 
