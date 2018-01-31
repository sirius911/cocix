#include "Deposer.h"
#include <cstring>
#include <iostream>

using namespace std;

Deposer::Deposer(){

	id = 16;
	strcpy(action, "Déposer");;
	chaleur = 0.02f;
	eau = 1.0f;
	calorie = 1.0f;
	duree = 3;
	deplacement = false;
	peut_etre_stoppee = false;
	terminee = false;
	temps_ecoule = 0;
}
void Deposer::identifie(){

	cout << "identifie() dans <Deposer.cpp>\n";
	//return true;

}