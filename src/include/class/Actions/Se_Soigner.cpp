#include "Se_Soigner.h"
#include <cstring>
#include <iostream>
#include <iomanip>

#include "Rentrer.h"
using namespace std;

Se_Soigner::Se_Soigner()

{
	charge();
	
	Action_alternative = new Rentrer();
}

bool Se_Soigner::valide_Action(const Cocix* cocix, const bool verbal){
	if(verbal) cout << "Suis-je chez moi ?\n";
	//cout << case_presence << "=="<<case_naissance;
	return (cocix->rentree());
}

void Se_Soigner::charge()
{
	set_id(14);
	strcpy(action, "Je me soigne");
	strcpy(desire, "Me soigner");
	chaleur = 0.02f;
	eau = 0.1f;
	calorie = 1.0f;
	set_duree(5);
	deplacement = false;
	peut_etre_stoppee = false;

}

//   *************************************** A C T I O N ***********************
void Se_Soigner::go(Cocix *cocix,bool verbal)
{
	float quantite_soins;

	cout <<  "...................................................\n";
	if(verbal) Actions::index();
	cout << "ACTION => Se Soigner....\n";
	quantite_soins = cocix->genome[SOINS].valeur;
	if(verbal) cout << "Quantité de soins appliquée : " << setprecision(3) << quantite_soins << setprecision(2)<<" pdv\n";
	cocix->Sante.modif(quantite_soins, &cocix->balises, verbal);
	le_temps_s_ecoule(verbal);
		
	cout << "...................................................\n";
}

