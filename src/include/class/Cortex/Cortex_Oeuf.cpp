#include "Cortex_Oeuf.h"
#include "../../constantes.h"
#include "../Cocix.h"
#include <cstring>
#include <iostream>


using std::cout;

Cortex_Oeuf::Cortex_Oeuf()
{

}

Cortex_Oeuf::Cortex_Oeuf(bool pondu)
{
	if(pondu) strcpy(nom,"Oeuf pondu");
	else strcpy(nom,"Oeuf non pondu");
}

void Cortex_Oeuf::gestion_Etat(Cocix* cocix, const bool verbal)
{
	cout << "\n****     C O R T E X   E T A T     ****\n";
	cout <<  "                  O E U F\n";
	cocix->prend_temperature(verbal);
	cocix->raz_balises(verbal);
	if(verbal) cout << "Température ("<< cocix->get_temp_exterieur() << " °C): \n";
	if(cocix->get_temp_exterieur() < 10.0f)
	{
		if(verbal) cout << " Temp ext < 10°C\n";
		cocix->Temperature.modif(-cocix->genome[Gene::TEMP].valeur, &cocix->balises,verbal); // on diminue la température de Genes.temp.valeur
	}
	else if(cocix->get_temp_exterieur() > 35.0f)
	{
		if(verbal) cout << "Temp ext > 35°C";
		cocix->Temperature.modif(+cocix->genome[Gene::TEMP].valeur, &cocix->balises, verbal);	// on augmente la température 
	}
}

bool Cortex_Oeuf::decide_Desire(Cocix* cocix, const bool verbal)
{
		// aucun désire
	return false;
}