//funkton to return a written help

#include "output.c"

void help()
{
	output("Hilfe:");
	output("------------------------------");
	output("Es werden folgende Befehle unterstützt:");
	output();
	output("LED X on");
	output("LED X off");
	output("LED X flash");
	output("Taster X");
	output("LED X");
	output("Trap on");
	output("Trap off");
	output("help");
	output();
	output("X steht jeweils für eine Variable von 0 bis 7");
}