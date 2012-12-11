
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