//#############################################################
//Terminalserver
//--------------------
//Dennis Rudy und David Sigler	Labor Mikrocontroller WS 12/13
//Dateiname: io.c
//#############################################################

#include <avr/io.h>									//Headerdatei zur Registerdefinition einbinden
#include <avr/interrupt.h>

/************************************************************************/
/*   Funktion zum Senden von char Strings über USART                    */
/************************************************************************/
void output(char out[])
{
	for(int i=0;out[i];i++)				//Ausgabe
	{
		while( !( UCSRA & (1<<UDRE) ))	//Warten
		{
		}
		UDR=out[i];						//Zeichen senden
	}
}

/************************************************************************/
/*   Funktion zum Senden von char Werten über USART                    */
/************************************************************************/
void outwert(char out)
{
	if (out=='\n')
	{
		while( !( UCSRA & (1<<UDRE) ))	//Warten
		{
		}
		UDR=13;						//Zeichen senden
		
		while( !( UCSRA & (1<<UDRE) ))	//Warten
		{
		}
		UDR=11;						//Zeichen senden
		
		return;
	}

	
	while( !( UCSRA & (1<<UDRE) ))	//Warten
	{
	}
	UDR=out;						//Zeichen senden
}


/************************************************************************/
/* Funktion liest eingabe von UART in Array ein, gibt echo zurück und prüft auf erlaubte Eingabelänge */
/************************************************************************/
void input(char in[], char trap_state)
{
	unsigned char i=0;
	#define MAX_INPUT 20							//Definiert die maximale Größe des Eingabearrays.
	
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
	
}