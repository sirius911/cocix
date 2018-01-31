#include "Se_Rechauffer.h"
#include <cstring>
#include <iostream>

using namespace std;

Se_Rechauffer::Se_Rechauffer(){

	id = 10;
	strcpy(action, "Se Réchauffer");;
	chaleur = 0.0f;
	eau = 1.0f;
	calorie = 3.0f;
	duree = 0;
	deplacement = false;
	peut_etre_stoppee = true;
	terminee = false;
	temps_ecoule = 0;
}

void Se_Rechauffer::identifie(){

	cout << "identifie() dans <Se_Rechauffer.cpp>\n";
	//return true;

}