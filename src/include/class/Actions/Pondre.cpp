#include "Pondre.h"
#include <cstring>
#include <stdio.h>
#include <iostream>
#include "Cherche_Case_Libre.h"
#include "../JourNuit.h"
#include "../../monde.h"

using namespace std;

Pondre::Pondre(){
	charge();
	Action_alternative = new Cherche_Case_Libre();
}

bool Pondre::valide_Action( const Cocix* cocix , const bool verbal)
{
	//verification normalement inutile
	if(cocix->male())
	{
		if(verbal) cout << "Impossible que je désire Pondre, JE SUIS UN MÂLE !!!\n";
		return false;
	}

	if(!cocix->fecondee())
	{
		if(verbal) cout << "Impossible ... je ne suis pas fécondée !!\n";
		return false;
	}

	if(cocix->cycle_sexuel() != 4)
	{
		if(verbal) cout << "Mon oeuf n'est pas encore prêt !\n";
		return false;
	}
	if(libre(cocix->get_case_presence()) )
	{
		if(verbal) cout << "Je suis prête ici !\n";
		return true;
	} else
	{
		if(verbal) cout << "Il n'y a plus de place ici !\n";
		return false;
	}
}


void Pondre::charge()
{
	set_id(9);
	strcpy(action, "Je ponds");
	strcpy(desire, "Pondre");
	set_chaleur(0.1f);
	set_eau(3.0f);
	set_calorie(3.0f);
	set_duree(5);
	deplacement = false;
	peut_etre_stoppee = false;
}

//   *************************************** A C T I O N ***********************
void Pondre::go(Cocix* cocix,bool verbal)
{
	
	cout <<  "...................................................\n";
	if(verbal) Actions::index();
	cout << "ACTION => Pondre ....\n";

	le_temps_s_ecoule();

	if(terminee())
	{
		if(verbal) cout << "Ponte terminée\n";
		int oeuf = cocix->get_id_oeuf();
		short lieu = cocix->get_case_presence();
		JourNuit Jour_Nuit;
		int jour = Jour_Nuit.jours;
		Cocix *Oeuf;
		Oeuf = new Cocix(oeuf,true,verbal);

		// fichiers
		char nomFichier[30] = "" , ancien_fichier[30] = "";
		sprintf(ancien_fichier, "%s%s", REPERTOIRE_NID, Oeuf->get_fichier());
		
		sprintf(nomFichier, "%d.cox", Oeuf->get_id());										
		if(verbal) cout << "Nouveau nom de fichier : " << nomFichier << "\n";
		Oeuf->set_fichier(nomFichier);


		Oeuf->set_case_naissance(lieu);
		Oeuf->set_case_presence(lieu);
		Oeuf->set_date_naissance(jour);
		Oeuf->marque_presence(verbal);

		//sauvegarde
		Oeuf->sauvegarde(verbal);

		// effacer le fichier .oeuf
		if(remove(ancien_fichier) != 0 )
		{
			cout << "Je n'ai pas réussi à enlever l'oeuf du nid !\n";
		}
		else
		{
			if(verbal) cout << ancien_fichier << " Effacé.\n";
		}


		delete Oeuf;


		// on met à jour la mere
		if(verbal) cout << "Mise à jour de la mère.\n";
		cocix->set_id_oeuf(0);
		cocix->balises.fecondee = false;
		set_action_terminee(true);
		cocix->sauvegarde(verbal);
	}
	else
	{
		if(verbal) cout << "Je ponds, tour N° " << get_temps_ecoule() << "\n";
	}
	cout <<  "...................................................\n";
}