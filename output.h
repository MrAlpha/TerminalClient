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