
//Funktion zum Senden von char Strings �ber USART

void output(char out[100])
{
	if ((out[0]=='\') && (out[1]=='n'))	//newline. Befehl "\n" muss einzeln ohne String gesendet werden
	{
		while( !( UCSRA & (1<<UDRE) ))			//Warten
		UDR=13;									//Enter senden

		while( !( UCSRA & (1<<UDRE) ))			//Warten
		UDR=11;									//Zeilenr�cklauf senden

	}


	for(int i=0;out[i];i++)				//Ausgabe
	{
		while( !( UCSRA & (1<<UDRE) ))	//Warten
		{
		}
		UDR=out[i];						//Zeichen senden
	}
}
