#include "Recolter.h"
#include <cstring>
#include <iostream>

#include "../../monde.h"
#include "../Cocix.h"
#include "Cherche_Recolte.h"

using namespace std;

Recolter::Recolter(){
	charge();
	Action_alternative = new Cherche_Recolte();
}

bool Recolter::valide_Action(const Cocix* cocix , const bool verbal)
{
	if(verbal) cout << "suis-je rentré(e) ? ";

	if(cocix->rentree())
	{
		if(verbal) cout << "Oui => je ne peux pas récolter chez moi !\n";

		return false;
	}
	else
	{
		if(verbal) cout << "Non.\t";
	}

	if(verbal) cout << " Ai-je de la place en moi ?... ";

	if(cocix->pleine())
	{
		if(verbal) cout << "Non => ";

		return false;
	}
	else
	{
		if(verbal) cout << "Oui.\tY-a-t-il de la nourriture sur ma case ? ";

		if(nourriture(cocix->get_case_presence()) > 0)
		{
			if(verbal) cout << "Oui => ";
			return true;
		}
		else
		{
			if(verbal) cout << "Non => ";
			return false;
		}
	}
}

void Recolter::charge()
{
	set_id(15);
	strcpy(action, "je récolte");
	strcpy(desire, "Recolter");
	set_chaleur(0.05f);
	set_eau(1.0f);
	set_calorie(1.0f);
	set_duree(3);
	deplacement = false;
	peut_etre_stoppee = false;

}

//   *************************************** A C T I O N ***********************
void Recolter::go(Cocix* cocix,bool verbal)
{
	float quantite_prise;
	float case_recolte = cocix->get_case_presence();
	struct struct_xy xy;

	xy  = case_to_xy(case_recolte);

	cout <<  "...................................................\n";
	if(verbal) Actions::index();
	cout << "ACTION => Récolter ....\n";
	
	// On met à jour la base de donnée du monde
	if(verbal) cout << "En case N° " << case_recolte << " (" << xy.x << "," << xy.y << ") Il y a " << nourriture(case_recolte) << " cal avant.\n";
	quantite_prise = prend_element(case_recolte, cocix->genome[Gene::ASSIMILATION_CALORIQUE].valeur / 2 ,NOURRITURE);
	cocix->set_recolte(cocix->get_recolte() + quantite_prise);

	//On incrémente le temps de l'action
	le_temps_s_ecoule(verbal);
	
	if(verbal) cout << "je porte maintenant " << cocix->get_recolte() << " cal sur moi. ";
	if(cocix->pleine())
	{
		if(verbal) cout << "Je suis plein(e) !\n";
		set_action_terminee(true);
	}
	else
	{
		if(verbal) cout << "\n";
		if( !valide_Action(cocix , verbal))
		{
			if(verbal) cout << "Non !\n";
			set_action_terminee(true);
		}
	}

	cout << "\n";
	Actions::affiche_action(false);
	cout << "...................................................\n";
}