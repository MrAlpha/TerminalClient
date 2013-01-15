//#############################################################
//Terminalserver
//--------------------
//Dennis Rudy und David Sigler	Labor Mikrocontroller WS 12/13
//Dateiname: HID.c
//#############################################################

#include <avr/io.h>								
#include "io.h"

/************************************************************************/
/*Funktion reads the state of an LED                                    */
/************************************************************************/

void read_led(char ledToRead_parameter)
{
	extern unsigned char blink_state;
	char temp=(PINA & (1<<ledToRead_parameter));

	if(blink_state & (1<<ledToRead_parameter))
	{
		output("LED ");
		outwert(ledToRead_parameter+48);
		output(" blinkt");
		outwert('\n');
	}
	
	
	else if (temp!=0)
	{
		output("LED ");	//Led p aus
		outwert(ledToRead_parameter+48);
		output(" AUS");
		outwert('\n');
	}
	else
	{
		output("LED "); //Led p an
		outwert(ledToRead_parameter+48);
		output(" AN");
		outwert('\n');
	}
	
}


/************************************************************************/
/* Function to read state of switch 0-7                                 */
/************************************************************************/

void read_switch(char switchToRead_parameter)
{
	char temp=PINB;
	temp &= (1<<switchToRead_parameter);
	
	if (temp!=0)
	{
		output("Taster ");	//Taster gedrückt
		outwert(switchToRead_parameter+48);
		output(" nicht gedrückt");
		outwert('\n');
	}
	else
	{
		output("Taster "); //Taster nicht gedrückt
		outwert(switchToRead_parameter+48);
		output(" gedrückt");
		outwert('\n');
	}
}

/************************************************************************/
/*   Funktion to set/reset/toggle LED 0-7                               */
/************************************************************************/

void set_led(char state, char ledtoChange_parameter)
{
	extern unsigned char blink_state;
	
	if (state==1)								//wenn gewünscht ist ein Bit zu löschen (eine LED einzuschalten)...
	{
		blink_state &= ~(1<<ledtoChange_parameter);		//blinkregister für die LED auf 0 -> Blinken aus
		PORTA &= ~(1<<ledtoChange_parameter);					//...setze das Bit aus dem Parameter auf low ->LED anschalten!
	}
	else if (state==0)					//wenn gewünscht ist ein Bit zu setzen (eine LED auszuschalten)...
	{
		blink_state &= ~(1<<ledtoChange_parameter);		//..setzt das gewünschte Bit in der blink Statusvariablen auf 0 ->Blinken d. LED Ausschalten
		PORTA |= (1<<ledtoChange_parameter);					//...setze das Bit aus dem Parameter auf high ->LED ausschalten!
	}
	else if (state==2)					//Wenn gewünscht ist eine LED blinken zu lassen:
	{
		blink_state |= (1<<ledtoChange_parameter);		//setzt das gewünschte Bit in der blink Statusvariablen auf 1 ->LED blinkt
	}
	
}

/************************************************************************/
/*   Funkton to return a written help                                   */
/************************************************************************/

void help()
{
	output("---------------------------------------------------");
	outwert('\n');
	output("Hilfe:");
	outwert('\n');
	output("---------------------------------------------------");
	outwert('\n');
	output("Es werden folgende Befehle unterstützt:");
	outwert('\n');
	outwert('\n');
	output("LED X on -> schaltet LED X an");
	outwert('\n');
	output("LED X off -> schaltet LED X aus");
	outwert('\n');
	output("LED X -> gibt den Zustand der LED aus");
	outwert('\n');
	output("LED X blinken -> lässt die LED blinken");
	outwert('\n');
	output("Taster X -> gibt den Zustand des Tasters aus");
	outwert('\n');
	output("Trap on -> schaltet die Trapfunktion an. Es werden in regelmäßigen Abständen die Zustände der LEDs ausgegeben.");
	outwert('\n');
	output("Trap off");
	outwert('\n');
	output("Help -> gibt diese Hilfe aus. Die hier beschriebene Syntax entspricht der Implementierung im Programm");
	outwert('\n');outwert('\n');
	output("X steht jeweils für eine Variable von 0 bis 7");
	outwert('\n');
	output("---------------------------------------------------");
	outwert('\n');
}