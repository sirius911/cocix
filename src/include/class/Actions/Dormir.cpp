#include "Dormir.h"
#include <cstring>
#include <iostream>
using namespace std;


Dormir::Dormir(){

	set_id( 6 );
	strcpy(action, "Je dors");
	strcpy(desire, "dormir");
	set_chaleur(-0.05f);
	set_eau(0.01f);
	set_calorie(0.01f);
	set_duree(0);
	deplacement = false;
	peut_etre_stoppee = true;
}

bool Dormir::valide_Action(const Cocix* , bool verbal){
	
	if(verbal) cout << " Peut toujours dormir !";
	return true;
}

void Dormir::go(Cocix*,bool verbal){
	cout <<  "...................................................\n";
	if(verbal) Actions::index();
	cout << "ACTION => DORT ....\n";
	if(verbal) cout << " ~~~~~~~~ RONFLEMENT ~~~~~~~~\n";

	//On incrémente le temps de l'action
	le_temps_s_ecoule(verbal);
	cout << " ~~~~~~~~ RONFLEMENT ~~~~~~~~\n";
	if(verbal) cout << "...................................................\n";
}
