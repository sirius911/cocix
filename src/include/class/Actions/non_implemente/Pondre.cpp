#include "Pondre.h"
#include <cstring>
#include <iostream>
using namespace std;

Pondre::Pondre(){

	id = 9;
	strcpy(action, "Pondre");;
	chaleur = 0.1f;
	eau = 3.0f;
	calorie = 3.0f;
	duree = 5;
	deplacement = false;
	peut_etre_stoppee = false;
	terminee = false;
	temps_ecoule = 0;
}

void faire(){
	cout << "Pondre\n";
}

bool valide_Action(){
	//cout << "NON IMPLÉMENTÉE !\n",
	return false;
}