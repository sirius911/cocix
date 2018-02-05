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

		Cocix();	//Constructeur Vide
		Cocix(const int, bool = false);	//constructeur avec numero de CoCiX
		Cocix(const char*, bool = false);	//Constructeur avec nom du Fichier
		~Cocix();	//destructeur
		Cocix(int, char[10], int, int,short, bool, short, short, short, short,Gene *, Param_Etat, Param_Etat, Param_Etat, Param_Etat );
		
		

		void creation_Toto(int, const bool = true);	// pour le debug
		void creation_Titi(int, const bool = true);	// pour le debug

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


		// methodes de "vie"
		int vie(bool = false);
		bool cortex_Etat(const bool verbal = false);	// Fonction du Cortex d'etat
		bool cortex_Action(const bool verbal = false); // Fonction du Cortex d'Action

		void raz_balises(const  bool verbal = false);
		void maj_balises(const bool verbal = false);
		bool alert_agressive();
		bool alert_froid(const bool verbal = false);
		bool alert_faim( const bool verbal = false);
		bool alert_soif(const bool verbal = false);
		bool agressive();
		bool rentree() const;
		bool vivant();

		// methodes d'informations ou d'affichage
		void affiche(const bool genetique = false , const bool verbal = false);
		void affiche_balises();
		void affiche_action(const bool verbal = false);
		void affiche_desire(const bool verbal = false);
		
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

		void deplace(const short arrivee, const bool = false);

		// SETTER
		void set_case_presence(short);
		void marque_presence(const bool = false);

		// GETTER
		int get_id();



		bool sauvegarde(bool verbal = false);
	private:
		
		bool chargement(bool verbal = false);
		void vieillissement(bool verbal = false);
		char fichier[30];	//nom physique du fichier CoCiX .cox

		float temp_exterieur;
};

#endif