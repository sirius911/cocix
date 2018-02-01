#include "Dormir.h"
#include <cstring>
#include <iostream>
using namespace std;


Dormir::Dormir(){

	set_id( 6 );
	strcpy(action, "Je dors");
	strcpy(desire, "dormir");
	chaleur = -0.05f;
	eau = 0.01f;
	calorie = 0.01f;
	set_duree(0);
	deplacement = false;
	peut_etre_stoppee = true;
}

void Dormir::faire(){
	cout << "Je dort\n";
	le_temps_s_ecoule();
}

bool Dormir::valide_Action(bool verbal){
	// peut toujours dormir
	cout << " Peut toujours dormir !";
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
