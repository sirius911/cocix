#include "Se_Rechauffer.h"
#include <cstring>
#include <iostream>

//#include "Rentre.h"

using namespace std;

Se_Rechauffer::Se_Rechauffer(){
	charge();
}

Se_Rechauffer::Se_Rechauffer(const short x_case_presence, const short x_case_naissance)
{
	charge();
	case_presence = x_case_presence;
	case_naissance = x_case_naissance;
	//Action_Alternative = new Rentre(case_presence, case_naissance);
}

bool Se_Rechauffer::valide_Action(const bool verbal){
	if(verbal) cout << "Suis-je rentré(e) chez moi ? ";

	return(case_presence == case_naissance);
}

void Se_Rechauffer::charge()
{
	set_id(10);
	strcpy(action, "Se Réchauffer");;
	chaleur = 0.0f;
	eau = 1.0f;
	calorie = 3.0f;
	set_duree(0);
	deplacement = false;
	peut_etre_stoppee = true;
}
//   *************************************** A C T I O N ***********************
void Se_Rechauffer::go(Cocix *cocix,bool verbal)
{
	cout <<  "...................................................\n";
	if(verbal) Actions::index();
	cout << "ACTION => Se Rechauffer....\n";
		
	//On incrémente le temps de l'action
	le_temps_s_ecoule(verbal);
		
	if(verbal) 
	{
		cout << "Ma température avant l'action ";
		cocix->Temperature.affiche();
		cout << "\n";
	}
	
	// On augmente la température extérieur de la valeur Gene['temp']
	cocix->Temperature.modif( cocix->genome[TEMP].valeur , &cocix->balises, verbal);

	if(verbal)
	{
		cout <<  "Ma température après l'action ";
		cocix->Temperature.affiche();
		cout << "\n";
	}

	le_temps_s_ecoule(verbal);

	// TODO Verifier s'il faut mettre une fourchette de Température pour arrêter l'Action
	
	Actions::affiche_action(false);
	cout << "...................................................\n";
}

