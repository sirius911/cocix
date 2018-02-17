#ifndef DEF_PARAM_ETAT
#define DEF_PARAM_ETAT

#include <string>
#include <fstream>
#include <iostream>

#include "../constantes.h"
#include "Gene.h"

class Param_Etat{

	private:
		float valeur;
		char nom[20];
		float capacite;
		float plafond;
		float plancher;
		float limite_haute_malade;
		float limite_basse_malade;
		float limite_haute_coma;
		float limite_basse_coma;
		float limite_basse_souffrance;
		float limite_haute_souffrance;
		float correction_souffrance;

		void verif_bornes(const bool = false);
		void maj_balises(struct_balises*,const bool = false);
		

	public:
		char unite[4];
		
		//methodes
		bool souffrance(Param_Etat *XSante, const bool coma, const bool modif, const bool verbal = false);
	
		Param_Etat();
		Param_Etat(const char[20], const char[3], float , float , float, float, float, float, float, float, float, float, float );


		// Getters
		float get_valeur(bool pourcentage=false);
		float get_capacite();
		char* get_nom();
		//bool souffre();	// renvoie vrai si des limites sont dépassées et qu'il y a souffrance sur l'état

		// Setters
		void set_valeur(float,struct_balises*, bool control = true); // met une valeur avec controle et mise à jours des balises ou pas
		void set_capacite(float);

		
		void affiche(bool pourcentage=false, bool limite = false);

		void modif(float modificateur, struct_balises*, const bool=false );

		int sauvegarde(ofstream*);
		int charge(ifstream*);
};
#endif
