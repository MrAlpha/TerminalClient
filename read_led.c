//reads the state of an LED

void read_led(char p)
{
	char temp=PINA;
	temp &= (1<<p);
	
	if (temp!=0)
	{
		output("LED ");	//Led p aus
		outwert(p+48);
		output(" ausgeschaltet");
		outwert('\n');
	}
	else
	{
		output("LED "); //Led p an
		outwert(p+48);
		output(" eingeschaltet");
		outwert('\n');
	}
	
}