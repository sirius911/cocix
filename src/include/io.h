#ifndef DEF_IO
#define DEF_IO
#include "constantes.h"

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
void affiche_nid();

#endif