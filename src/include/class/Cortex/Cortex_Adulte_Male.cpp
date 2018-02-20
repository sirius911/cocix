#include "Cortex_Adulte_Male.h"
#include "../../constantes.h"
#include "../Cocix.h"

#include <cstring>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "../Actions/Actions.h"
//#include "../Actions/Agresser.h"
#include "../Actions/Boire.h"
#include "../Actions/Cherche_Eau.h"
#include "../Actions/Deposer.h"
#include "../Actions/Dormir.h"
#include "../Actions/Manger.h"
#include "../Actions/Pondre.h"
#include "../Actions/Recolter.h"
#include "../Actions/Cherche_Recolte.h"
#include "../Actions/Rentrer.h"
#include "../Actions/Se_Reproduire.h"
#include "../Actions/Se_Soigner.h"
#include "../Actions/Cherche_Partenaire.h"
#include "../Actions/Cherche_Case_Libre.h"
#include "../Actions/Soigner.h"
#include "../Actions/Cherche_Malade.h"


using std::cout;

Cortex_Adulte_Male::Cortex_Adulte_Male()
{
	strcpy(nom,"Adulte Male");
}

void Cortex_Adulte_Male::gestion_Etat(Cocix* cocix, const bool verbal)
{
	Cortex_Adulte::gestion_Etat(cocix,verbal);
}

bool Cortex_Adulte_Male::decide_Desire(Cocix* cocix, const bool verbal)
{
	if(Cortex_Adulte::decide_Desire(cocix , verbal))
	{
		// on continue ici les choix
		//MALE
    if(verbal) cout << " MALE ==> ";
        	if(cocix->cycle_sexuel() == 0)
        	{	//mature
        		// on regarde l'agressivité
        					if(cocix->agressive())
        						cout << "Agresser  ...non implémenté...";
        						//Desire = new Agresser();
        					else if(cocix->compassion())
       							cocix->Desire = new Soigner();
        					else
        						cocix->Desire = new Se_Reproduire();
        	} 
          else cocix->Desire = new Dormir();	//Immature
	}	

	cocix->Desire->affiche_desire(false);
	return true;
}