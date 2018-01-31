#ifndef DEF_PARAM_ETAT
#define DEF_PARAM_ETAT

#include <string>
#include <fstream>
#include <iostream>

#include "../constantes.h"
#include "Gene.h"

class Param_Etat{

	public:
		char nom[20];
		char unite[4];
		float capacite;
		float valeur;
		float limite_haute_malade;
		float limite_basse_malade;
		float limite_haute_coma;
		float limite_basse_coma;
		float limite_basse_souffrance;
		float limite_haute_souffrance;
		float correction_souffrance;

		//methodes
		void maj_balises(struct_balises*,const bool = false);
		void souffrance(Param_Etat*, const bool);
	
		Param_Etat();
		Param_Etat(const char[20], const char[3], float , float , float, float, float, float, float, float, float );

		float _valeur(bool pourcentage=false);	//getter
		void _valeur(float,struct_balises*);	//setter
		void affiche(bool pourcentage=false, bool limite = false);

		void modif(float modificateur, struct_balises*, const bool=false );

		int sauvegarde(ofstream*);
		int charge(ifstream*);
};
#endif
