#include "Rentrer.h"
#include <cstring>
#include <iostream>

#include "../../monde.h"

using namespace std;

Rentrer::Rentrer(){
	charge();
}

Rentrer::Rentrer(const short x_case_presence, const short x_case_naissance)
{
	charge();
	case_presence = x_case_presence;
	case_naissance = x_case_naissance;
	//Action_Alternative = new Rentre(case_presence, case_naissance);
}

bool Rentrer::valide_Action(const bool verbal){
	if(verbal) cout << "Peut toutjours rentrer !\n";

	return true;
}

void Rentrer::charge()
{
	set_id(11);
	strcpy(action, "Rentrer");;
	chaleur = 0.02f;
	eau = 1.0f;
	calorie = 1.0f;
	set_duree(0);
	deplacement = true;
	peut_etre_stoppee = true;
}
//   *************************************** A C T I O N ***********************
void Rentrer::go(Cocix *cocix,bool verbal)
{
	short case_arrivee = 0;
	cout <<  "...................................................\n";
	if(verbal) Actions::index();
	cout << "ACTION => Rentre....\n";
		
	// verifi qu'on est pas déjà arrivé
	if(case_presence == case_naissance){
		if(verbal) cout << "Je suis déjà arrivé(e) !\n";
		set_action_terminee(true);
	} else
	{
		case_arrivee = aller(case_presence , case_naissance, verbal);
	}

	//On incrémente le temps de l'action
	le_temps_s_ecoule(verbal);
		
	cout << "...................................................\n";
}

