#include "Cherche_Partenaire.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <map>
#include "../../reproduction.h"
#include "../Cocix.h"

using namespace std;

Cherche_Partenaire::Cherche_Partenaire(){
	charge();
}

bool Cherche_Partenaire::valide_Action(const Cocix* , const bool verbal){
	// on peut toujours chercher !
	return true;
}

void Cherche_Partenaire::charge(){
	set_id( 4 );
	strcpy(action, "je cherche un partenaire");
	strcpy(desire, "Chercher un partenaire");
	set_chaleur(0.02f);
	set_eau(1.0f);
	set_calorie(1.0f);
	set_duree(0);
	deplacement = true;
	peut_etre_stoppee = true;
}
void Cherche_Partenaire::go(Cocix *cocix, const bool verbal){
	
	cout << ".........................................................................\n";
	if(verbal) Actions::index();
	cout << "CHERCHE un partenaire ....\n";

	short case_arrivee;
	case_arrivee = meilleur_case_partenaire( cocix->get_case_presence(), cocix ,verbal);

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