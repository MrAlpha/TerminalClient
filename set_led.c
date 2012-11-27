//funktion to set/reset LED 0-7

void set_led(signed char state, signed char *p)
{
	if (state==1)				//wenn gew�nscht ist ein Bit zu setzen (eine LED einzuschalten)...
	{
		PORTC |= (1<<*p);		//...setze das Bit auf das der Pointer zeigt auf high.
	}
	else if (state==0)			//wenn gew�nscht ist ein Bit zu l�schen...
	{
		PORTC &= ~(1<<*p);		//...setze das Bit aud das der Pointer zeigt auf low.
	}
	
}