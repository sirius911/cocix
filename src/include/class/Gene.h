#ifndef DEF_CLASS_GENE
#define DEF_CLASS_GENE

#include <string>

using namespace std;

class Gene
{
	public:

		Gene();	//constructeur
		Gene(const char[30] ,int ,float ,float,float, float, float, float, float);

		char nom[30];	// nom unique
		int id;				// Id unique
		float valeur;		// valeur du gène
		float pere;			// du père
		float mere;			// de la mère
		float gp_mere;		// grand-père Maternel
		float gp_pere;		// grand-père Paternel
		float gm_mere;		// grand-mère Maternelle
		float gm_pere;		// grand-mère Paternelle
		//string influent; //Garder ?

		//methodes

		void affiche();
};

#endif