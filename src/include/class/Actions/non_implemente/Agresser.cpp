#include "Agresser.h"
#include <cstring>
#include <iostream>

using namespace std;

Agresser::Agresser(){

	id = 18;
	strcpy(action, "Agresser");;
	chaleur = 0.3f;
	eau = 1.0f;
	calorie = 2.0f;
	duree = 5;
	deplacement = false;
	peut_etre_stoppee = false;
	terminee = false;
	temps_ecoule = 0;
}

void Agresser::identifie(){

	cout << "identifie() dans <Dormir.cpp>\n";
	//return true;

}