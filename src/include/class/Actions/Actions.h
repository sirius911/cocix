#ifndef DEF_CLASS_ACTIONS
#define DEF_CLASS_ACTIONS

#include <fstream>
#include <iostream>

class Cocix;	// pour éviter la récurence d'un #include "Cocix.h"

class Actions{

	private:
		bool action_terminee;		// Action terminée
		short temps_ecoule;	// Temps écoulé depuis le début de l'action
		short id;			// N° ID de l'Action
		short duree;		// Durée normale de l'action
		float chaleur;		// Chaleur engendrée
		float eau;			// eau consommée
		float calorie;		// Calories consommées

	public:

		enum
		{
			BOIRE = 1,
 			CHERCHE_EAU = 2,
			CHERCHE_NOURRITURE = 3,
			CHERCHE_PARTENAIRE = 4,
			SOIGNER = 5,
			DORMIR  = 6,
			CHERCHE_MALADE = 7,
			MANGER = 8,
			PONDRE = 9,
			CHERCHE_CASE_LIBRE = 10,
			RENTRER = 11,
			SE_REPRODUIRE = 12,
			SE_SOIGNER = 14,
			RECOLTER = 15,
			DEPOSER = 16,
			CHERCHE_RECOLTE = 17
		};

		char action[30];	// Verbe conjugué
		char desire[30];	// Désire à l'infinitif
		
		bool deplacement;	//Action nécessitant un déplacement
		bool peut_etre_stoppee;	//Action pouvant être stoppée

		Actions * Action_alternative;		

		// constructeurs
		Actions();
		Actions(bool,short);

		// utilitaires d'affichage
		void affiche_action(bool info=false);
		void affiche_desire(bool verbal=false);
		void index();

		// Getter & Setter
		void set_action_terminee(bool);
		bool get_action_terminee();

		void set_temps_ecoule(short);
		short get_temps_ecoule();

		void set_id(short);
		short get_id();

		void set_duree(short);
		short get_duree();

		void set_chaleur(float);
		float get_chaleur();

		void set_eau(float);
		float get_eau();

		void set_calorie(float);
		float get_calorie();

		char* get_action();
		char* get_desire();

		// Méthodes des Actions
		virtual void go(Cocix*, const bool=false);
		virtual bool valide_Action(const Cocix*, const bool=false);
		void le_temps_s_ecoule(bool=false);
		int sauvegarde(std::ofstream*);

		bool equal(Actions A);

		bool terminee();	// renvoi vrai si l'action est terminée
};


bool operator == ( Actions &action1 ,  Actions &action2);
bool operator != ( Actions &action1 ,  Actions &action2);
/*
bool operator == ( Actions &action1 ,  Actions action2);
bool operator != ( Actions &action1 ,  Actions action2);*/
#endif