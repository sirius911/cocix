#include "Se_Soigner.h"
#include <cstring>
#include <iostream>

using namespace std;

Se_Soigner::Se_Soigner(){

	id = 14;
	strcpy(action, "Se soigner");;
	chaleur = 0.02f;
	eau = 0.1f;
	calorie = 1.0f;
	duree = 5;
	deplacement = false;
	peut_etre_stoppee = false;
	terminee = false;
	temps_ecoule = 0;
}

void Se_Soigner::identifie(){

	cout << "identifie() dans <Se_Soigner.cpp>\n";
	//return true;

}