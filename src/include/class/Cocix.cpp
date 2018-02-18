#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
#include <vector>
#include "Gene.h"
#include "Cocix.h"
#include "JourNuit.h"
#include "Param_Etat.h"
#include "../monde.h"
#include "../reproduction.h"
#include <iomanip>

#include "Actions/Actions.h"
//#include "Actions/Agresser.h"
#include "Actions/Boire.h"
#include "Actions/Cherche_Eau.h"
#include "Actions/Deposer.h"
#include "Actions/Dormir.h"
#include "Actions/Manger.h"
#include "Actions/Pondre.h"
#include "Actions/Recolter.h"
#include "Actions/Cherche_Recolte.h"
#include "Actions/Rentrer.h"
#include "Actions/Se_Reproduire.h"
#include "Actions/Se_Soigner.h"
#include "Actions/Cherche_Partenaire.h"
#include "Actions/Cherche_Case_Libre.h"
#include "Actions/Soigner.h"
#include "Actions/Cherche_Malade.h"

using namespace std;

Cocix::Cocix(){}


Cocix::Cocix(const int x_id, const bool oeuf, const bool verbal){
	//constructeur 
	id = x_id;

	// construction du  nom du fichier
	if(oeuf)
		sprintf(fichier, "%d.oeuf", id);
	else
		sprintf(fichier, "%d.cox", id);

	// chargement
	if(verbal) cout << "chargement du CoCiX N° " << id << " ...";
	if(chargement(verbal))
	{
		prend_temperature();
		if(verbal) cout << " Terminé\n";
	}
	else 
	{
		if(verbal) cout << " Interrompu.\n";
		id = 0;
	}
	
}
Cocix::Cocix(const char x_fichier[30],bool verbal)
{
	// initialise le nomFichier
	// XXXF
	if(verbal) cout << "fichier = " << x_fichier << "\n";
	set_fichier(x_fichier);
	//strcpy(fichier,x_fichier);
	
	
	if(chargement(verbal))
	{
		prend_temperature();
		if(verbal) cout << " Terminé\n";
	}
	else
	{
		if(verbal) cout << " Interrompu.\n";
		id = 0;
	}
}

Cocix::~Cocix(){
	
}

/* Création de Cocix exemple pour le debugage ******************************************************************
			A EFFACER ensuite
			*/
void Cocix::creation_Toto(int x_id, const bool verbal){

	cout << "\n Création de Toto ...";
	// Paramètre d'identité
	id = x_id;
	strcpy(nom, "Toto");
	strcpy(fichier,"1.cox");
	idPere = 0;
	idMere = 0;
	date_naissance = 31;
	date_mort = 0;
	sexe = MALE;
	case_presence = 9694;
	case_naissance = 3030;
	vieux = 20;
	vivacite = 50;
	recolte = 0;
	id_partenaire = 2;
	id_oeuf = 0;
	// creation de son genome
	//Gene genome[MAX_GEN];
	nb_genes = 23;
	genome.insert(genome.end(),Gene("Assimilation Calorique",ASSIMILATION_CALORIQUE,8.0f,3.0f,2.0f,8.0f,4.0f,4.0f,2.0f,m6,false));
	genome.insert(genome.end(),Gene("Assimilation Hydrique",ASSIMILATION_HYDRIQUE,10.f,10.0f,2.0f,3.0f,3.0f,2.0f,2.0f,m6,false));
	genome.insert(genome.end(),Gene("Calorie",CALORIE,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,PM,false));
	genome.insert(genome.end(),Gene("Faim",FAIM,0.5f,0.65f,0.5f,0.65f,0.65f,0.65f,0.65f,m6,true));
	genome.insert(genome.end(),Gene("Froid",FROID,0.65f,0.65f,0.65f,0.65f,0.65f,0.65f,0.65f,H,true));
	genome.insert(genome.end(),Gene("Hydro",HYDRO,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,GP,false));
	genome.insert(genome.end(),Gene("Sante",SANTE,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,H,false));
	genome.insert(genome.end(),Gene("Satiété",SATIETE,0.58f,0.58f,0.60f,0.65f,0.65f,0.65f,0.65f,m6,true));
	genome.insert(genome.end(),Gene("Soif",SOIF,0.50f,0.60f,0.50f,0.50f,0.50f,0.50f,0.50f,GP,true));
	genome.insert(genome.end(),Gene("Temp",TEMP,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,PM,true));
	genome.insert(genome.end(),Gene("Vieux",VIEUX,20.0f,20.0f,20.0f,20.0f,20.0f,20.0f,20.0f,PM,false));
	genome.insert(genome.end(),Gene("Souffre_Faim",SOUFFRE_FAIM,0.50f,0.30f,0.5f,0.3f,0.3f,0.3f,0.3f,m6,true));
	genome.insert(genome.end(),Gene("Souffre_Soif",SOUFFRE_SOIF,0.5f,0.8f,0.4f,0.5f,0.8f,0.4f,0.3f,m6,true));
	genome.insert(genome.end(),Gene("Recup_Sommeil",RECUP_SOMMEIL,0.0005f,0.0004f,0.0005f,0.0004f,0.0003f,0.0005f,0.0005f,M,true));
	genome.insert(genome.end(),Gene("Récolte",RECOLTE,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,F,false));
	genome.insert(genome.end(),Gene("Agressivité",AGRESSIVITE,0.3333f,0.3333f,0.3333f,0.3333f,0.3333f,0.3333f,0.3333f,H,true));
	genome.insert(genome.end(),Gene("Vivacité",VIVACITE,0.3f,0.3f,0.3f,0.3f,0.3f,0.3f,0.3f,GM,true));
	genome.insert(genome.end(),Gene("Soins",SOINS,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,GM,false));
	genome.insert(genome.end(),Gene("Seuil_Malade",SEUIL_MALADE,0.45f,0.45f,0.45f,0.45f,0.45f,0.45f,0.45f,m6,true));
	genome.insert(genome.end(),Gene("Seuil_Comas",SEUIL_COMA,0.10f,0.10f,0.15f,0.10f,0.10f,0.10f,0.10f,m6,true));
	genome.insert(genome.end(),Gene("Vieillissement",VIEILLISSEMENT,0.007f,0.007f,0.007f,0.007f,0.007f,0.007f,0.007f,M,true));
	genome.insert(genome.end(),Gene("Seuil_accel_vieille",SEUIL_ACCEL_VIEILLE,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,pm,false));
	genome.insert(genome.end(),Gene("Compassion",COMPASSION,0.30f,0.30f,0.30f,0.20f,0.20f,0.20f,0.20f,pm,true));
	
	//Param_Etat(nom,unite,capacite, valeur, limite_basse_malade,limite_haute_malade,  limite_basse_coma,limite_haute_coma,
	//			limite_basse_souffrance, limite_haute_souffrance, correction)
	
	Sante = Param_Etat("Santé","Pdv",100.0f,100.0f,
		genome[SEUIL_MALADE].valeur*genome[SANTE].valeur, (float)NULL,
		genome[SEUIL_COMA].valeur*genome[SANTE].valeur, (float)NULL,
		genome[SEUIL_MALADE].valeur*genome[SANTE].valeur,(float)NULL,
		(float) SOUFFRANCE_MALADIE, 0.0f,100.0f);

	Calorie = Param_Etat("Calorie","Cal",120.0,80.3578f,
		(float)NULL,(float) NULL,	
		genome[CALORIE].valeur * (float) COMA_CALORIE,	(float)NULL,
		genome[SOUFFRE_FAIM].valeur * genome[CALORIE].valeur,(float)NULL,
		(float) SOUFFRANCE_CALORIQUE, 0.0f, 120.0f);

	Hydro = Param_Etat("Hydro","muL",100.0f,60.222f,
		(float)NULL,(float) NULL,	
		genome[HYDRO].valeur * (float)COMA_HYDRO, (float)NULL,	
		genome[SOUFFRE_SOIF].valeur * genome[HYDRO].valeur, (float)NULL,		
		(float) SOUFFRANCE_HYDRIQUE, 0.0f, 100.0f);
	Temperature = Param_Etat("Temp.","°C", (float)NULL ,37.0f,
		(float)NULL, 40.0f,
		35.8f,42.0f,
		36.0f,40.0f,
		(float) SOUFFRANCE_THERMIQUE, 35.5f, 42.5f);	
		
	// balises etat
	balises.fecondee = false;
	balises.vivant = true;
	balises.mort = false;
	balises.malade = false;
	balises.coma = false;
	balises.agressive = true;
	balises.froid = false;
	balises.faim = false;
	balises.soif = false;

	Desire =  new Se_Reproduire();
	Action =  new Se_Reproduire();
	Action->set_temps_ecoule(3);
	int i = 0 ;
	do 
	{
		ancetres[i] = 0;
	} while( ++i < 30);
	
	sauvegarde(verbal);
	cout << " Terminée !\n";
	temp_exterieur = temperature(case_presence);
	//affiche(true);
}

void Cocix::creation_Titi(int x_id, bool verbal){

	cout << "\n Création de Titi ...";
	// Paramètre d'identité
	id = x_id;
	strcpy(nom, "Titi");
	strcpy(fichier,"2.cox");
	idPere = 0;
	idMere = 0;
	date_naissance = 35;
	date_mort = 0;
	sexe = FEMELLE;
	case_presence = 9694;
	case_naissance = 1010;
	vieux = 25;
	vivacite = 65;
	recolte = 100;
	id_partenaire = 1;
	id_oeuf = 0;
	// creation de son genome
	
	//Gene genome[MAX_GEN];
	nb_genes = 23;
	genome.insert(genome.end(),Gene("Assimilation Calorique",ASSIMILATION_CALORIQUE,8.0f,3.0f,2.0f,8.0f,4.0f,4.0f,2.0f,m6,false));
	genome.insert(genome.end(),Gene("Assimilation Hydrique",ASSIMILATION_HYDRIQUE,10.f,10.0f,2.0f,3.0f,3.0f,2.0f,2.0f,m6,false));
	genome.insert(genome.end(),Gene("Calorie",CALORIE,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,PM,false));
	genome.insert(genome.end(),Gene("Faim",FAIM,0.5f,0.65f,0.5f,0.65f,0.65f,0.65f,0.65f,m6,true));
	genome.insert(genome.end(),Gene("Froid",FROID,0.65f,0.65f,0.65f,0.65f,0.65f,0.65f,0.65f,H,true));
	genome.insert(genome.end(),Gene("Hydro",HYDRO,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,GP,false));
	genome.insert(genome.end(),Gene("Sante",SANTE,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,H,false));
	genome.insert(genome.end(),Gene("Satiété",SATIETE,0.58f,0.58f,0.60f,0.65f,0.65f,0.65f,0.65f,m6,true));
	genome.insert(genome.end(),Gene("Soif",SOIF,0.50f,0.60f,0.50f,0.50f,0.50f,0.50f,0.50f,GP,true));
	genome.insert(genome.end(),Gene("Temp",TEMP,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,PM,true));
	genome.insert(genome.end(),Gene("Vieux",VIEUX,20.0f,20.0f,20.0f,20.0f,20.0f,20.0f,20.0f,PM,false));
	genome.insert(genome.end(),Gene("Souffre_Faim",SOUFFRE_FAIM,0.50f,0.30f,0.5f,0.3f,0.3f,0.3f,0.3f,m6,true));
	genome.insert(genome.end(),Gene("Souffre_Soif",SOUFFRE_SOIF,0.5f,0.8f,0.4f,0.5f,0.8f,0.4f,0.3f,m6,true));
	genome.insert(genome.end(),Gene("Recup_Sommeil",RECUP_SOMMEIL,0.0005f,0.0004f,0.0005f,0.0004f,0.0003f,0.0005f,0.0005f,M,true));
	genome.insert(genome.end(),Gene("Récolte",RECOLTE,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,100.0f,F,false));
	genome.insert(genome.end(),Gene("Agressivité",AGRESSIVITE,0.3333f,0.3333f,0.3333f,0.3333f,0.3333f,0.3333f,0.3333f,H,true));
	genome.insert(genome.end(),Gene("Vivacité",VIVACITE,0.3f,0.3f,0.3f,0.3f,0.3f,0.3f,0.3f,GM,true));
	genome.insert(genome.end(),Gene("Soins",SOINS,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,GM,false));
	genome.insert(genome.end(),Gene("Seuil_Malade",SEUIL_MALADE,0.45f,0.45f,0.45f,0.45f,0.45f,0.45f,0.45f,m6,true));
	genome.insert(genome.end(),Gene("Seuil_Comas",SEUIL_COMA,0.10f,0.10f,0.15f,0.10f,0.10f,0.10f,0.10f,m6,true));
	genome.insert(genome.end(),Gene("Vieillissement",VIEILLISSEMENT,0.007f,0.007f,0.007f,0.007f,0.007f,0.007f,0.007f,M,true));
	genome.insert(genome.end(),Gene("Seuil_accel_vieille",SEUIL_ACCEL_VIEILLE,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,pm,false));
	genome.insert(genome.end(),Gene("Compassion",COMPASSION,0.50f,0.50f,0.50f,0.50f,0.50f,0.50f,0.50f,pm,true));

	//Param_Etat(nom,unite,capacite, valeur, limite_basse_malade,limite_haute_malade,  limite_basse_coma,limite_haute_coma,
	//			limite_basse_souffrance, limite_haute_souffrance, correction, plancher, plafond)


	Sante = Param_Etat("Param Santé","Pdv",100.0f,80.0f,
		genome[SEUIL_MALADE].valeur*genome[SANTE].valeur, (float)NULL,
		genome[SEUIL_COMA].valeur*genome[SANTE].valeur, (float)NULL,
		genome[SEUIL_MALADE].valeur*genome[SANTE].valeur,(float)NULL,
		(float) SOUFFRANCE_MALADIE,0.0f,100.0f);	// plafond est Capacite

	Calorie = Param_Etat("Calories","Cal",120.0,80.3578f,
		(float)NULL,(float) NULL,	
		genome[CALORIE].valeur * (float) COMA_CALORIE,	(float)NULL,
		genome[SOUFFRE_FAIM].valeur * genome[CALORIE].valeur,(float)NULL,
		(float) SOUFFRANCE_CALORIQUE,0.0f,120.0f);

	Hydro = Param_Etat("Param Hydro","muL",100.0f,60.222f,
		(float)NULL,(float) NULL,	
		genome[HYDRO].valeur * (float)COMA_HYDRO, (float)NULL,	
		genome[SOUFFRE_SOIF].valeur * genome[HYDRO].valeur, (float)NULL,		
		(float) SOUFFRANCE_HYDRIQUE,0.0f,100.0f);
	Temperature = Param_Etat("Température","°C", (float)NULL ,37.0f,
		(float)NULL, 40.0f,
		35.8f,42.0f,
		36.0f,40.0f,
		(float) SOUFFRANCE_THERMIQUE, 35.5f, 43.5f);	
	// balises etat
	balises.fecondee = false;
	balises.vivant = true;
	balises.mort = false;
	balises.malade = false;
	balises.coma = false;
	balises.agressive = false;
	balises.froid = false;
	balises.faim = false;
	balises.soif = false;
	Desire =  new Se_Reproduire();
	Action =  new Se_Reproduire();
	Action->set_temps_ecoule(3);
	int i = 0 ;
	do 
	{
		ancetres[i] = 0;
	} while( ++i < 30);

	
	sauvegarde(verbal);
	cout << " Terminée !\n";
	temp_exterieur = temperature(case_presence);
	
}


//******************************************************************************************************************
//                                 G E T T E R S
//*******************************************************************************************************************

int Cocix::get_id() const
{
	return id;
}

short Cocix::get_recolte()
{
	return recolte;
}

int Cocix::get_id_partenaire() const
{
	return id_partenaire;
}

int Cocix::get_id_oeuf() const
{
	return id_oeuf;
}

short Cocix::get_case_presence() const
{
	return case_presence;
}

short Cocix::get_case_naissance() const
{
	return case_naissance;
}

int Cocix::get_nb_genes() const
{
	return nb_genes;
}

int Cocix::get_idPere() const
{
	return idPere;
}

int Cocix::get_idMere() const
{
	return idMere;
}

short Cocix::get_date_naissance() const
{
	return date_naissance;
}

short Cocix::get_date_mort() const
{
	return date_mort;
}

char* Cocix::get_fichier()
{
	return fichier;
}

int Cocix::get_ancetre(const short numero ) const
{
	if(numero >=0 && numero < 30 )
		return ancetres[numero];
	else
		cout << "ERREUR de numéro d'ancetre : " << numero << "\n";
	return 0;
}

//******************************************************************************************************************
//                                 S E T T E R S
//*******************************************************************************************************************

void Cocix::set_id(int x_id)
{
	id = x_id;
}

void Cocix::set_case_presence(short x_case_presence)
{
	case_presence = x_case_presence;
}

void Cocix::marque_presence(const bool verbal)
{
	marque_trace(case_presence,id,verbal);
}

void Cocix::deplace(const short arrivee, const bool verbal)
{
	if(bouge(id, case_presence,valide_case(arrivee),verbal),verbal)
	{
		set_case_presence(arrivee);
		sauvegarde();
	}
	else
	{
		cout << "Problème de déplacement... je ne sauvegarde par " << nom << "\n";
	}
}

void Cocix::set_recolte(short x_recolte)
{
	recolte = x_recolte;
}

void Cocix::set_id_partenaire(int x_id)
{
	id_partenaire = x_id;
}

void Cocix::set_id_oeuf( int x_id)
{
	id_oeuf = x_id;
}

void Cocix::set_sexe(bool x_sexe)
{
	sexe = x_sexe;
}

void Cocix::set_fichier(const char *x_fichier)
{
	strcpy(fichier, x_fichier);
}

void Cocix::set_idPere(int x_idPere)
{
	idPere = x_idPere;
}

void Cocix::set_idMere(int x_idMere)
{
	idMere = x_idMere;
}

void Cocix::set_nom(char *x_nom)
{
	strcpy(nom, x_nom);
}

void Cocix::set_date_naissance( short x_date)
{
	date_naissance = x_date;
}

void Cocix::set_date_mort( short x_date)
{
	date_mort = x_date;
}

void Cocix::set_case_naissance( short x_case)
{
	case_naissance = x_case;
}

void Cocix::set_vieux(short x_vieux)
{
	vieux = x_vieux;
}

void Cocix::set_vivacite(short x_vivacite)
{
	vivacite = x_vivacite;
}

void Cocix::set_nb_genes( int x_nb_genes)
{
	nb_genes = x_nb_genes;
}

void Cocix::set_ancetre(short numero, int x_ancetre)
{
	if(numero >=0 && numero < 30 )
		ancetres[numero] = x_ancetre;
	else
		cout << "ERREUR de numero d'ancetre : " << numero << "\n";
}
//******************************************************************************************************************
//                                V I V R E
//*******************************************************************************************************************



int Cocix::vie(bool verbal){
	//fait vivre la CoCiX
	if(cortex_Etat(verbal)){
		
		//sauvegarde();		//Enlevé pour Debug
		return (cortex_Action(verbal) );
		
	}
	return -1;
}
/*****************************************************************************************************************/
	/*
	 _____   _____   _____    _____   _____  __    __       _____   _____       ___   _____  
	/  ___| /  _  \ |  _  \  |_   _| | ____| \ \  / /      | ____| |_   _|     /   | |_   _| 
	| |     | | | | | |_| |    | |   | |__    \ \/ /       | |__     | |      / /| |   | |   
	| |     | | | | |  _  /    | |   |  __|    }  {        |  __|    | |     / / | |   | |   
	| |___  | |_| | | | \ \    | |   | |___   / /\ \       | |___    | |    / /  | |   | |   
	\_____| \_____/ |_|  \_\   |_|   |_____| /_/  \_\      |_____|   |_|   /_/   |_|   |_| */  

bool Cocix::cortex_Etat(bool verbal){
	float correction,depense_eau,depense_calorie;
	JourNuit Jour_Nuit;
	
	cout << "\n****     C O R T E X   E T A T     ****\n";

	raz_balises(verbal);
	
	temp_exterieur = temperature(case_presence);

		/*
		¯|¯ |¯ |\/| |¯| |¯ |¯| /¯\ ¯|¯ | | |¯| |¯ 
 		 |  |¯ |  | |¯  |¯ |¯\ |¯|  |  |_| |¯\ |¯ 
      	 	 ¯           ¯                      ¯ 
		
				Echange avec l'extérieur
		*/
	
		
		if(verbal) cout << "Température ("<< temp_exterieur << " °C): \n";
		else cout << "temp...";
	// vérifie l'étape de la Fourmiz
		if(etape() == ETAT_OEUF ) {
			// Pas de Cortex d'état
			if(verbal) cout << "Je suis un oeuf ! (TODO)</br>";
			// verifier la température
			if(temp_exterieur < 10.0f)
			{
				if(verbal) cout << " Temp ext < 10°C\n";
				Temperature.modif(-genome[TEMP].valeur, &balises,verbal); // on diminue la température de Genes.temp.valeur
			} else if(temp_exterieur > 35.0f)
			{
				if(verbal) cout << "Temp ext > 35°C";
				Temperature.modif(+genome[TEMP].valeur, &balises, verbal);	// on augmente la température 
			}
			return (balises.vivant);
		}
		
		if(etape() == ETAT_BEBE) {
			
			// cortex d'etat des Bébés
			if(verbal) cout << "Je suis un bébé ! </br>";
			// TO DO
		}


		if(temp_exterieur > Temperature.get_valeur() ){
			// si la température exterieur ext supérieur au augmente la température interne de Genes['temp']->valeur
			if(verbal) cout << " Temp ext > Temp corporel => \n"; 
			Temperature.modif(genome[TEMP].valeur, &balises,verbal);
		} else {
			// sinon rien ne change
			if(verbal) cout << " Temp ext <= temp corporel -> aucune modif\n";
		}


		// verification de la température extérieur < à 10°C
		if(temp_exterieur < 10.0f) {
			
			if(verbal) cout << " Temp ext < 10°C<\n";
			Temperature.modif(-genome[TEMP].valeur, &balises,verbal); // on diminue la température de Genes.temp.valeur
			
		}


		//variation de température en fonction de l'action
		// la température ne descend pas en dessous de 36.5 quand elle Mange Dort ou BOIT

		// si je dort ou si je mange ou si bois et que ma température est inf à 36.5°C mon action ne bouge pas ma température
		if(Action->get_chaleur() <= 0 && Temperature.get_valeur() < 36.5f)
		{
			if(verbal)
			{
				cout << Action->get_action() << " ne me fait pas perdre de température car ma température < 36,5°C\n";
			}
		}
		else
		{
			Temperature.modif(Action->get_chaleur(), &balises,verbal);
			if(verbal) cout << Action->get_action() << " -> +" << Action->get_chaleur() << "°C = " << Temperature.get_valeur() << "°C\n";

		}

		
		// Calcul du facteur de correction de température
		correction = (Temperature.get_valeur() - 37.5f) * (Temperature.get_valeur() - 37.5f) * sqrt(Temperature.get_valeur());

		if(verbal) cout << "Facteur de correction  de Temperature = " << correction << "%\n";
	cout << "ok\n";
	cout << "Hydro...";
		/*
						|¯\ |¯ |¯| |¯ |\| |¯  |¯ |¯    | | \| |¯\ |¯| | |¯|  | | |¯ 
						|_/ |¯ |¯  |¯ | |  ¯| |¯  ¯|   |¯|  | |_/ |¯\ | |_|¬ |_| |¯ 
     						¯      ¯      ¯   ¯  ¯                               ¯ 
		*/
		// depense en eau en fonction de l'action:
		depense_eau = Action->get_eau() + (Action->get_eau() * correction / 100);
		if(fecondee()) 
		{
			depense_eau += ( depense_eau * 0.1f ); //si fécondée 10% en plus
			if(verbal) cout << "fécondée : + 10% ";
		}
		Hydro.modif(-depense_eau, &balises,verbal);
		if(verbal) cout << Action->get_action() << " -> -" << depense_eau << " muL = " << Hydro.get_valeur() << " muL\n";
	
	cout << "ok\n";
	cout << "Cal...";
		/*
						|¯\ |¯ |¯| |¯ |\| |¯  |¯ |¯    |¯ /¯\ |  |¯| |¯| | |¯|  | | |¯ 
						|_/ |¯ |¯  |¯ | |  ¯| |¯  ¯|   |_ |¯| |_ |_| |¯\ | |_|¬ |_| |¯ 
     						¯      ¯      ¯   ¯  ¯                                  ¯ 
		*/
		// depense en Calorie en fonction de l'action:
		depense_calorie = Action->get_calorie();
		if(fecondee())
		{
			depense_calorie += (depense_calorie * 0.1f);	// si fécondée 10% en plus
			if(verbal) cout << "fécondée : + 10% ";
		} 
		Calorie.modif(-depense_calorie, &balises);
		if(verbal) cout << Action->get_action() << " -> -" << depense_calorie <<" Cal = " << Hydro.get_valeur() << "Cal\n";

	cout << "ok\n";
	cout << "SA...";
		/*
		\ | /¯\ |¯| | /¯\ ¯|¯ | |¯| |\|   |¯\ |¯   |¯  /¯\ |\| ¯|¯ |¯ 
 		 \| |¯| |¯\ | |¯|  |  | |_| | |   |_/ |¯    ¯| |¯| | |  |  |¯ 
                                              ¯    ¯               ¯ 
		*/
		// Vieux ?	
		if(etape() == ETAT_VIEUX) {
			vieillissement(verbal);
		}

		// Souffrances des Etats
	cout << "ok\n";
	cout << "Souffrances :\nHydro...";	
		Hydro.souffrance(&Sante,  balises.coma, true, verbal);
	cout << "\nCal...";
		Calorie.souffrance(&Sante,  balises.coma, true, verbal);
	cout << "\nTemp...";
		Temperature.souffrance(&Sante,  balises.coma, true, verbal);
	cout << "\nSant...";
		Sante.souffrance(&Sante,  balises.coma, true, verbal);
	cout << "\n";

		// GESTION DU SOMMEIL
		if(Action->equal(Dormir())) {
			// La CoCix Dort
			cout << "Sommeil...";
			Sante.modif(Sante.get_valeur() * genome[RECUP_SOMMEIL].valeur, &balises,verbal);	
			if(verbal) cout << "Action = DORMIR ==> Santé + " << setprecision(3) << ( Sante.get_valeur() * genome[RECUP_SOMMEIL].valeur )<< setprecision(2) <<  "% = " << Sante.get_valeur() << "\n";
			cout << "ok\n";
		}

/*
                                +-+-+-+-+-+-+-+
								|B|A|L|I|S|E|S|
								+-+-+-+-+-+-+-+
*/
        maj_balises(verbal);

        //MORT
        if(Sante.get_valeur() < 1 || Sante.get_capacite() < 1){
        	if(verbal)cout << "\n\t JE MEURT !! =============> TODO \n";
        	// meurt();	 TODO
        	return false;
        }
/*
					 ####  #    #  ####  # #    #    #####  ######  ####  # #####  ######  ####  
					#    # #    # #    # #  #  #     #    # #      #      # #    # #      #      
					#      ###### #    # #   ##      #    # #####   ####  # #    # #####   ####  
					#      #    # #    # #   ##      #    # #           # # #####  #           # 
					#    # #    # #    # #  #  #     #    # #      #    # # #   #  #      #    # 
 					####  #    #  ####  # #    #    #####  ######  ####  # #    # ######  ####  
*/
         cout << "Désire...";
        if (Jour_Nuit.jour_nuit == JOUR)
        {
        //JOUR
        cout << "Jour...";
        	// Besoins vitaux
        	if(coma())
        	{
        		Desire = new Dormir();
        		Action = new Dormir();
        	} 
        	else if(malade())
        		Desire = new Se_Soigner();
        	else if(fecondee() && cycle_sexuel() == 4 && get_id_oeuf() !=0)
        		Desire = new Pondre();
        	else if(soif())
        		Desire = new Boire();
        	else if(faim())
        		Desire = new Manger();
        	else if(froid())
        	{
        		// si le CoCiX a froid elle désire rentrer car chez elle elle n'a plus froid
        		Desire = new Rentrer();
        	}
        	else
        	{
        	// besoins non-vitaux
        		if(etape() > ETAT_BEBE){
        			if(male())
        			{
        			//MALE
        				if(cycle_sexuel() == 0)
        				{	//mature
        					// on regarde l'agressivité
        					if(agressive())
        						cout << "Agresser  ...non implémenté...";
        						//Desire = new Agresser();
        					else if(compassion())
       							Desire = new Soigner();
        					else
        						Desire = new Se_Reproduire();
        				} else 
        					Desire = new Dormir();	//Immature
        			}
        			else
        			{
        			//FEMELLE      				
       					// femelle 
       					if(cycle_sexuel() >=0  && cycle_sexuel() < 3 )
       					{	
       						if(fecondee())
       						{	// non fécondable
       							if(compassion())
       							{
       								Desire = new Soigner();	
       							}
       							else if(agressive())
       							{
       								cout << "Agresser()  ...non implémenté...";
       								//Desire = new Agresser();	
       							}
       							else
       							{
       								//recolte
       								if(pleine())
	        							Desire = new Deposer();
        							else
	        							Desire = new Recolter();
        						}
       						}
       						else
       						{
       							//Fertile
        						if(agressive())
	       							cout << "Agresser()  ...non implémenté...";
       								//Desire = new Agresser();
       							else if(compassion())
       								Desire = new Soigner();
       							else
           							Desire = new Se_Reproduire();
           					}
       					}
       					else
       					{
       						// non fertile
       						if(agressive())
       							cout << "Agresser()  ...non implémenté...";
       							//Desire = new Agresser();
       						else if(compassion())
       							Desire = new Soigner();
       						else
       						{
       							//recolte
       							if(pleine())
        							Desire = new Deposer();
        						else
        							Desire = new Recolter();
        					}
        				}
        			}
        		} else {
        			// Bébé ou Oeuf
        			Desire = new Dormir();
        		}
        	}
        	
        } 
        else if (Jour_Nuit.jour_nuit == CREPUSCULE)
        {
        cout << "Crépuscule ...";
        // CRESPUSCULE
        	if(malade())
        		Desire = new Se_Soigner();
        	else if(soif())
        		Desire = new Boire();
        	else if(faim())
        		Desire = new Manger();
        	else
        		Desire = new Dormir();
        
        } 
        else 
        {
        //Il fait Nuit
        	cout << "Nuit ...";
       		Desire = new Dormir();
       	}
       	cout << " ==> ";
        Desire->affiche_desire(verbal);
        return balises.vivant;
}
/* ********************************************************************************************************************

										 _____ ___________ _____ _______   __
										/  __ \  _  | ___ \_   _|  ___\ \ / /
										| /  \/ | | | |_/ / | | | |__  \ V / 
										| |   | | | |    /  | | |  __| /   \ 
										| \__/\ \_/ / |\ \  | | | |___/ /^\ \
 										 \____/\___/\_| \_| \_/ \____/\/   \/
			                                     
                                     
  										  ___  _____ _____ _____ _____ _   _  _____ 
 										 / _ \/  __ \_   _|_   _|  _  | \ | |/  ___|
										/ /_\ \ /  \/ | |   | | | | | |  \| |\ `--. 
										|  _  | |     | |   | | | | | | . ` | `--. \
										| | | | \__/\ | |  _| |_\ \_/ / |\  |/\__/ /
										\_| |_/\____/ \_/  \___/ \___/\_| \_/\____/ 

*/

bool Cocix::cortex_Action(bool verbal){
	JourNuit Jour_Nuit;

	cout << "\n****     C O R T E X   -   A C T I O N      ****\n";
	Jour_Nuit._jour_nuit();
	if(verbal){
		
		cout << "\tCycle Journalier : ";
		
		cout << "\n";

		cout << "\t(" << Jour_Nuit.heure << ":" << Jour_Nuit.minute << ")\n";
				
		cout << "\tDésire => " << Desire->desire << "\n";
				
		cout << "\tAction en cours => " << Action->get_action() << "\n";
	}

	// verifi l'etape de la CoCiX
		if(etape() == ETAT_OEUF) {
			// aucune action
			if(verbal) cout << "Aucune action pour l'oeuf !\n";
			return(vivant());
		}
		
		// action des Bébé
		if(etape() == ETAT_BEBE){
			
			if(verbal) cout << "Bébé => TODO\n";
			// TO DO
			return(vivant());
		}

		if(Jour_Nuit.jour_nuit == JOUR){
			// il fait jour
			if(verbal) {
					
				cout << "L'action <" << Desire->get_desire() << "> est-elle faisable ? : ";
					
				cout << "Fonction de validation interne à l'Action (" << Desire->get_desire() << ") ...";
			}
			if(Desire->valide_Action(this ,verbal)){
				//faisable
				if(verbal) cout << " OUI ! ";
					// est-on déjà en train de faire cette action ?
					if(*Action == *Desire){
							//oui
						if(verbal) cout << " Je suis déjà en train de faire cette action !! \n";
							
					} else {
							//non
						if(verbal) 
						{
							cout << " Mais je fait autre chose : " << Action->get_action() <<"\n";
							
							cout << "Peut-on arreter l'action en cours ou est-elle terminée ? : ";
						}
						if(Action->terminee()) {
							//oui
							if(verbal) cout << "OUI ! \n\t ==> On va commencer l'action demandée.\n";
								 	
							Action = Desire;
							Action->set_temps_ecoule(0);
								
						} else {
								//non
							if(verbal) cout << "NON ! \n\t ==> ON CONTINUE L'ACTION EN COURS!! \n";
						}
					}
			} else {
				//non faisable
				if(verbal) cout << " NON \nPeut-on arrêter l'action en cours ou est-elle terminée ? : ";
				if(Action->terminee()) {
					//oui
					if(verbal) cout <<"OUI ! \n\t ==> On va prendre l'action alternative : "<< Desire->Action_alternative->get_action() << "\n";
						// on va prendre l'alternative
					
					Action = Desire->Action_alternative;
					Action->set_temps_ecoule(0);

				} else {
					//non
					if(verbal) cout << "NON ! \n\t ==> Je continue ce que je fais alors!! \n";
				}
			}
			Action->go(this,verbal);
			return vivant();	

		} else {
					////////////////////////////////////////    N U I T    //////////////////////////////////////
		}
		return vivant();
}

void Cocix::raz_balises( bool verbal)
{
	// Init balise Coma & malade
	if(verbal) cout << "Mise à Zero des balise Coma & Malade\n";

	balises.coma = false;
	balises.malade = false;
	balises.faim = false;
	balises.froid = false;
	balises.agressive = false;
}

void Cocix::maj_balises( bool verbal){
	cout << "\n ***** MAJ des balises *****\n";
	cout << "Agr";
	balises.agressive = alert_agressive();
	balises.froid = alert_froid(verbal);
	balises.faim = alert_faim(verbal);
	balises.soif = alert_soif(verbal);
	balises.vivant = vivant();
	if(balises.vivant) cout << " - Vivant\n";
	else cout << " - Morte\n";
}

bool Cocix::alert_agressive()
{
	// calcul l'agresivité
	float taux_agressivite;
	int hasard;
	taux_agressivite = genome[AGRESSIVITE].valeur;	// pourcentage d'agressivite
	hasard = aleatoire(1,100);
	return(hasard > (int)(taux_agressivite * 100.0f)); 
}

bool Cocix::compassion()
{		//calcul de la compassion
	float taux_compassion;
	int hasard;
	taux_compassion = genome[COMPASSION].valeur;	// pourcentage de compassion
	hasard = aleatoire(1,100);
	return (hasard > (int) (taux_compassion * 100.0f));

}

bool Cocix::alert_froid(bool verbal){
		
		float temp_froid = Temperature.get_valeur() - (Temperature.get_valeur() * genome[FROID].valeur); // à revoir *******************************************
		
		if(verbal)
			cout << "\n - Temp Ext = " << temp_exterieur << "°C, J'ai froid si la temp descend en dessous de " << temp_froid << "°C !\n";
		else
			cout << "- temp";
		if(rentree()){
			if(verbal) cout << "Mais je suis chez moi !\n";
			return false;
		} else {
			return (temp_exterieur < temp_froid);
		}
}

bool Cocix::alert_faim(bool verbal){
	// renvoi vrai si le seuil de ressenti de la faim est dépassé
	bool faim;
	faim = (Calorie.get_valeur(true) < genome[FAIM].valeur);
		
	// vérifie que le seuil des COMA_CALORIE% n'est pas atteint si oui -> coma
	if(Calorie.get_valeur(true) < COMA_CALORIE) {
			balises.coma = true;
			if(verbal) cout << "Calorie < " << (COMA_CALORIE * 100) << "% de cc => COMA !\n";
			else cout << " - faim=>coma";
			return faim;
	}
	cout << " - faim"; 
	return faim;
}

bool Cocix::alert_soif(bool verbal)
{
	// renvoi vrai si  le seuil de ressenti de la soif est dépassé ou si la température exterieure > TEMPERATURE_SOIF
	bool soif;
	if(temp_exterieur > TEMPERATURE_SOIF)
	{
		if(verbal) cout << "Température exterieure (" << temp_exterieur << "°C) > " << TEMPERATURE_SOIF << "°C => j'ai soif !\n";
		else cout << " - soif";
		return true;
	}

	soif = (Hydro.get_valeur(true) < genome[SOIF].valeur);
	
	// vérifie que le seuil  COMA_HYDRO% n'est pas atteint si oui -> coma	
	if(Hydro.get_valeur(true) < COMA_HYDRO)
	{
		balises.coma = true;
		if(verbal) cout << "Hydro < " << (COMA_HYDRO * 100) << "% de ch => COMA ! \n";
		else cout << "- soif=>coma";
		return soif;
	}
	cout << " - soif";
	return soif;
}

void Cocix::vieillissement(bool verbal){
			// Alors on diminue le Capital Santé CS de  genome[VIEILLISSEMENT].valeur % par cycle
			if(Sante.get_capacite() >= genome[SEUIL_ACCEL_VIEILLE].valeur)
			{
				Sante.set_capacite(Sante.get_capacite() - (Sante.get_capacite() * genome[VIEILLISSEMENT].valeur));
				if(verbal) cout << "VIEILLESSE ===> Capital Santé - " << (genome[VIEILLISSEMENT].valeur * 100) << "% = " << Sante.get_capacite() << "\n";
			}
			else 
			{
				Sante.set_capacite(Sante.get_capacite() - genome[VIEILLISSEMENT].valeur );
				if(verbal) cout << "VIEILLESSE ===> Capital Santé - "<< genome[VIEILLISSEMENT].valeur << " = " << Sante.get_capacite() << "\n";
			}

			if(Sante.get_capacite() < 1) Sante.set_capacite(0.0f); // mort
			if(Sante.get_valeur() > Sante.get_capacite()) Sante.set_valeur(Sante.get_capacite(), &balises , false); 
}


/*
			| |\| |¯ |¯| |¯| |\/| /¯\ ¯|¯ | |¯| |\| 
			| | | |¯ |_| |¯\ |  | |¯|  |  | |_| | | 
*/
void Cocix::affiche(const bool genetique,const bool verbal){
	cout<<"\nCocix n° "<< id << " : " << nom;
	if(date_naissance > 0)
	{	
		cout << " en " << case_presence << (rentree()?" rentré(e)\n":"\n");
		cout << ((sexe == MALE)?"Mâle ":"Femelle ");
		if(vivant())
		{
			cout << "de " << age() << " jour(s)\n";
			cout << "Cycle Sexuel = " << cycle_sexuel() << "\n";
		}
		else
		{
			cout << "Mort(e) à " << age() << " jour(s)\n";
		}
	}
	else
	{
		cout << " - Oeuf dans CoCiX N°" << get_idMere() << "\n";
	}

	if(fecondee())
	{
		cout << "Porte l'oeuf #" << get_id_oeuf() << "\n";
	}

	if(get_id_partenaire() !=0)
	{
		cout << "Partenaire n° " << get_id_partenaire() << "\n";
	}

	Sante.affiche(true,verbal);
	Hydro.affiche(false, verbal);
	Calorie.affiche(false, verbal);
	Temperature.affiche(false, verbal);

	affiche_balises();
	cout << "Contient " << nb_genes << " gènes.\n";
	if(genetique){
		unsigned int i;
		for(i=0;i <  genome.size();i++){
			genome.at(i).affiche();
		}
	}
	cout << "Je désire ";
	Desire->affiche_desire();
	Action->affiche_action();

}
bool Cocix::rentree() const
{
// fonction qui renvoie vrai si la fourmiz est rentrée chez elle
		return (case_presence == case_naissance);
}

short Cocix::etape(){
		short age;
		age = (int) this->age();
		if(age <= 1) return ETAT_OEUF;
		if(age > 1 && age < MATURITE) return ETAT_BEBE;
		if(age >= MATURITE && age < vieux) return ETAT_ADULTE;
		return ETAT_VIEUX;
}

bool Cocix::vivant(){
	// s'il y a une date de mort c'est que je suis mort !! et donc pas vivant !!
	return (date_mort == 0);
}

bool Cocix::coma(){
	return balises.coma;
}

bool Cocix::malade(){
	return balises.malade;
}

bool Cocix::fecondee() const{
	return balises.fecondee;
}

bool Cocix::soif(){
	return balises.soif;
}

bool Cocix::faim(){
	return balises.faim;
}

bool Cocix::froid(){
	return balises.froid;
}

bool Cocix::pleine() const{
	// fonction qui renvoi vrai si la CoCiX ne peut plus récolter
	// la récolte peut dépasser la quantité maximal sur une prise 
		return(recolte >= genome[RECOLTE].valeur);
}

bool Cocix::male() const
{
	return (sexe == MALE);
}

bool Cocix::agressive(){
	return balises.agressive;
}

short Cocix::age() const
{
		JourNuit Jour_Nuit;
		if(date_naissance == 0 ) return 0;

		if(balises.vivant){
			return (Jour_Nuit.jours - date_naissance);
		} else {
			return (date_mort - date_naissance);	
		}
}

short Cocix::cycle_sexuel() const
{
	short cycle;
	// on revoie en numérique  (-1,0,1,2,3,4)
	// si age < age maturité sexuelle alors les Mâles & femelles sont immatures
	if(age() < MATURITE) return IMMATURE;

	if(male()) return 0;
	cycle = (( age() - MATURITE ) % 5);
	return cycle;
}

void Cocix::affiche_balises(){

	cout << "-------------------------------------------------------\n";
	cout << "| Fec | Viv | Mor | Mal | Com | Agr | Fro | Fai | Soi |\n";
	cout << "-------------------------------------------------------\n";
	cout << "|  " << ((fecondee()) ? "X":" ") << "  |  " << ((balises.vivant) ? "X":" ") << "  |  " << ((balises.mort) ? "X":" ") <<
	"  |  " << ((malade()) ? "X":" ") << "  |  " << ((balises.coma) ? "X":" ") << "  |  " << 
	((balises.agressive) ? "X":" ") << "  |  " << ((froid()) ? "X":" ") << "  |  " << ((faim()) ? "X":" ") << 
	"  |  " << ((soif()) ? "X":" ") << "  |\n";
	cout << "-------------------------------------------------------\n";
}

void Cocix::affiche_action(const bool verbal)
{
	Action->affiche_action(verbal);
}

void Cocix::affiche_desire(const bool verbal)
{
	Desire->affiche_desire(verbal);
}

void Cocix::prend_temperature(const bool verbal)
{
	if(get_date_naissance() == 0 )
		{
			// je prend la température de la case de la mère
			Cocix *maman;
			if(verbal) cout << "Je prend la température de la case de ma mère\n";
			maman = new Cocix( get_idMere(), false, verbal);
			temp_exterieur = temperature(maman->get_case_presence());
			delete maman;
		}
		else
		{
			temp_exterieur = temperature(case_presence);
		}

}

int Cocix::consanguinite(int idC,  bool verbal)
{
	int consG = -1;
	Cocix *C;
	if(verbal) cout << "Calcul de consanguinité avec # " << idC << " = ";
	C = new Cocix(idC,false,false);
	if(C->get_id() > 0 )
	{
		consG = calcul_consanguin(this, C);
		if(verbal) cout << consG << "\n";
	}
	else
	{
		cout << "Erreur au chargement du CoCiX N° " << idC << "\n";
	}
	delete C;
	return consG;
}

/********************************************************************************************************************
										FICHIERS
*/

bool Cocix::sauvegarde(bool verbal){

	char nomFichier[30] = "";
	sprintf(nomFichier, "%s%s", REPERTOIRE_NID, fichier);
	if(verbal) cout << "Sauvegarde de " << nomFichier << " ...";
	ofstream f (nomFichier, ios::out | ios::binary);

  	if(!f.is_open())
    {
      cout << " Impossible d'ouvrir le fichier '" <<  nomFichier << "' en ecriture !... Interrompue";
      f.close();
      return false;
      
    } else {
    	// Paramètre d'identité
    	f.write ((char*) &id, sizeof (int));
    	f.write ((char*) &nom, sizeof (char[10]));
    	f.write ((char*) &idPere, sizeof (int));
    	f.write ((char*) &idMere, sizeof (int));
    	f.write ((char*) &date_naissance, sizeof (short));
    	f.write ((char*) &date_mort, sizeof (short));
    	f.write ((char*) &sexe,1);
    	f.write ((char*) &case_presence, sizeof (short));
    	f.write ((char*) &case_naissance, sizeof (short));
    	f.write ((char*) &vieux , sizeof (short));
    	f.write ((char*) &vivacite , sizeof(short));
    	f.write ((char*) &recolte, sizeof(short));
    	f.write ((char*) &id_partenaire, sizeof(int));
    	f.write ((char*) &id_oeuf, sizeof(int));
    	// balises etat
    	f.write ((char*) &balises.fecondee ,1);
    	f.write ((char*) &balises.vivant ,1);
    	f.write ((char*) &balises.mort ,1);
    	f.write ((char*) &balises.malade ,1);
    	f.write ((char*) &balises.coma ,1);
    	f.write ((char*) &balises.agressive,1);
    	f.write ((char*) &balises.froid,1);
    	f.write ((char*) &balises.faim,1);
    	f.write ((char*) &balises.soif,1);
    	// Parametres Etat
    	Sante.sauvegarde(&f);
    	Calorie.sauvegarde(&f);
    	Hydro.sauvegarde(&f);
    	Temperature.sauvegarde(&f);



    	// on sauvegarde le nombre de Genes
    	f.write ((char*) &nb_genes, sizeof(int));
    	if(verbal) cout << "sauvegarde des " << nb_genes << " Gène(s).\n";
    	
    	// Sauvegarde Genome
    	int i = 0, total = 0;
    	do
    	{
    		genome[i].sauvegarde(&f);
    		total += sizeof(Gene);
    	} while( ++i < nb_genes);

    	if(verbal) cout << "Taille des Genes = " << total << "\n";
    	//f.write ((char*) &genome, sizeof(genome) );

    	// Sauvegarde Action 
    	Action->sauvegarde(&f);
    	//sauvegarde le numero Id de l 'Action' Désirée
    	short numDesire;
    	numDesire = Desire->get_id();
    	f.write ((char*) &numDesire, sizeof(short));
    	
    	// sauvegarde des ancetres
    	i = 0;
    	int temp;
    	do
    	{
    		temp = get_ancetre(i);
    		f.write ((char*) &temp, sizeof(int));
    	} while (++i < 30);
    	

    	if(verbal) cout << " Terminée (taille : " << sizeof(*this) << " o)\n";
 	}
 	f.close();
 	return true;
}

bool Cocix::chargement(bool verbal){
	
	// lecture dans fichier 
    char nomFichier[30] = "";
	sprintf(nomFichier, "%s%s", REPERTOIRE_NID, fichier);
	if(verbal) cout << "Chargement de " << nomFichier << " ... ";
    ifstream f(nomFichier, std::ios::binary);
  	if (!f){
      	cout << "Impossible de lire dans le fichier :'" << nomFichier << "'";
      	return false;
      	
    } else {
    	// Paramètres d'identité
    	f.read((char*) &id, sizeof(int));
    	f.read((char*) &nom, sizeof(char[10]));
    	f.read((char*) &idPere, sizeof(int));
    	f.read((char*) &idMere, sizeof(int));
    	f.read((char*) &date_naissance, sizeof(short));
    	f.read((char*) &date_mort, sizeof(short));
    	f.read((char*) &sexe, 1);
    	f.read((char*) &case_presence, sizeof(short));
    	f.read((char*) &case_naissance, sizeof(short));
    	f.read((char*) &vieux, sizeof(short));
    	f.read((char*) &vivacite, sizeof(short));
    	f.read((char*) &recolte, sizeof(short));
    	f.read((char*) &id_partenaire, sizeof(int));
    	f.read((char*) &id_oeuf, sizeof(int));

    	// balises etat
    	f.read ((char*) &balises.fecondee ,1);
    	f.read ((char*) &balises.vivant ,1);
    	f.read ((char*) &balises.mort ,1);
    	f.read ((char*) &balises.malade ,1);
    	f.read ((char*) &balises.coma ,1);
    	f.read ((char*) &balises.agressive ,1);
    	f.read ((char*) &balises.froid ,1);
    	f.read ((char*) &balises.faim ,1);
    	f.read ((char*) &balises.soif ,1);
    	// Param Etat

    	Sante.charge(&f);
    	Calorie.charge(&f);
    	Hydro.charge(&f);
    	Temperature.charge(&f);
    	// charge Genome
    	// on récupère le nombre de gènes
    	f.read((char*) &nb_genes, sizeof(int));
    	if(nb_genes<0 || nb_genes > MAX_GEN) nb_genes = MAX_GEN;
    	//f.read ((char*) &genome, (sizeof(Gene) * MAX_GEN ));
    	//cout << "Taille du genome = " << sizeof(genome) << "\n";
    	if(verbal) cout << "Chargement des " << nb_genes << " Gène(s).\n";
    	int i = 0;
    	Gene *gene;
    	do
    	{
    		gene  = new Gene();
    		gene->charge(&f);
    		genome.insert(genome.end(),*gene);
    	} while(++i < nb_genes);
    	delete gene;
		
		// charge NumAction
		short numAction,x_temps_ecoule;
		bool x_action_terminee;
		f.read ((char*) &numAction, sizeof(short));
		f.read((char*) &x_temps_ecoule, sizeof(short));
		f.read((char*) &x_action_terminee,1);

		switch(numAction){
			case DORMIR:
				Action = new Dormir();
				break;
			case MANGER:
				Action = new Manger();
				break;
			case BOIRE:
				Action = new Boire();
				break;
			case CHERCHE_EAU:
				Action = new Cherche_Eau();
				break;
			case RENTRER:
				Action = new Rentrer();
				break;
			case SE_SOIGNER:
				Action = new Se_Soigner();
				break;
			case RECOLTER:
				Action = new Recolter();
				break;
			case CHERCHE_RECOLTE:
				Action = new Cherche_Recolte();
				break;
			case DEPOSER:
				Action = new Deposer();
				break;
			case SE_REPRODUIRE:
				Action = new Se_Reproduire();
				break;
			case CHERCHE_PARTENAIRE:
				Action = new Cherche_Partenaire();
				break;
			case PONDRE:
				Action = new Pondre();
				break;
			case CHERCHE_CASE_LIBRE:
				Action = new Cherche_Case_Libre();
				break;
			case SOIGNER:
				Action = new Soigner();
				break;
			case CHERCHE_MALADE:
				Action = new Cherche_Malade();
				break;
			default:
				cout << "ERREUR: Je n'ai pas trouvé l'Action : " << numAction << "->Action init à Dormir()...";
				Action = new Dormir();
		}
		// il faut charger les infos sur l'action en cours
		Action->set_action_terminee( x_action_terminee );
		Action->set_temps_ecoule( x_temps_ecoule );

		// chargement du désire
		short numDesire;
		f.read((char* ) &numDesire , sizeof(short));

		switch(numDesire)
		{
			case DORMIR:
				Desire = new Dormir();
				break;
			case MANGER:
				Desire = new Manger();
				break;
			case BOIRE:
				Desire = new Boire();
				break;
			case CHERCHE_EAU:
				Desire = new Cherche_Eau();
				break;
			case RENTRER:
				Desire = new Rentrer();
				break;
			case SE_SOIGNER:
				Desire = new Se_Soigner();
				break;
			case RECOLTER:
				Desire = new Recolter();
				break;
			case CHERCHE_RECOLTE:
				Desire = new Cherche_Recolte();
				break;
			case DEPOSER:
				Desire = new Deposer();
				break;
			case SE_REPRODUIRE:
				Desire = new Se_Reproduire();
				break;
			case CHERCHE_PARTENAIRE:
				Desire = new Cherche_Partenaire();
				break;
			case PONDRE:
				Desire = new Pondre();
				break;
			case CHERCHE_CASE_LIBRE:
				Desire = new Cherche_Case_Libre();
				break;	
			case SOIGNER:
				Desire = new Soigner();
				break;
			case CHERCHE_MALADE:
				Desire = new Cherche_Malade();
				break;
			default:
				cout << "ERREUR: Je n'ai pas trouvé le Desire : " << numDesire << "->Desire init à Dormir()...";
				Desire = new Dormir();

			
			
		}
		// chargement des ancetres
			i = 0;
			int temp;
			do
			{
				f.read ((char*) &temp , sizeof(int));
				set_ancetre(i,temp);
			} while (++i < 30);

  	 	f.close();
  	 	return true;
	}
}

void Cocix::ancetre()
{
	int i;
	i = 14;
	do
	{
		cout << ancetres[i] << " ";

	} while ( ++i < 30);
	cout << "\n";

	i = 6;
	do
	{
		cout << "  " << ancetres[i] << "  ";
	} while (++i < 14);
	cout << "\n";
	i = 2;
	do
	{
		cout << "      " << ancetres[i] << "      ";
	} while (++i < 6);
	cout << "\n" << ancetres[0] << "\t\t" << ancetres[1] << "\n";
}