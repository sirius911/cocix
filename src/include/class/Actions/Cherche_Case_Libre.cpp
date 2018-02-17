#include "Cherche_Case_Libre.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include "../../monde.h"
//#include <map>

#include "../Cocix.h"

using namespace std;

Cherche_Case_Libre::Cherche_Case_Libre(){
	charge();
}

bool Cherche_Case_Libre::valide_Action(const Cocix* , const bool verbal){
	// on peut toujours chercher !
	return true;
}

void Cherche_Case_Libre::charge(){
	set_id( 10 );
	strcpy(action, "je cherche une case libre");
	strcpy(desire, "Chercher une case libre");
	set_chaleur(0.02f);
	set_eau(1.0f);
	set_calorie(0.9f);
	set_duree(0);
	deplacement = true;
	peut_etre_stoppee = true;
}
void Cherche_Case_Libre::go(Cocix *cocix, const bool verbal){
	
	cout << ".........................................................................\n";
	if(verbal) Actions::index();
	cout << "CHERCHE une case libre ....\n";

	short case_arrivee;
	case_arrivee = case_libre( cocix->get_case_presence());

	if(case_arrivee > 0){
		if(verbal)
		{
			cout << "Case où je veux aller : ";
			affiche_case(case_arrivee,false);
			cout << "\nJe bouge ...";
		}
		// je bouge en case_arrivée
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
		

	}
	else
	{
		// je bouge au hasard
		if(verbal) cout << "Pas de place libres autour de moi... je bouge au hasard \n"; 
		case_arrivee = case_hasard(cocix->get_case_presence());
	}

	if(bouge(cocix->id, cocix->get_case_presence(), case_arrivee, verbal)) 
	{
				cocix->set_case_presence(case_arrivee);
				if(verbal) cout << " en " << case_arrivee << "...\n";
				set_action_terminee(false);
				le_temps_s_ecoule();
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