//#############################################################
//Terminalserver
//--------------------
//Dennis Rudy und David Sigler	Labor Mikrocontroller WS 12/13
//Dateiname: read_led.c
//#############################################################

/************************************************************************/
/*Funktion reads the state of an LED                                    */
/************************************************************************/

void read_led(char ledToRead_parameter)
{
	extern unsigned char blink_state;
	char temp=(PINA & (1<<ledToRead_parameter));

	if(blink_state & (1<<ledToRead_parameter))	
	{
		output("LED ");	
		outwert(ledToRead_parameter+48);
		output(" blinkt");
		outwert('\n');
	}
	
	
	else if (temp!=0)
	{
		output("LED ");	//Led p aus
		outwert(ledToRead_parameter+48);
		output(" AUS");
		outwert('\n');
	}
	else
	{
		output("LED "); //Led p an
		outwert(ledToRead_parameter+48);
		output(" AN");
		outwert('\n');
	}
	
}