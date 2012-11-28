//function to read state of switch 0-7

//#include "output.c"

void read_switch(signed char *p)
{
	signed char temp=PINB;
	temp &= (1<<*p);
	if (temp!=0)
	{
		output("");	//Taster *p gedrückt
	}
	else
	{
		output(""); //Taster *p nicht gedrückt
	}	
}