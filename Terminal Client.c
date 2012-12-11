
#include <avr/io.h>									//Headerdatei einbinden zur Registerdefinition
#include "output.c"		
#include "outwert.c"	
void output(unsigned char[]);
void outwert(char);
#include "pars.c"
#include "set_led.c"
#include "read_switch.c"

#define MAX_INPUT 20

int main(void) 
{
	
	unsigned char in[MAX_INPUT]={0};
	//char out[100]={0};	
	char i=0;	
	signed char para=0;
	signed char *ppara= &para;						//pointer auf "para" zur �bergabe der Parameter aus "pars()"
	
	UCSRB = (1<<RXEN) | (1<<TXEN);        //USART Receiver und Transmitter einschalten
																				//die n�tigen Ausgangspins des Controllers werden
																				//automatisch auf USART-Funktionalit�t umgeschalten
													
  UCSRC = (1<<URSEL)|(3<<UCSZ0);    				//Asynchron, keine Parit�t, 1 Stoppbit, 8 Datenbits
																						//URSEL muss f�r Zugriff auf UCSRC gesetzt sein
 
  UBRRH = 0;										//Einstellen der Baudrate
  UBRRL = 51;										//Werte aus der Tabelle im Datenblatt

/************************************************************************/
/* PORT C f�r LEDs:                                                     */
/************************************************************************/	

	DDRA = 0xff;							//Port C als Ausgang Definieren (f�r die LEDs)
	PORTA = 0xff;							//Alle Pins an Port C auf 1 setzen -> LEDs sind low activ;

/************************************************************************/
/* PORT B f�r Taster:                                                   */
/************************************************************************/
	DDRB= 0x00;							//Port B als Eingang (f�r Taster)
	PORTB= 0xff;						//Pull-ups on

/************************************************************************/
/*  Hauptprogramm (Endlosschleife)                                      */
/************************************************************************/
	while(1)
	{
		for(i=0;i<MAX_INPUT;i++)
		{
			while ( !(UCSRA & (1<<RXC)) )
			{
													//warten bis Daten empfangen werden
			}

			in[i]=UDR;								//Ankommendes Byte in "in" Array schreiben...
			

			if(in[i]==13)							//Wenn Eingabe 13 (Enter) war...
			{
				in[i]='\0';						//...terminierende 0 ins Array
				outwert('\n');						//Zeilen und spaltenr�cklauf
				break;									//eingabe beenden.
			}
			
			outwert(in[i]);						//...und gleich als Echo wieder raushauen.
		
			if (in[i]==127)
			{
				i-=2;
			}
		}	
		

		if(i>=(MAX_INPUT))
		{
			output("Zu viele Zeichen im Befehl, h�chstens 20 Erlaubt!!!");
		}
/************************************************************************/
/* Parsen des Eingegebenen Befehls mit "pars()" und �bergabe der Werte an die Ausf�hrenden Funktionen   */
/************************************************************************/

		switch(pars(in, ppara))
		{
			case 1:		//1 LED on
			{
				set_led(1,ppara);
				break;
			}
			
			case 2:		//2 LED off
			{
				set_led(0,ppara);
				break;
			}
			
			case 3:		//3 Taster abfragen
			{
			read_switch(ppara);
				break;
			}
			
			case 4:		//4 Trap on
			{
				break;
			}
			
			case 5:		//5 Trap off
			{
				break;
			}
			
			case 6:		//6 Help
			
			{
				break;
			}
			
			case -1:		//-1 Fehler
			{
				output("Der Befehl existiert nicht!");
				outwert('\n');
				output("Bitte nochmals versuchen");
				outwert('\n');
				break;
			}
			
			case 7:	//Led flash
			{
				break;
			}
			
			case 8:	//Led lesen
			{
				break;
			}
		}
		
		
	
	}
	
	



	return 0;
}
