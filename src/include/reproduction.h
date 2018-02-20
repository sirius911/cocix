#ifndef DEF_REPRODUCTION
#define DEF_REPRODUCTION


#include "reproduction.h"
#include <iostream>
#include <iomanip>
#include <map>
#include "constantes.h"

#include "monde.h"
//#include "io.h"
#include "class/Cocix.h"
#include <string>
#include <map>

#include "constantes.h"

int partenaire(const short num_case, const Cocix *cocix, const bool verbal); // renvoi le numero du CoCiX compatible ou 0
short meilleur_case_partenaire(short case_centrale, Cocix *cocix, bool verbal);
int procreation (Cocix *Male, Cocix *Femelle, bool verbal);
int calcul_consanguin(const  Cocix* , const Cocix*); 		// renvoi le un int (plus le chiffre est elevé plus faible est la consanguinite) -1 indique qu'il y a aucun ancetre commun
#endif