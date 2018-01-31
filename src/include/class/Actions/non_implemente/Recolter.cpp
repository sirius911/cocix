#include "Recolter.h"
#include <cstring>
#include <iostream>

using namespace std;

Recolter::Recolter(){

	id = 15;
	strcpy(action, "Recolter");;
	chaleur = 0.05f;
	eau = 1.0f;
	calorie = 1.0f;
	duree = 3;
	deplacement = false;
	peut_etre_stoppee = false;
	terminee = false;
	temps_ecoule = 0;
}

void Recolter::identifie(){

	cout << "identifie() dans <Recolter.cpp>\n";
	//return true;

}