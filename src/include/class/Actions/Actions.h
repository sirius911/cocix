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

	public:

		char action[30];	// Verbe conjugué
		char desire[30];	// Désire à l'infinitif
		float chaleur;		// Chaleur engendrée
		float eau;			// eau consommée
		float calorie;		// Calories consommées
		
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


		// Méthodes des Actions
		virtual void faire();	//inutile 
		virtual void go(Cocix*,bool=false);
		virtual bool valide_Action(const bool=false);
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