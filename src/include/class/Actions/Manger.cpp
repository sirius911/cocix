#include "Manger.h"
#include <cstring>
#include <iostream>
#include "../../monde.h"
#include "Cherche_Nourriture.h"

using namespace std;

Manger::Manger()
{
	charge();
}

Manger::Manger(short x_case_nourriture)
{
	charge();
	case_nourriture = x_case_nourriture;
	Action_alternative = new Cherche_Nourriture(case_nourriture);
}

bool Manger::valide_Action(const bool verbal)
{
	if(verbal) cout << " Y-a-t-il de la nourriture sur ma case ?... ";
	return((nourriture(case_nourriture) > 0));
}


void Manger::charge()
{
	set_id( 8 );
	strcpy(action, "Je mange");
	strcpy(desire, "manger");
	chaleur = -0.05f;
	eau = 0.5f;
	calorie = 0.5f;
	set_duree(5);
	deplacement = false;
	peut_etre_stoppee = false;
}

//   *************************************** A C T I O N ***********************
void Manger::go(Cocix *cocix,bool verbal)
{
	float quantite_prise, seuil_satiete;
	struct struct_xy xy;

	case_nourriture = cocix->case_presence;
	xy  = case_to_xy(case_nourriture);

	cout <<  "...................................................\n";
	if(verbal) Actions::index();
	cout << "ACTION => MANGE ....\n";
		
	// On met à jour la base de donnée du monde
	if(verbal) cout << "En case N° " << case_nourriture << " (" << xy.x << "," << xy.y << ") Il y a " << nourriture(case_nourriture) << " cal avant.\n";
	quantite_prise = prend_element(case_nourriture,cocix->genome[ASSIMILATION_CALORIQUE].valeur,EAU);
	cocix->Calorie.modif(quantite_prise, &cocix->balises,verbal);
		
	//On incrémente le temps de l'action
	le_temps_s_ecoule(verbal);
		
	if(verbal) cout << "Il y a maintenant "<< nourriture(case_nourriture) << " cal.\n";
	

	// on verifie la satiété pour l'eau la CoCiX n' plus soif si hydro==CH
		seuil_satiete = (cocix->genome[SATIETE].valeur * cocix->Calorie.capacite);
		if(verbal) cout << "Seuil de Saiété : " << seuil_satiete << " cal : ";
		if(cocix->Calorie.valeur > seuil_satiete){
			if(verbal) cout << " Atteint.\n";
		}
		else{
			if(verbal) cout << " Non Atteint.\n";
		}

		if(! valide_Action(verbal)){
			if(verbal) cout << "NON ! \n";
			set_action_terminee(true);
		} else {
			if(verbal) cout << "OUI !\n";
		}
	cout << "\n";
	Actions::affiche_action(false);
	cout << "...................................................\n";
}

