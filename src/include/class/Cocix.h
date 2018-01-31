#ifndef DEF_CLASS_COCIX
#define DEF_CLASS_COCIX

#include "../constantes.h"
#include "Gene.h"
#include "Param_Etat.h"
#include "Actions/Actions.h"


using namespace std;


class Cocix
{
	public:

		Cocix();
		Cocix(int);	//constructeur
		~Cocix();	//destructeur
		Cocix(int, char[10], int, int,short, bool, short, short, short, short,Gene *, Param_Etat, Param_Etat, Param_Etat, Param_Etat );
		
		

		void creation_Toto(int);	// pour le debug
		void creation_Titi(int);	// pour le debug

		int id;				// Id unique
		char nom[10];	
		int idPere;
		int idMere;
		short date_naissance;
		short date_mort;
		bool sexe;
		short case_presence;
		short case_naissance;
		short vieux;
		short recolte;
		
		// parmetres genetiques
	
		Gene genome[MAX_GEN]; 

		// Paramètre d'Etat;
		Param_Etat Sante;
		Param_Etat Calorie;
		Param_Etat Hydro;
		Param_Etat Temperature;

		// Balise binaires d'etat
		struct struct_balises balises;

		// Actions & désires
		Actions *Desire;
		Actions *Action;
		// methodes
		
		int vie(bool = false);
		bool cortex_Etat(bool=false);	// Fonction du Cortex d'etat
		bool cortex_Action(bool=false); // Fonction du Cortex d'Action
		void maj_balises(bool=false);
		bool alert_agressive();
		bool alert_froid(bool=false);
		bool alert_faim(bool=false);
		bool alert_soif(bool=false);
		bool agressive();
		bool rentree();
		bool vivant();

		// methodes d'informations ou d'affichage
		void affiche(bool genetique = false);
		void affiche_balises();
		short etape();	// renvoi l'etape bébé (OEUF,BEBE,ADULTE ou VIEUX)
		short age();	// Age actuel ou à sa mort
		bool coma();
		bool malade();
		bool fecondee();
		bool soif();
		bool froid();
		bool faim();
		bool pleine();
		bool male();
		short cycle_sexuel();

		// SETTER
		int set_id();

		bool sauvegarde(bool verbal = false);
	private:
		
		bool chargement(bool verbal = false);
		void vieillissement(bool verbal = false);

		float temp_exterieur;
};

#endif