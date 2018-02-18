#include "Cherche_Malade.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <map>
#include "../../monde.h"
#include "../Cocix.h"

using namespace std;

Cherche_Malade::Cherche_Malade(){
	charge();
}

bool Cherche_Malade::valide_Action(const Cocix* , const bool verbal){
	// on peut toujours chercher !
	return true;
}

void Cherche_Malade::charge(){
	set_id( CHERCHE_MALADE );
	strcpy(action, "je cherche un malade");
	strcpy(desire, "Chercher un malade");
	set_chaleur(0.02f);
	set_eau(1.0f);
	set_calorie(1.0f);
	set_duree(0);
	deplacement = true;
	peut_etre_stoppee = true;
}
void Cherche_Malade::go(Cocix *cocix, const bool verbal){
	
	cout << ".........................................................................\n";
	if(verbal) Actions::index();
	cout << "CHERCHE un malade ....\n";

	short case_arrivee;
	case_arrivee = meilleur_case_malade( cocix->get_case_presence(), cocix ,verbal);

	if(case_arrivee > 0){
		if(verbal)
		{
			cout << "Case où je veux aller : ";
			affiche_case(case_arrivee,false);
			cout << "\nJe bouge ...";
		}
		// je bouge en case_arrivée
		
		

	}
	else
	{
		// je bouge au hasard
		if(verbal) cout << "... au hasard \n"; 
		case_arrivee = case_hasard(cocix->get_case_presence());
	}
	if(bouge(cocix->id, cocix->get_case_presence(), case_arrivee, verbal)) 
	{
				cocix->set_case_presence(case_arrivee);
				if(verbal) cout << " en " << case_arrivee << "...\n";
				set_action_terminee(true);
	}
	else 
	{
				set_action_terminee(false);
				le_temps_s_ecoule();
	}	
	cout << "\n";
	Actions::affiche_action(false);
	cout << ".........................................................................\n";

}