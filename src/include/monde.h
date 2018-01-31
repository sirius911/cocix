#ifndef DEF_MONDE
#define DEF_MONDE


#include <string>
#include <map>

#include "constantes.h"
#include "io.h"

using namespace std;

struct struct_xy
{
	short x;
	short y;
};

float temperature(short );
float nourriture(short );
float humidite(short );
float radioactivite(short );
void affiche_case(short , bool  info=true); //affiche 
void affiche_grille(short);
short xy_to_case(short const,short const); 	// (x,y) ==> IdCase
short xy_to_case(struct_xy const);		// struct_xy ==> IdCase
struct_xy case_to_xy(short const);
short valide_case(short);
int nbCocix( short numCase);			//renvoi le nombre de CoCiX sur numCase ou 0 si vide
const char* nbCocixGraph(const short numCase);	// renvoi une chaine de longueur fixe comme "**********" ou "   ****   "
bool libre(short const numCase);	// renvoi vrai si le Nb de Cocix sur numCase < MAX_PAR_CASE


// deplacements
bool bouge(int numCocix, short depart, short arrivee, bool verbal= false );
short monte_gauche(short);
short monte_droite(short);
short descend_gauche(short);
short descend_droite(short);
short monte(short);
short descend(short);
short gauche(short);
short droite(short);

float prend_element(short,float,int); // prend sur la case short, un element type d'un quantite float

//fonctions diverses
void affiche_map(const multimap <float, short, greater<float> > &);
short meilleur_case(short , int , bool, bool=false);	 // fonction revoyant la case avec la meilleur infos

#endif
