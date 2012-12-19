
#include <avr/io.h>									//Headerdatei einbinden zur Registerdefinition
#include "output.c"		

void output(char[]);
void outwert(char);

#include "pars.c"
#include "set_led.c"
#include "read_switch.c"
#include "help.c"
#include "read_led.c"

#define MAX_INPUT 20

int main(void) 
{
	
	char in[MAX_INPUT];	
	//char pfeil_links[3]={27,91,68}
	char i=0;	
	char para=0;
	char *ppara= &para;						//pointer auf "para" zur übergabe der Parameter aus "pars()"
	
	UCSRB = (1<<RXEN) | (1<<TXEN);        //USART Receiver und Transmitter einschalten
																				//die nötigen Ausgangspins des Controllers werden
																				//automatisch auf USART-Funktionalität umgeschalten
													
  UCSRC = (1<<URSEL)|(3<<UCSZ0);    				//Asynchron, keine Parität, 1 Stoppbit, 8 Datenbits
																						//URSEL muss für Zugriff auf UCSRC gesetzt sein
 
  UBRRH = 0;										//Einstellen der Baudrate
  UBRRL = 51;										//Werte aus der Tabelle im Datenblatt

/************************************************************************/
/* PORT C für LEDs:                                                     */
/************************************************************************/	

	DDRA = 0xff;							//Port A als Ausgang Definieren (für die LEDs)
	PORTA = 0xff;							//Alle Pins an Port A auf 1 setzen -> LEDs sind low activ;

/************************************************************************/
/* PORT B für Taster:                                                   */
/************************************************************************/
	DDRB= 0x00;							//Port B als Eingang (für Taster)
	PORTB= 0xff;						//Pull-ups on

/************************************************************************/
/*  Hauptprogramm (Endlosschleife)                                      */
/************************************************************************/
	while(1)
	{
		for (i=0;i<=MAX_INPUT; i++)		//"in" Array nullen -> reste entfernen
		{
			in[i]=0;
		}
		
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
				outwert('\n');						//Zeilen und spaltenrücklauf
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
			output("Zu viele Zeichen im Befehl, höchstens 20 Erlaubt!!!");
		}
/************************************************************************/
/* Parsen des Eingegebenen Befehls mit "pars()" und Übergabe der Werte an die Ausführenden Funktionen   */
/************************************************************************/

		switch(pars(in, ppara))
		{
			case 1:		//1 LED on
			{
				set_led(1,para);
				break;
			}
			
			case 2:		//2 LED off
			{
				set_led(0,para);
				break;
			}
			
			case 3:		//3 Taster abfragen
			{
			read_switch(para);
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
				help();
				break;
			}
			
			case 7: //7 Blinken
			{
				set_led(2,para);
				break;
			}
			
			case 8:	//Led lesen
			{
				read_led(para);
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
		}
	}
	
	return 0;
}
