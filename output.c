//#############################################################
//Terminalserver
//--------------------
//Dennis Rudy und David Sigler	Labor Mikrocontroller WS 12/13
//Dateiname: output.c
//#############################################################

//Funktion zum Senden von char Strings über USART

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