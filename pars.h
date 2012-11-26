
//Funktion zum Zerlegt der Eingabe,
//Rückgabe von Werten zum Aufrufen der entsprechenden Fktionen
//gibt Parameter per pointer zurück.

					//Rückgabewerte entsprächend des erkannten befehls:
					//
					//1=LED on
					//2=LED off
					//3=Taster
					//4=Trap on
					//5=Trap off
					//6=Help
					//-1 Fehler (Befehl existiert nicht -> wurde falsch geschrieben o.ä.)

int pars(char in[20], int *ppara)	//->evtl. als rückgabegröße char???
{
	char led[]="LED";				//"Vergleichs arrays
	char taster[]="Taster";			//
	char trap[]="Trap";				//
	char help[]="Help";
	char on[]="on";
	char off[]="off";
		
	char i=0;
	char select=0;			//Erkannter Befehl
	//char *ppara;			//Pointer zur Übergabe des Ausgelesenen Parameters an die Main.
	
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
		case 1:					//liest den letzten Teil des Befehles aus und ruft dann entsprechende Fkt. auf.				
		{	
			if (7<in[4]<0)
			{
				output("Befehl nicht möglich. Nur 0-7 als Parameter zulässig");
				break;
			}
			else
			{	
												
				ppara=in[4];						//liest den parameter aus und übergibt ihn per pointer zur main
			}
						
			for (i=0; in[i+6]==on[i]; i++)
			{
				if (i==1)
				{
					return 1;					//LED on
					//break;
				}
			}
			
			for (i=0;in[i+6]==off[i]; i++)
			{
				if (i==2)
				{
					return 2;					//LED off
					//break;
				}
			}
			break;
		}
		
		case  2:
		{
			if (7<in[7]<0)
			{
				output("Befehl nicht möglich. Nur 0-7 als Parameter zulässig");
				break;
			} 
			else
			{
				ppara=in[7];						//liest den parameter aus und übergibt ihn per pointer zur main
			}
			
			
			return 3;					//Taster
			//break;
		}
		
		case  3:
		{
			for (i=0;in[i+5]==on[i];i++)
			{
				if (i==2)
				{
					return 4;		//Trap on
					//break;
				}
			}
			
			for (i=0;in[i+5]==off[i];i++)
			{
				if (i==3)
				{
					return 5;		//Trap off
					//break;
				}
			}
			break;
		}
		
		case 4:
		{
			return 6;			//Help
			//break;
		}
		
		default:
		{
			return -1;
			//output("Befehl existiert nicht!");
			//break;
		}
	}
}
