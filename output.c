
//Funktion zum Senden von char Strings �ber USART

void output(char out[100])
{
while( !( UCSRA & (1<<UDRE) ))			//Warten
UDR=13;									//Enter senden
										
while( !( UCSRA & (1<<UDRE) ))			//Warten
UDR=11;									//Zeilenr�cklauf senden

	for(int i=0;out[i];i++)				//Ausgabe
	{
		while( !( UCSRA & (1<<UDRE) ))	//Warten
		{
		}
		UDR=out[i];						//Zeichen senden
	}
	while( !( UCSRA & (1<<UDRE) )){}
	UDR=32;									//Leerzeichen
}
