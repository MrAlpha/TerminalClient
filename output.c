
//Funktion zum Senden von char Strings über USART

void output(unsigned char out[])
{
		for(int i=0;out[i];i++)				//Ausgabe
		{
			while( !( UCSRA & (1<<UDRE) ))	//Warten
			{
			}
			UDR=out[i];						//Zeichen senden
		}
}
