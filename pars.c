//#############################################################
//Terminalserver
//--------------------
//Dennis Rudy und David Sigler	Labor Mikrocontroller WS 12/13
//Dateiname: pars.c
//#############################################################

//Funktion zum Zerlegt der Eingabe,
//Rückgabe von int Werten zum Aufrufen der entsprechenden Fktionen
//gibt Parameter per pointer zurück.

					//char Rückgabewerte entsprächend des erkannten Befehls:
					//
					//1 LED on
					//2 LED off
					//3 Taster
					//4 Trap on
					//5 Trap off
					//6 Help
					//-1 Fehler (Befehl existiert nicht -> wurde falsch geschrieben o.ä.)

 signed char pars(char in[20], char *p)
{
	char led[]="LED";				//"Vergleichs arrays
	char taster[]="Taster";			//
	char trap[]="Trap";				//
	char help[]="Help";
	char on[]="on";
	char off[]="off";
	char blink[]="blinken";
		
	unsigned char i=0;
	char select=0;			//Erkannter Befehl
	
	// Selects setzen: 
	
	
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
	
	// Switch Case von Select ausführen
	
	switch(select)				//liest den letzten Teil des Befehles aus und ruft dann entsprechende Fkt. auf.		
	{
		case 1:							//wenn erster Teil "LED" war
		{	
			if (7<(in[4]-48) || (in[4]-48)<0)
			{
				output("Befehl nicht möglich. Nur 0-7 als Parameter zulässig");
				outwert('\n');
				break;
			}
			else
			{					
				*p=((in[4])-48);						//liest den parameter aus und übergibt ihn per pointer zur main
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
			
			for (i=0; in[i+6]==blink[i]; i++) //LED x blinken
			{
				if (i==6)
				{
					return 7;												
				}
			}
			
			for (i=0; in[i+5]=='\0'; i++)		//LED X an/aus?
			{
				return 8;
			}
			
			return -1;										//wenn kein passender folgebefehl kommt -> fehler
		}
		
		case  2:															//Taster
		{
			if (7<((in[7])-48) || (in[7]-48)<0)
			{
				output("Befehl nicht möglich. Nur 0-7 als Parameter zulässig");
				outwert('\n');
				break;
			} 
			else
			{
				*p=(in[7]-48);						//liest den parameter aus und übergibt ihn per pointer zur main
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
				}
			}
			
			for (i=0;in[i+5]==off[i];i++)
			{
				if (i==3)
				{
					return 5;		//Trap off
				}
			}
			return -1;
		}
		
		case 4:
		{
			return 6;			//Help hat keine Parameter zum auswerten
		}
		
		default:
		{
			return -1;			//Befehl existiert nicht!
		}
	}
	
}
