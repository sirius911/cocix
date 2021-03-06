#ifndef DEF_CLASS_COCIX
#define DEF_CLASS_COCIX

#include "../constantes.h"
#include "Gene.h"
#include "Param_Etat.h"
#include "Actions/Actions.h"
#include "Cortex/Cortex.h"

#include <vector>
#include <array>


using namespace std;

class Cortex;

class Cocix
{
	private:
		short date_naissance;
		short date_mort;
		int idPere;
		int idMere;
		short case_presence;
		short case_naissance;
		short recolte;
		int id_partenaire;
		int id_oeuf;
		bool chargement(bool verbal = false);
		
		char fichier[30];	//nom physique du fichier CoCiX .cox
		short vivacite;
		float temp_exterieur;
		array <int , 30 > ancetres;
		Cortex *cortex;

	public:

		Cocix();	//Constructeur Vide
		Cocix(const int, const bool oeuf=false, const bool verbal = false);	//constructeur avec numero de CoCiX
		Cocix(const char*, bool = false);	//Constructeur avec nom du Fichier
		~Cocix();	//destructeur

		void creation_Toto(int, const bool = true);	// pour le debug
		void creation_Titi(int, const bool = true);	// pour le debug

		int id;				// Id unique
		char nom[10];	
		
		bool sexe;
		
		short vieux;
		
		enum
	{
		FEMELLE = 0,
		MALE = 1,

		ETAT_OEUF = 0,
		ETAT_BEBE = 1,
		ETAT_ADULTE = 2,
		ETAT_VIEUX  = 3,
		MATURITE  = 4,	// Age de la maturité sexuelle en jours
		IMMATURE  = -1

	};

		
		// parmetres genetiques
		int nb_genes;	// nombre de gène
		//Gene genome[MAX_GEN]; 
		vector<Gene> genome;

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
		void meurt(bool verbal = false);
		bool cortex_Etat(const bool verbal = false);	// Fonction du Cortex d'etat
		bool cortex_Action(const bool verbal = false); // Fonction du Cortex d'Action
		void vieillissement(bool verbal = false);
		
		void prend_temperature(const bool = false);	// fonction qui prend la température de la case et maj temp_exterieur
		void raz_balises(const  bool verbal = false);
		void maj_balises(const bool verbal = false);
		bool alert_agressive();
		bool alert_froid(const bool verbal = false);
		bool alert_faim( const bool verbal = false);
		bool alert_soif(const bool verbal = false);
		bool agressive();
		bool compassion();
		bool rentree() const;
		bool vivant();

		// methodes d'informations ou d'affichage
		void affiche(const bool genetique = false , const bool verbal = false);
		void affiche_balises();
		void affiche_action(const bool verbal = false);
		void affiche_desire(const bool verbal = false);
		
		const int etape();	// renvoi l'etape bébé (OEUF,BEBE,ADULTE ou VIEUX)
		short age() const;	// Age actuel ou à sa mort
		bool coma();
		bool malade();
		bool fecondee() const;
		bool soif();
		bool froid();
		bool faim();
		bool pleine() const;
		bool male() const;
		short cycle_sexuel() const;

		void deplace(const short arrivee, const bool = false);

		// SETTER
		void set_id(int);
		void set_nom(char*);
		void set_date_naissance(short);
		void set_date_mort(short);
		void set_case_presence(short);
		void set_case_naissance(short);
		void marque_presence(const bool = false);
		void set_recolte(short);
		void set_id_partenaire(int);
		void set_id_oeuf(int);
		void set_sexe(bool);
		void set_fichier(const char*);
		void set_idPere(int);
		void set_idMere(int);
		void set_vieux(short);
		void set_vivacite(short);
		void set_nb_genes(int);

		// GETTER
		int get_id() const;
		char* get_fichier();
		short get_recolte();
		int get_idPere() const;
		int get_idMere() const;
		int get_id_partenaire() const;
		int get_id_oeuf() const;
		short get_vivacite() const;
		short get_case_presence() const;
		short get_case_naissance() const;
		int get_nb_genes() const;
		short get_date_naissance() const;
		short get_date_mort() const;
		float get_temp_exterieur() const;
		char* get_nom_cortex() const;


// ancêtres
		
		void ancetre();
		int get_ancetre(const short) const;
		void set_ancetre(short,int);
		int consanguinite(int,bool = false);	// renvoi la consanguinité avec un id d'un CoCiX


		bool sauvegarde(bool verbal = false);
};

#endif