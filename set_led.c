//funktion to set/reset LED 0-7

void set_led(char state, char ledtoChange_parameter)
{
	extern unsigned char blink_state;
	
	if (state==1)								//wenn gew�nscht ist ein Bit zu l�schen (eine LED einzuschalten)...
	{
		blink_state &= ~(1<<ledtoChange_parameter);		//blinkregister f�r die LED auf 0 -> Blinken aus
		PORTA &= ~(1<<ledtoChange_parameter);					//...setze das Bit aus dem Parameter auf low ->LED anschalten!
	}
	else if (state==0)					//wenn gew�nscht ist ein Bit zu setzen (eine LED auszuschalten)...
	{
		blink_state &= ~(1<<ledtoChange_parameter);		//..setzt das gew�nschte Bit in der blink Statusvariablen auf 0 ->Blinken d. LED Ausschalten
		PORTA |= (1<<ledtoChange_parameter);					//...setze das Bit aus dem Parameter auf high ->LED ausschalten!
	}
	else if (state==2)					//Wenn gew�nscht ist eine LED blinken zu lassen:
	{
		blink_state |= (1<<ledtoChange_parameter);		//setzt das gew�nschte Bit in der blink Statusvariablen auf 1 ->LED blinkt
	}
	
}