// Alhimiq.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Himik.h"
int main()
{
	Himik ico(1, 4, 3, 10);
	ico.addFoundFormula("Metal + Stone = Gold");
	ico.addFoundFormula("Fire + Earth = Metal");
	ico.addFoundFormula("/Fire");
	ico.addFoundFormula("Energy + Gold + Spirit = Philosopher's Stone");
	ico.addFoundFormula("Spirit + Air = Energy");
	ico.addFoundFormula("Water + Air = Energy");
	ico.addFoundFormula("Air + Air = Spirit");
	ico.addFoundFormula("Fire + Water + Earth = Gold");
	ico.addFoundFormula("Water + Earth = Stone");
	ico.addFoundFormula("Energy + Earth = Stone");
	ico.getFoundBook().print();
	ico.isItPossibleToOptainPS();
}
 