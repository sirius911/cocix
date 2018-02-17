#include "Deposer.h"
#include <cstring>
#include <iostream>
#include <iomanip>

#include "Rentrer.h"
#include "../../monde.h"

using namespace std;

Deposer::Deposer(){
	charge();
	Action_alternative = new Rentrer();
}

bool Deposer::valide_Action(const Cocix* cocix , const bool verbal)
{
	if(verbal) cout << "suis-je rentré(e) ? ";

	return (cocix->rentree());
}

void Deposer::charge()
{
	set_id (16);
	strcpy(action, "Je Dépose");
	strcpy(desire, "Déposer");
	set_chaleur(0.02f);
	set_eau(1.0f);
	set_calorie(1.0f);
	set_duree(3);
	deplacement = false;
	peut_etre_stoppee = false;
}


//   *************************************** A C T I O N ***********************
void Deposer::go(Cocix* cocix,bool verbal)
{
	float quantiteDeposee;

	cout <<  "...................................................\n";
	if(verbal) Actions::index();
	cout << "ACTION => Déposer ....\n";

	le_temps_s_ecoule(verbal);

	// on dépose en fractionnant de la durée de l'Action 3 mn

	if(get_temps_ecoule() < get_duree())
	{
		if(verbal) cout << "Tour N° " << get_temps_ecoule();
		// tour 1  : 1/3 = 1/(duree - tour)
		// tour 2  : 1/2 de ce qui reste 1/(duree - tour)
		
		quantiteDeposee = (float)cocix->get_recolte() * (float)( 1.0f / (  (float) get_duree() - (float) get_temps_ecoule() + 1.0f));
		set_action_terminee(false);

	} else {
		// tour 3 = le reste
		quantiteDeposee = cocix->get_recolte();
		if(verbal) cout << " Terminé!\n";
		set_action_terminee(true);
	}

	if(verbal) cout << ", je dépose "<< quantiteDeposee << " Cal sur la case " << cocix->get_case_presence() << ".\n";
	ajoute_element(cocix->get_case_presence() , (float) quantiteDeposee, NOURRITURE);
	cocix->set_recolte(cocix->get_recolte() - quantiteDeposee);
	if(verbal)
	{
		if(cocix->get_recolte() > 0 )
			cout << "Il me reste "<< cocix->get_recolte() << " Cal.\n";
		else
			cout << "Je suis vide !\n";
	}
	
	cout << "\n";
	Actions::affiche_action(false);	
	cout <<  "...................................................\n";
}