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

	private:
		const string affiche(const float);
};

#endif