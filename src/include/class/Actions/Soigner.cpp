#include "Soigner.h"
#include <cstring>
#include <iostream>
#include <iomanip>

#include "../../monde.h"
#include "Cherche_Malade.h"
#include "../Cocix.h"

using namespace std;

Soigner::Soigner(){
	charge();
	Action_alternative = new Cherche_Malade();
}

bool Soigner::valide_Action( const Cocix* cocix , const bool verbal)
{
	// si je n'ai pas dejà partenaire je regarde s'il y en a un sur ma case

	if(cocix->get_id_partenaire() > 0)
	{
		if(verbal) cout << "J'ai déjà un patient ... ";
			// le patient est toujours là ?
			if(existe(cocix->get_case_presence() , cocix->get_id_partenaire(),  verbal) != -1 )
			{
				if(verbal) cout << "toujours là ! ";
				return true;
			}
			else
			{
				if(verbal) cout << " mais qui est parti(e) ";
			}

	} 
	// on regarde s'il existe un partenaire potentiel sur notre case
	int id_malade_potentiel;

	id_malade_potentiel = malade(cocix->get_case_presence(), cocix, verbal);

	if(id_malade_potentiel != 0){
		
		return true;
	}
	else
	{
		return false;
	}

}

void Soigner::charge()
{
	set_id(SOIGNER);
	strcpy(action, "Je soigne");
	strcpy(desire, "Soigner");
	set_chaleur(0.1f);
	set_eau(2.0f);
	set_calorie(1.8f);
	set_duree(3);
	deplacement = false;
	peut_etre_stoppee = false;
}

//   *************************************** A C T I O N ***********************
void Soigner::go(Cocix* cocix,bool verbal)
{
	int id_malade;
	Cocix *Malade;
	float quantite_soins;


	cout <<  "...................................................\n";
	if(verbal) Actions::index();
	cout << "ACTION => Soigner ....\n";

	// verification du partenaire et chargement

	if(verbal) cout << "Verifications du patient ...\n";
	if(cocix->get_id_partenaire() > 0 ){
		Malade = new Cocix(cocix->get_id_partenaire(),false,verbal);
		if(Malade->get_id() == 0 )
		{
			if(verbal) cout << "Mon patient à des problèmes de chargement, je termine l'action !\n";
			cocix->set_id_partenaire(0);
			set_action_terminee(true);
			delete Malade;
			return;	
		}
	}
	else
	{
		// je n'ai pas inscris de partenaire
		id_malade = malade(cocix->get_case_presence(), cocix, verbal);
		if(id_malade > 0)
		{	// j'ai un partenaire disponible
			Malade = new Cocix(id_malade, false, verbal);
			if(Malade->get_id() == 0 )
			{
				if(verbal) cout << "Mon patient à des problèmes de chargement, je termine l'action !\n";
				cocix->set_id_partenaire(0);
				set_action_terminee(true);
				delete Malade;
				return;
			}
		}
		else
		{
			if(verbal) cout << "Pas de patient disponible, je termine l'action !\n";
			cocix->set_id_partenaire(0);
			set_action_terminee(true);
			return;
		}
	}
	
	le_temps_s_ecoule(verbal);
	
	// est-ce terminé ?
	if(terminee())
	{	// oui
		set_action_terminee(true);
		cocix->set_id_partenaire(0);
		if(verbal) cout << "SOINS Terminés !\n";
		quantite_soins = cocix->genome[SOINS].valeur;
		if(verbal) cout << "Quantité de soins appliquée : " << setprecision(3) << quantite_soins << setprecision(2)<<" pdv\n";
	
		Malade->Sante.modif(quantite_soins, &Malade->balises, verbal);

		// baisser ou monter la température si souffrance 
		if(Malade->Temperature.souffrance(&Malade->Sante , &Malade->balises.coma, false, verbal))
		{
			//il y a souffrance 
			if( Malade->Temperature.get_valeur() < 37.5f)
			{
				//on rechauffe si temp < moyenne 
				Malade->Temperature.modif(cocix->genome[TEMP].valeur , &Malade->balises, verbal);
				if(verbal) cout << "\nJe le rechauffe de " << cocix->genome[TEMP].valeur << "°C.\n";
			} else if(Malade->Temperature.get_valeur() > 37.5f)
			{
				// je refroidi
				Malade->Temperature.modif(- cocix->genome[TEMP].valeur , &Malade->balises, verbal);
				if(verbal) cout << "\nJe le refroidi de -" << cocix->genome[TEMP].valeur << "°C.\n";
			} else
			{
				// ???
				cout << "\nIl semble qu'il y ai un soucis avec la température mais je ne sais pas quoi !\n";
			}
		}
		
		Malade->sauvegarde(verbal);
	}
	
	
	
	Actions::affiche_action(false);
	cout << "...................................................\n";
	delete Malade;
}