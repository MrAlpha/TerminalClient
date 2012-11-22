
// 
// ------------------------------------------------------------------------------

#include <avr/io.h>	
//#include <util/delay.h>								//Headerdatei einbinden zur Registerdefinition

void output(char[100]);

int main(void) {
	
	char in[20]={0};
	char out[100]={0};	
	unsigned char i=0;							//Variable zum Zwischenspeichern deklarieren
	
	UCSRB = (1<<RXEN) | (1<<TXEN);        			//USART Receiver und Transmitter einschalten
													//die nötigen Ausgangspins des Controllers werden
													//automatisch auf USART-Funktionalität umgeschalten
    UCSRC = (1<<URSEL)|(3<<UCSZ0);    				//Asynchron, keine Parität, 1 Stoppbit, 8 Datenbits
													//URSEL muss für Zugriff auf UCSRC gesetzt sein
 
    UBRRH = 0;										//Einstellen der Baudrate
    UBRRL = 51;										//Werte aus der Tabelle im Datenblatt
	
	//Hauptprogramm (Endlosschleife)
	while(1)
	{
		for(i=0;i<20;i++)
		{
			while ( !(UCSRA & (1<<RXC)) )
			{
				//warten bis Daten empfangen werden
			}

			in[i]=UDR;

			while( !( UCSRA & (1<<UDRE) ))
			{
			}				//warten bis "USART Data Register Empty" gesetzt ist

			UDR = in[i];

			if(in[i]==13)
			{
				while( !( UCSRA & (1<<UDRE) ))
				{
				}		//warten bis "USART Data Register Empty" gesetzt ist
			
				UDR=11;
				break;
			}

		}	
	if(i==20)
	{	
		output("Zu viele Zeichen im Befehl, höchstens 20 Erlaubt!!!");
	}
	
	}
	
	



	return 0;
}






void output(char out[100])
{	
	while( !( UCSRA & (1<<UDRE) )){}
	UDR=13;
	while( !( UCSRA & (1<<UDRE) )){}
	UDR=11;
	for(int i=0;out[i];i++)
	{
		while( !( UCSRA & (1<<UDRE) ))
		{
		}
		UDR=out[i];
	}
	while( !( UCSRA & (1<<UDRE) )){}
	UDR=32;
}
