int pars(char in[20])
{
	char led[]="LED";
	char taster[]="Taster";
	char trap[]="Trap";
	char help[]="Help";
	char on[]="on";
	char off[]="off";
		
	char i=0;
	char select=0;			//Erkannter Befehl
	char para=0;			//Ausgelesener Parameter zur Übergabe an "mach" Funktion.
	
	for(i=0; in[i]==led[i]; i++)	//Vergleichen: Eingabe==LED?
	{
		if(i==2)
		{								//wenn ja, select=1
			select=1;
			break;
		}	
	}
	
	for(i=0; in[i]==taster[i]; i++)	//Vergleich: Eingabe==Taster?
	{
		if(i==5)					//wenn ja, select=2
		{
			select=2;
			break;
		}
	}
	
	for (i=0; in[i]==trap[i]; i++)	//Vergleich: Eingabe == Trap?
	{
		if (i==3)					//wenn ja, select=3
		{
			select=3;
			break;
		}
	}
	
	for (i=0; in[i]==help[i]; i++)	//Verleich: Eingabe == Help?
	{
		if (i==3)					//wenn ja, select=4
		{
			select=4;
			break;
		}
	}
	
	switch(select)
	{
		case 1:
		{
			para=in[4];
			
			for (i=0; in[i+6]==on[i]; i++)
			{
				if (i==1)
				{
					//Aufruf LED_on mit Parameter(para)
					break;
				}
			}
			
			for (i=0;in[i+6]==off[i]; i++)
			{
				if (i==2)
				{
					//Aufruf LED_off mit Parameter(para)
					break;
				}
			}
			break;
		}
		
		case  2:
		{
			break;
		}
		
		case  3:
		{
			break;
		}
		
		case 4:
		{
			break;
		}
		
		default:
		{
			//Fehlermeldung raushauen, Befehl existiert nicht!!!
			break;
		}
	}
}