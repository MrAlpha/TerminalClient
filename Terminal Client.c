
//#include "limits.h"
#include <avr/io.h>									//Headerdatei zur Registerdefinition einbinden
#include <avr/interrupt.h> 					//Headerdatei zur Definition der Interruptvektoren einbinden

void output(char[]);								//Funktionsprototypen
void outwert(char);

#include "config.c"
#include "output.c"									//Includen der Funktionen in extra Dateien
#include "pars.c"
#include "set_led.c"
#include "read_switch.c"
#include "help.c"
#include "read_led.c"

#define MAX_INPUT 20							//Definiert die maximale Größe des Eingabearrays.

/************************************************************************/
/* Globale Variablen                                                    */
/************************************************************************/
char timer1_overflowCount=0;			
char timer2_overflowCount=0;

unsigned char blink_state=0;	//Variable zum Speichern des Blinkzustandes in binärer Form. 

int main(void) 
{
	/************************************************************************/
	/* Locale Variablen                                                     */
	/************************************************************************/
	
	char in[MAX_INPUT];						//Array zum Speichern der über den USART empfangenen Zeichen
	char i=0;	
	char para=0;
	char *ppara= &para;						//pointer auf "para" zur übergabe der Parameter aus "pars()"
	char trap_state=0;						//Speichert den Zustand d. Trapfunktion (an/aus)
	
	/************************************************************************/
	/* Konfigurieren der verwendeten Module                                 */
	/************************************************************************/
	
	config();											//ruft die Fkt. config auf.
																//konfiguriert werden: USART, Timer1, Timer2, PortA und PortB.
																//Globale Interrupts werden eingeschaltet

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
			if ((i==0) && trap_state)	//wenn trap_state==1 (Trap angeschalten) Trap Interrupt nach Eingabe wieder aktivieren
			{
				TIFR |= (1<<TOV1);			//Interrupt Flag zurücksetzen -> keine Trap Meldung unmittelbar nach beenden der Eingabe
				TIMSK	|= (1<<TOIE1);		//Trap Interrupt einschalten.
			}
			
			while ( !(UCSRA & (1<<RXC)) )
			{
													//warten bis Daten empfangen werden
			}
			
			TIMSK	&= ~(1<<TOIE1);			//Trap Interrupt während Eingabe deaktivieren

			in[i]=UDR;								//Ankommendes Byte in "in" Array schreiben...
			

			if(in[i]==13)							//Wenn Eingabe 13 (Enter) war...
			{
				in[i]='\0';								//...terminierende 0 ins Array
				outwert('\n');						//Zeilen und spaltenrücklauf
				break;										//eingabe beenden.
			}
			
			outwert(in[i]);						//...und gleich als Echo wieder raushauen.
		
			if (in[i]==127)						//wenn Eingabe == Backspace (ASCII 127) Arrayindex i wieder um 2 verringern
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
				TIMSK	|= (1<<TOIE1);    // Trap Interrupt freischalten
				trap_state=1;						//
				break;
			}
			
			case 5:		//5 Trap off
			{
				TIMSK	&= ~(1<<TOIE1);    // Trap Interrupt sperren
				trap_state=0;
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

/************************************************************************/
/* Interrupt Service Routine Timer 1 (16 bit)                                                                     */
/************************************************************************/
ISR(TIMER1_OVF_vect)
{
		timer1_overflowCount += 1;
		
		if(timer1_overflowCount>=3)
		{
			timer1_overflowCount = 0;
			output("--------------------------------");
			outwert('\n');
			output("Hier spricht Ihre Trap funktion!");
			outwert('\n');
			output("--------------------------------");
			outwert('\n');
			output("Aktueller Status:  ");
			outwert('\n');
			for (char x=0;x<=7;x++)
			{
				read_led(x);
			}
			outwert('\n');
		}
	
}
/************************************************************************/
/* Interrupt Service Routine!!! Timer 2  (8 bit)                                                                   */
/************************************************************************/
ISR( TIMER2_OVF_vect )
{
	
	timer2_overflowCount += 1;
	
	if(timer2_overflowCount>=100)		//zähler zum verringern des Taktes
	{
			timer2_overflowCount = 0;			
			PORTA ^= (blink_state);    // LEDs toggeln	
	}		
}
