#include "Cherche_Nourriture.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <map>
#include "../../monde.h"
#include "../Cocix.h"

using namespace std;

Cherche_Nourriture::Cherche_Nourriture(){
	charge();
}
Cherche_Nourriture::Cherche_Nourriture(short x_case_nourriture){
	charge();
	//Action_alternative = new Dormir();
	case_nourriture = x_case_nourriture;
}

bool Cherche_Nourriture::valide_Action(const bool verbal){
	// on peut toujours chercher !
	return true;
}

void Cherche_Nourriture::charge(){
	set_id( 3 );
	strcpy(action, "Chercher de la nourriture");
	chaleur = 0.02f;
	eau = 1.0f;
	calorie = 1.0f;
	set_duree(0);
	deplacement = true;
	peut_etre_stoppee = true;
}
void Cherche_Nourriture::go(Cocix *cocix, const bool verbal){
	
	cout << ".........................................................................\n";
	if(verbal) Actions::index();
	cout << "CHERCHE de La nourriture ....\n";

	short case_arrivee;
	case_arrivee = meilleur_case( cocix->case_presence, NOURRITURE, true, verbal);

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
		if(verbal) cout << "Je cherche au hasard...\n"; 
	}
	if(bouge(cocix->id, cocix->case_presence, case_arrivee, verbal)) 
	{
				cocix->case_presence = case_arrivee;
				if(verbal) cout << " en " << case_arrivee << "...\n";
				set_action_terminee(true);
	}
	else 
	{
				if(verbal) cout << " impossible !	\n";
				set_action_terminee(false);
				le_temps_s_ecoule();
	}	
	cout << "\n";
	Actions::affiche_action(false);
	cout << ".........................................................................\n";

}