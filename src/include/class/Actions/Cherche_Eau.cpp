#include "Cherche_Eau.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <map>
#include "../../monde.h"
#include "../Cocix.h"

using namespace std;

Cherche_Eau::Cherche_Eau(){
	charge();
}

bool Cherche_Eau::valide_Action(const Cocix* , const bool verbal){
	// on peut toujours chercher !
	return true;
}

void Cherche_Eau::charge(){
	set_id( 2 );
	strcpy(action, "je cherche de l'eau");
	strcpy(desire, "Chercher de l'eau");
	chaleur = 0.02f;
	eau = 1.0f;
	calorie = 1.0f;
	set_duree(0);
	deplacement = true;
	peut_etre_stoppee = true;
}
void Cherche_Eau::go(Cocix *cocix, const bool verbal){
	
	cout << ".........................................................................\n";
	if(verbal) Actions::index();
	cout << "CHERCHE de L'eau ....\n";

	short case_arrivee;
	case_arrivee = meilleur_case( cocix->case_presence, EAU, true);

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
		if(verbal) cout << "Je cherche au hasard\n"; 

		cout << "\n\t\t******A FAIRE !! HASARD !! ****** \n";
	}
	if(bouge(cocix->id,cocix->case_presence,case_arrivee)) 
	{
				cocix->case_presence = case_arrivee;
				if(verbal) cout << " en " << case_arrivee << "...\n";
	}
	else 
	{
				if(verbal) cout << " impossible !	\n";
	}


	le_temps_s_ecoule();
	
	cout << "\n";
	Actions::affiche_action(false);
	cout << ".........................................................................\n";

}