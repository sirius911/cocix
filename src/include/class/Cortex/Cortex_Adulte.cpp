#include "Cortex_Adulte.h"
#include "../../constantes.h"
#include "../Cocix.h"

#include <cstring>
#include <iostream>


#include "../Actions/Dormir.h"

//using std::cout;

Cortex_Adulte::Cortex_Adulte()
{
	strcpy(nom,"Adulte");
}

void Cortex_Adulte::gestion_Etat(Cocix* cocix, const bool verbal)
{
	Cortex::gestion_Etat(cocix,verbal);
}




bool Cortex_Adulte::decide_Desire(Cocix* cocix, const bool verbal)
{
	return Cortex::decide_Desire(cocix , verbal);
}