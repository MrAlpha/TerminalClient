
#include <avr/io.h>									//Headerdatei einbinden zur Registerdefinition
#include "output.c"			
#include "pars.c"
#include "set_led.c"
#include "read_switch.c"
//#include <avr/interrupt.h>						

//void output(char[100]);

#define MAX_INPUT 20

int main(void) 
{
	
	char in[MAX_INPUT]={0};
	char out[100]={0};	
	signed char i=0;	
	signed char para=0;
	signed char *ppara= &para;						//pointer auf "para" zur �bergabe der Parameter aus "pars()"
	
	UCSRB = (1<<RXEN) | (1<<TXEN);        			//USART Receiver und Transmitter einschalten
													//die n�tigen Ausgangspins des Controllers werden
													//automatisch auf USART-Funktionalit�t umgeschalten
													
  UCSRC = (1<<URSEL)|(3<<UCSZ0);    				//Asynchron, keine Parit�t, 1 Stoppbit, 8 Datenbits
													//URSEL muss f�r Zugriff auf UCSRC gesetzt sein
 
  UBRRH = 0;										//Einstellen der Baudrate
  UBRRL = 51;										//Werte aus der Tabelle im Datenblatt

/************************************************************************/
/* PORT C f�r LEDs:                                                     */
/************************************************************************/	

	DDRC = 0xff;							//Port C als Ausgang Definieren (f�r die LEDs)
	PORTC = 0x00;							//Alle Pins an Port C auf 0 setzen;

/************************************************************************/
/* PORT B f�r Taster:                                                   */
/************************************************************************/
	DDRB= 0x00;							//Port B als Eingang (f�r Taster)
	PORTB= 0xff;						//Pull-ups on

//	UCSRB=(1<<RXCIE);								//Setze RX Complete Interrupt Enable

//	sei;											//global interrupt enable

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

			in[i]=UDR;								//Ankommendes Byte in "in" Array schreiben

			while( !( UCSRA & (1<<UDRE) ))
			{
			}										//warten bis "USART Data Register Empty" gesetzt ist

			UDR = in[i];							//empfangenes Byte als Echo zur�ck senden

			if(in[i]==13)							//Wenn Eingabe 13 (Enter) war...
			{
				while( !( UCSRA & (1<<UDRE) ))
				{
				}									//warten bis "USART Data Register Empty" gesetzt ist
			
				UDR=11;								//...Zeilenr�cklauf (11) schicken. (Enter wurde schon per echo geschickt)
				break;								//-> wir haben eine Terminierende "13" im Array
			}

		}	

		if(i>=MAX_INPUT)
		{
			output("Zu viele Zeichen im Befehl, h�chstens MAX_INPUT Erlaubt!!!");	//Funktion "output" aufrufen
		}
/************************************************************************/
/* Parsen des Eingegebenen Befehls mit "pars()" und �bergabe der Werte an die Ausf�hrenden Funktionen   */
/************************************************************************/

		switch(pars(in/*[MAX_INPUT]*/, ppara))
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
			
			case 3:		//3 Taster
			{
			//	read_switch();
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
				output("Der Befehl existiert nicht oder wurde falsch geschrieben!");
				output("Bitte nochmals versuchen");
				break;
			}
		}
		
		
	
	}
	
	



	return 0;
}