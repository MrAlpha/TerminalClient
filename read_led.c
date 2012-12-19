//reads the state of an LED

void read_led(char p)
{
	char temp=PINA;
	temp &= (1<<p);
	
	if (temp!=0)
	{
		output("LED ");	//Taster p gedrückt
		outwert(p+48);
		output(" ausgeschaltet");
		outwert('\n');
	}
	else
	{
		output("LED "); //Taster p nicht gedrückt
		outwert(p+48);
		output(" eingeschaltet");
		outwert('\n');
	}
	
}