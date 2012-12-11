//function to read state of switch 0-7

//#include "output.c"

void read_switch(signed char *p)
{
	signed char place = (signed char) *p;
	signed char temp=PINB;
	temp &= (1<<*p);
	
	if (temp!=0)
	{
		output("Taster ");	//Taster *p gedrückt
		outwert((unsigned char) *p);
		output("nicht gedrückt");
		outwert('\n');
	}
	else
	{
		output("Taster"); //Taster *p nicht gedrückt
		outwert((unsigned char) *p);
		output(" gedrückt");
		outwert('\n');
	}	
}