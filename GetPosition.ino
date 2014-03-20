const char startOfNumberDelimiter = 'I';
const char endOfNumberDelimiter   = '\r';

void GetPosition(int motorNr){
  shaftEncoder(motorNr);
  Position[motorNr] = (drehwert);
  //delay(10);
  //Serial.println("motor " + String(motorNr) + "Position now: " + String(drehwert));
}


void shaftEncoder(int motorNr){
	Serial2.print("#" + String(motorNr) + "I\r");
	delay(10);
        while (Serial2.available())
	processInput();
}

void processNumber (const long n)
{
	drehwert = n;
}  // end of processNumber

void processInput ()
{
	static long receivedNumber = 0;
	static boolean negative = false;
	static boolean numberTrigger = false; //trigger if add the read number to the target sum value
	byte c = Serial2.read ();
	
	switch (c)
	{
		case endOfNumberDelimiter:
		if(numberTrigger == true) {
		if (negative) 
			processNumber (- receivedNumber);
		else
			processNumber (receivedNumber);
		numberTrigger = false;
		}
		break;
		
		case startOfNumberDelimiter:
		receivedNumber = 0;
		negative = false;
		numberTrigger = true;
		break;
		
		case '0' ... '9':
		if(numberTrigger) {
			receivedNumber *= 10;
			receivedNumber += c - '0';
		}
		break;
		
		case '-':
		if(numberTrigger)
			negative = true;
		break;
		
		case '+':
		if(numberTrigger)
			negative = false;
		break;
		
		default:
		Serial.write(c);
		Serial.println();
		break;
		
	} // end of switch
}  // end of processInput
