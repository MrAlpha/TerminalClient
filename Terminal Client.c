
#include <avr/io.h>									//Headerdatei einbinden zur Registerdefinition
#include "output.h"			
#include "pars.h"
#include <avr/interrupt.h>						

//void output(char[100]);

int main(void) 
{
	
	char in[20]={0};
	char out[100]={0};	
	unsigned char i=0;							
	
	UCSRB = (1<<RXEN) | (1<<TXEN);        			//USART Receiver und Transmitter einschalten
													//die nötigen Ausgangspins des Controllers werden
													//automatisch auf USART-Funktionalität umgeschalten
													
    UCSRC = (1<<URSEL)|(3<<UCSZ0);    				//Asynchron, keine Parität, 1 Stoppbit, 8 Datenbits
													//URSEL muss für Zugriff auf UCSRC gesetzt sein
 
    UBRRH = 0;										//Einstellen der Baudrate
    UBRRL = 51;										//Werte aus der Tabelle im Datenblatt
	
	
//	UCSRB=(1<<RXCIE);								//Setze RX Complete Interrupt Enable

//	sei;											//global interrupt enable

	//Hauptprogramm (Endlosschleife)
	while(1)
	{
		for(i=0;i<20;i++)
		{
			while ( !(UCSRA & (1<<RXC)) )
			{
													//warten bis Daten empfangen werden
			}

			in[i]=UDR;								//Ankommendes Byte in "in" Array schreiben

			while( !( UCSRA & (1<<UDRE) ))
			{
			}										//warten bis "USART Data Register Empty" gesetzt ist

			UDR = in[i];							//empfangenes Byte als Echo zurück senden

			if(in[i]==13)							//Wenn Eingabe 13 (Enter) war...
			{
				while( !( UCSRA & (1<<UDRE) ))
				{
				}									//warten bis "USART Data Register Empty" gesetzt ist
			
				UDR=11;								//...Zeilenrücklauf (11) schicken. (Enter wurde schon per echo geschickt)
				break;								//-> wir haben eine Terminierende "13" im Array
			}

		}	

		if(i>=20)
		{
			output("Zu viele Zeichen im Befehl, höchstens 20 Erlaubt!!!");	//Funktion "output" aufrufen
		}
		
		pars(in);
	
	}
	
	



	return 0;
}