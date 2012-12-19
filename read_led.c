//reads the state of an LED

void read_led(char p)
{
	char temp=PINA;
	temp &= (1<<p);
	
	if (temp!=0)
	{
		output("LED ");	//Taster p gedr�ckt
		outwert(p+48);
		output(" ausgeschaltet");
		outwert('\n');
	}
	else
	{
		output("LED "); //Taster p nicht gedr�ckt
		outwert(p+48);
		output(" eingeschaltet");
		outwert('\n');
	}
	
}