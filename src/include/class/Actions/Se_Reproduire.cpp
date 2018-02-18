#include "Se_Reproduire.h"
#include <cstring>
#include <iostream>

#include "../../monde.h"
#include "../../reproduction.h"
#include "Cherche_Partenaire.h"
#include "../Cocix.h"

using namespace std;

Se_Reproduire::Se_Reproduire(){
	charge();
	Action_alternative = new Cherche_Partenaire();
}

bool Se_Reproduire::valide_Action( const Cocix* cocix , const bool verbal)
{
	// si je n'ai pas dejà partenaire je regarde s'il y en a un sur ma case

	if(cocix->get_id_partenaire() > 0)
	{
		if(verbal) cout << "J'ai déjà un partenaire ... ";
			// le partenaire est toujours là ?
			//cout << "case_presence = " << cocix->case_presence << " get_case_presence() = " << cocix->get_case_presence() << "\n";
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
	int id_partenaire_potentiel;

	id_partenaire_potentiel = partenaire(cocix->get_case_presence(), cocix, verbal);

	if(id_partenaire_potentiel != 0){
		
		return true;
	}
	else
	{
		return false;
	}

}

void Se_Reproduire::charge()
{
	set_id(12);
	strcpy(action, "Je me reproduit");
	strcpy(desire, "Se reproduire");
	set_chaleur(0.1f);
	set_eau(3.0f);
	set_calorie(1.8f);
	set_duree(5);
	deplacement = false;
	peut_etre_stoppee = false;
}

//   *************************************** A C T I O N ***********************
void Se_Reproduire::go(Cocix* cocix,bool verbal)
{
	int id_partenaire_potentiel, oeuf;
	Cocix *Partenaire;


	cout <<  "...................................................\n";
	if(verbal) Actions::index();
	cout << "ACTION => Se reproduire ....\n";

	// verification du partenaire et chargement

	if(verbal) cout << "Verifications du partenaire ...\n";
	if(cocix->get_id_partenaire() > 0 ){
		Partenaire = new Cocix(cocix->get_id_partenaire(),false,verbal);
		if(Partenaire->get_id() > 0 )
		{
			// on verifie qu'il est bien avec moi
			if(Partenaire->get_id_partenaire() == cocix->get_id())
			{
				//oui
				if(verbal) cout << "Tout est ok\n";
			}
			else
			{
				// il est avec qu'un d'autre
				if(verbal) cout << "Mon partenaire me trompe avec quelqu'un ! je termine l'action !\n";
				cocix->set_id_partenaire(0);
				set_action_terminee(true);
				delete Partenaire;
				return;
			}
		}
		else
		{
			if(verbal) cout << "Mon partenaire à des problèmes de chargement, je termine l'action !\n";
			cocix->set_id_partenaire(0);
			set_action_terminee(true);
			delete Partenaire;
			return;	
		}
	}
	else
	{
		// je n'ai pas inscris de partenaire
		id_partenaire_potentiel = partenaire(cocix->get_case_presence(), cocix, verbal);
		if(id_partenaire_potentiel > 0)
		{	// j'ai un partenaire disponible
			Partenaire = new Cocix(id_partenaire_potentiel, false, verbal);
			if(Partenaire->get_id() > 0 )
			{ 
				// verifie que le partenaire soit pas déjà avec quelqu'un
				if(Partenaire->get_id_partenaire() == 0)
				{
					//il est dispo
					cocix->set_id_partenaire(Partenaire->get_id());	// je l'inscris chez moi
					Partenaire->set_id_partenaire(cocix->get_id());	// je m'inscrisS chez lui
					if(verbal) cout << "Présentations faites !\n";
				}
				else
				{
					// il a dejà un partenaire ?
					if(Partenaire->get_id_partenaire() == cocix->get_id())
					{
						// c'est moi !
						cocix->set_id_partenaire(Partenaire->get_id());	// je l'inscris chez moi
						if(verbal) cout << "Présentations faites !\n";
					}
					else
					{
						// c'est quelqu'un d'autre
						if(verbal) cout << "Mon partenaire est déjà avec quelqu'un ! je termine l'action !\n";
						cocix->set_id_partenaire(0);
						set_action_terminee(true);
						delete Partenaire;
						return;
					}
				}
			}
			else
			{
				if(verbal) cout << "Mon partenaire à des problèmes de chargement, je termine l'action !\n";
				cocix->set_id_partenaire(0);
				set_action_terminee(true);
				delete Partenaire;
				return;
			}
		}
		else
		{
			if(verbal) cout << "Pas de partenaire disponible, je termine l'action !\n";
			cocix->set_id_partenaire(0);
			set_action_terminee(true);
			return;
		}
	}
	
	// verification des infos Actions du partenaire

	if(Partenaire->Action->equal(Se_Reproduire()))
	{
		// ok il est déjà au courant qu'on se reproduit !

	}
	else
	{
		Partenaire->Action = new Se_Reproduire();
	}

	// c'est le male qui incrémente le temps de l'action
	if(cocix->male())
	{
		le_temps_s_ecoule(verbal);
		Partenaire->Action->le_temps_s_ecoule(verbal);
	}

	// est-ce terminé ?
	if((cocix->male() && terminee()) || (Partenaire->male() && Partenaire->Action->terminee()))
	{	// oui
		set_action_terminee(true);
		if(verbal) cout << "REPRODUCTION Terminée !\n";
		// on va créer un nouvel oeuf
		if(cocix->male()){
			// male
			//Il faut féconder le partenaire femelle
			Partenaire->balises.fecondee = true;
			oeuf = procreation (cocix, Partenaire, verbal);
			Partenaire->set_id_oeuf(oeuf);
		}
		else
		{
			// femelle
			cocix->balises.fecondee = true;
			oeuf = procreation(Partenaire , cocix, verbal);
			cocix->set_id_oeuf(oeuf);
		}
		if(oeuf > 0 )
		{
			if(verbal) cout << "Un Oeuf vient d'être crée => N°" << oeuf << "\n";
		}
		else
		{
			cout << "Une erreur apparait car l'oeuf n'a pas été retrouvé !\n";
		}
		// on efface les partenaires
		cocix->set_id_partenaire(0);
		Partenaire->set_id_partenaire(0);
		Partenaire->Action->set_action_terminee(true);
	}
	
	Partenaire->sauvegarde(verbal);
	
	Actions::affiche_action(false);
	cout << "...................................................\n";
}