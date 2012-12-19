//funktion to set/reset LED 0-7

void set_led(char state, char p)
{
	if (state==1)				//wenn gewünscht ist ein Bit zu löschen (eine LED einzuschalten)...
	{
		PORTA &= ~(1<<p);		//...setze das Bit aus dem Parameter auf low ->LED anschalten!
	}
	else if (state==0)			//wenn gewünscht ist ein Bit zu setzen (eine LED auszuschalten)...
	{
		PORTA |= (1<<p);		//...setze das Bit aus dem Parameter auf high ->LED ausschalten!
	}
	else if (state==2)
	{
		PORTA ^=(1<<p);
	}
	
}