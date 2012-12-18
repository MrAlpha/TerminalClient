//function to read state of switch 0-7

//#include "output.c"

void read_switch(char p)
{
	char temp=PINB;
	temp &= (1<<p);
	
	if (temp!=0)
	{
		output("Taster ");	//Taster p gedrückt
		outwert(p+48);
		output(" nicht gedrückt");
		outwert('\n');
	}
	else
	{
		output("Taster "); //Taster p nicht gedrückt
		outwert(p+48);
		output(" gedrückt");
		outwert('\n');
	}	
}