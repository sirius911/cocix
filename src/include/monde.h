#ifndef DEF_MONDE
#define DEF_MONDE


#include <string>
#include <map>

#include "constantes.h"
#include "io.h"
#include "class/Cocix.h"
using namespace std;

struct struct_xy
{
	short x;
	short y;
};

enum
{
	// POUR LES INFOS A CHERCHER DANS MONDE
	EAU  = 1,			// recherche d'eau
	NOURRITURE = 2,	// recherche nourriture
};

float temperature(const short );	//revoi la température de la case
float nourriture(const short );	// renvoi la quantite de nourriture
float humidite(const short );		// renvoi la quantité d'eau
float radioactivite(const short );	// renvoi la quantité de radioactivité
void affiche_case(short , bool  info=true); //affiche 
void affiche_grille(short);		// affiche les 25 cases autour d'une case
short xy_to_case(short const,short const); 	// (x,y) ==> IdCase
short xy_to_case(struct_xy const);		// struct_xy ==> IdCase
struct_xy case_to_xy(short const);		// renvoi la structure x,y d'une case
short valide_case(short);				// ferme le monde 
int nbCocix( short numCase);			//renvoi le nombre de CoCiX sur numCase ou 0 si vide
const char* nbCocixGraph(const short numCase);	// renvoi une chaine de longueur fixe comme "**********" ou "   ****   "
bool libre(short const numCase);	// renvoi vrai si le Nb de Cocix sur numCase < MAX_PAR_CASE
short case_libre(const short numCase); // renvoi la case premiere case libre autour de la case centrale

void efface_trace(const short,const int id=0, const bool verbal = false);	// efface les traces des CoCiX sur la case
bool marque_trace(const short num_case, const int id, const bool verbal=false); // inscript l'Id du CoCiX sur la case si libre renvoi vrai si cela a fonctionné
int existe(const short num_case, const int id, const bool verbal = false);// renvoi le numero de position du CoCiX id  num_case ou -1 si absent
int malade(const short num_case, const Cocix *cocix, const bool verbal); // renvoi le num id du plus malade des Cocix sur num_case
// deplacements
bool bouge(const int numCocix, const short depart, const short arrivee, const bool verbal= false );	// bouge de case départ à case d'arrivée
short aller(const short depart, const short arrivee, const bool= false ); // renvoi la case intermédière pour bouger départ à arrivée danz un monde fermé
short monte_gauche(short);
short monte_droite(short);
short descend_gauche(short);
short descend_droite(short);
short monte(short);
short descend(short);
short gauche(short);
short droite(short);

float prend_element(short case_a_prendre, float quantite, int type); // prend sur la case short, un element type, d'une quantite float
void ajoute_element(short case_depose, float quantite, int type);	// rajoute sue la case hort un elemet type, d'une quantite float

//fonctions diverses
void affiche_map(const multimap <float, short, greater<float> > &);	// pour l'affichage des éléments recherchés
void affiche_map(const multimap <int, int, greater<int> > &);	// pour l'affichage des consanguinité
short meilleur_case(short case_centrale , int info , bool libre, short recole = 0, bool=false);	 // fonction revoyant la case avec la meilleur infos
short meilleur_case_malade(short case_centrale, Cocix *cocix, bool verbal); // fonction renvoyant la case contenant le CoCiX le plus malade ou 0
short case_hasard(const short case_centrale); // renvoi une des 8 cases entourant case_centrale au hazard
#endif
