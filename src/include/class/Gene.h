#ifndef DEF_CLASS_GENE
#define DEF_CLASS_GENE

#include <string>
#include <fstream>

using namespace std;

class Gene
{
	public:



		Gene();	//constructeur
		Gene(const char[30] ,int ,float ,float,float, float, float, float, float, int, bool);

		char nom[30];	// nom unique
		int id;				// Id unique
		float valeur;		// valeur du gène
		float pere;			// du père
		float mere;			// de la mère
		float gp_mere;		// grand-père Maternel
		float gp_pere;		// grand-père Paternel
		float gm_mere;		// grand-mère Maternelle
		float gm_pere;		// grand-mère Paternelle
		int mod_trans;		// mode de transmission
		bool pourc;			// est un pourcentage

		//methodes

		void affiche();
		const char* trans();
		int sauvegarde(ofstream*);
		int charge(ifstream*);

		enum
		{
			MAX_GEN = 23,

			ASSIMILATION_CALORIQUE = 0,
			ASSIMILATION_HYDRIQUE = 1,
			CALORIE = 2,
			FAIM = 3,
			FROID = 4,
			HYDRO = 5,
			SANTE = 6,
			SATIETE = 7,
			SOIF = 8,
			TEMP = 9,
			VIEUX = 10,
			SOUFFRE_FAIM = 11,
			SOUFFRE_SOIF = 12,
			RECUP_SOMMEIL = 13,
			RECOLTE = 14,
			AGRESSIVITE = 15,
			VIVACITE = 16,
			SOINS = 17,
			SEUIL_MALADE = 18,
			SEUIL_COMA = 19,
			VIEILLISSEMENT = 20,
			SEUIL_ACCEL_VIEILLE = 21,
			COMPASSION = 22,
			P = 0,
			M = 1,
			PM = 3,
			pm = 4,
			GP = 5,
			GM = 6,
			H = 7,
			F = 8,
			m6 = 9
		};

	private:
		const string affiche(const float);
};

#endif