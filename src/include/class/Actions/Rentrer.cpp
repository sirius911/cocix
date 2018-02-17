#include "Rentrer.h"
#include <cstring>
#include <iostream>

#include "../../monde.h"

//#include "../Cocix.h"

using namespace std;

Rentrer::Rentrer(){
	charge();
}

bool Rentrer::valide_Action(const Cocix* , const bool verbal){
	if(verbal) cout << "Peut toutjours rentrer !\n";

	return true;
}

void Rentrer::charge()
{
	set_id(11);
	strcpy(action, "Je rentre");;
	strcpy(desire, "Rentrer");
	set_chaleur(0.02f);
	set_eau(1.0f);
	set_calorie(1.0f);
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
		
	//On incrémente le temps de l'action
	le_temps_s_ecoule(verbal);

	// verifi qu'on est pas déjà arrivé
	if(cocix->get_case_presence() == cocix->get_case_naissance()){
		if(verbal) cout << "Je suis déjà arrivé(e) !\n";
		set_action_terminee(true);
		//case_arrivee = case_naissance;
		return;
	}
		
	case_arrivee = aller(cocix->get_case_presence() , cocix->get_case_naissance(), verbal);
	if(bouge(cocix->get_id(),cocix->get_case_presence(), case_arrivee, verbal))
	{
			if( cocix->rentree() )
			{
				set_action_terminee(true);
				if(verbal) cout << "Je suis rentré(e).\n";
			}
			else
			{
				set_action_terminee(false);
				if(verbal) cout << "Je suis en chemin.\n";
			}
			cocix->set_case_presence(case_arrivee);
	}	
	cout << "...................................................\n";
}

