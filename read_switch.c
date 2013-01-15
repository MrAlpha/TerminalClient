//#############################################################
//Terminalserver
//--------------------
//Dennis Rudy und David Sigler	Labor Mikrocontroller WS 12/13
//Dateiname: read_switch.c
//#############################################################

//function to read state of switch 0-7

//#include "output.c"

void read_switch(char switchToRead_parameter)
{
	char temp=PINB;
	temp &= (1<<switchToRead_parameter);
	
	if (temp!=0)
	{
		output("Taster ");	//Taster gedr�ckt
		outwert(switchToRead_parameter+48);
		output(" nicht gedr�ckt");
		outwert('\n');
	}
	else
	{
		output("Taster "); //Taster nicht gedr�ckt
		outwert(switchToRead_parameter+48);
		output(" gedr�ckt");
		outwert('\n');
	}	
}