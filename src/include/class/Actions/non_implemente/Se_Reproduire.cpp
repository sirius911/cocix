#include "Se_Reproduire.h"
#include <cstring>
#include <iostream>

using namespace std;

Se_Reproduire::Se_Reproduire(){

	id = 12;
	strcpy(action, "Se Reproduire");;
	chaleur = 0.1f;
	eau = 3.0f;
	calorie = 1.8f;
	duree = 5;
	deplacement = false;
	peut_etre_stoppee = false;
	terminee = false;
	temps_ecoule = 0;
}

void Se_Reproduire::identifie(){

	cout << "identifie() dans <Se_Reproduire.cpp>\n";
	//return true;

}