#ifndef DEF_IO
#define DEF_IO
#include "constantes.h"
#include <vector>
#include "monde.h"

using namespace std;

struct ligneCase {
	float nourriture; 
	float humidite; 
	float temperature; 
	float radioactivite; 
	int cocix[MAX_PAR_CASE];
};


ligneCase lirecase (short const);
void ecrireligne(short , ligneCase* );
int aleatoire (int x, int y);
vector<char*> affiche_nid(const bool num , const int flag_oeuf);	// falg oeuf = 0 pas les oeuf, 1 = que les oeufs, 2 les oeufs et les CoCiX
#endif