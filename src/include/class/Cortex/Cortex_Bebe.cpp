#include "Cortex_Bebe.h"
#include "../../constantes.h"
#include "../Cocix.h"
#include <cstring>
#include <iostream>


using std::cout;

Cortex_Bebe::Cortex_Bebe()
{
	strcpy(nom,"Bébé");
}

void Cortex_Bebe::gestion_Etat(Cocix* cocix, const bool verbal)
{
	Cortex::gestion_Etat(cocix,verbal);

}

bool Cortex_Bebe::decide_Desire(Cocix* cocix, const bool verbal)
{
	Cortex::decide_Desire(cocix,verbal);	// besoins vitaux
	return false;
}