//funkton to return a written help

//#include "output.c"

void help()
{
	output("---------------------------------------------------");
	outwert('\n');
	output("Hilfe:");
	outwert('\n');
	output("---------------------------------------------------");
	outwert('\n');
	output("Es werden folgende Befehle unterst�tzt:");
	outwert('\n');
	outwert('\n');
	output("LED X on -> schaltet LED X an");
	outwert('\n');
	output("LED X off -> schaltet LED X aus");
	outwert('\n');
	output("LED X -> gibt den Zustand der LED aus");
	outwert('\n');
	output("LED X blinken -> l�sst die LED blinken");
	outwert('\n');
	output("Taster X -> gibt den Zustand des Tasters aus");
	outwert('\n');
	output("Trap on -> schaltet die Trapfunktion an. Es werden in regelm��igen Abst�nden die Zust�nde der LEDs ausgegeben.");
	outwert('\n');
	output("Trap off");
	outwert('\n');
	output("Help -> gibt diese Hilfe aus. Die hier beschriebene Syntax entspricht der Implementierung im Programm");
	outwert('\n');outwert('\n');
	output("X steht jeweils f�r eine Variable von 0 bis 7");
	outwert('\n');
	output("---------------------------------------------------");
	outwert('\n');
	return;
}