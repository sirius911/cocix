#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <math.h>
#include <fstream>
#include <dirent.h>
#include <cstring>

#ifndef WIN32
    #include <sys/types.h>
#endif


#include "io.h"
#include "constantes.h"

using namespace std;

int aleatoire (int x, int y){
	// renvoi un nombre int aléatoire entre x et y
	float nombre_aleatoire;
	int a;	// pour la permutation x,y
	if(x>y){
		a=x;
		x=y;
		y=a;
	}
	nombre_aleatoire = rand();
	return( (int) (nombre_aleatoire * (y+1 - x) / RAND_MAX + x ));
}

ligneCase lirecase (short const num_case)

{
	int numLigne;
	struct ligneCase ligneSortie;
	
	numLigne = num_case - 1;	// num_case =[1;10000] mais lecture des lignes de 0 à 9999
    if(numLigne < 0 || numLigne >= MAX_CASE)
    {
    	cout << "ERREUR : Essais de lire une ligne dans '" << FICHIER_MONDE << "' en dehors des limites : " << numLigne << " !\n";
    	return ligneSortie;
    }

  	long deplacement;
    
  	deplacement = (long)(LONGUEUR_LIGNE * numLigne);	// longueur ligne = 56 Octets
  
    // lecture dans FICHER_MONDE
    ifstream f_in (FICHIER_MONDE, ios::in|ios::binary);

  	if (!f_in)
    {
      	cout << "\nImpossible de lire dans le fichier " << FICHIER_MONDE << "\n";
      	exit(-1);
    }
    // je me déplace à la bonne ligne
    f_in.seekg(deplacement,ios::beg);

    // je lit la ligne
    f_in.read ((char *) &ligneSortie, sizeof(ligneSortie));
    f_in.close();
	
  	return ligneSortie;

}

void ecrireligne(short x_case, ligneCase * x_donnee){

	long deplacement;
	short x_ligne = (short) x_case -1;	// on ecrit sur les ligne [0 , 9999]
 	deplacement = (long)(LONGUEUR_LIGNE * x_ligne);	// longueur ligne = 56 Octets


 	ofstream f_in (FICHIER_MONDE, ios::in | ios::out | ios::binary);
  	if(!f_in.is_open()){
    	 cout << "Impossible d'ouvrir le fichier "<< FICHIER_MONDE << " en écriture !\n";
    	exit (-1);
    } 
    else
    {
    	// je me déplace dans le fichier à la bonne ligne
    	f_in.seekp(deplacement,ios::beg);

	 	//cout << "Ecriture sur ligne : " << x_ligne << " -> deplacement = " << deplacement << "long enr => " << sizeof(ligneCase) << "\n";
 	 	f_in.write((char *)x_donnee, sizeof(ligneCase));
 	}
 	f_in.close();

}

bool isCocix(char* s)
{
    return(! strstr(s, ".cox") == 0);
}

void lireDossier(const char* s, DIR* rep)
{
    struct dirent* ent = NULL;
    char * nom_fichier_cocix;

    cout << " -- Lecture du Nid '" << s << "' -- \n";

    while ((ent = readdir(rep)) != NULL)
    {/* Lecture du dossier. */
        nom_fichier_cocix = ent->d_name;
        if(isCocix(nom_fichier_cocix))
           cout << " --> " << ent->d_name << "\n";
    } 
}

void affiche_nid()
{
    DIR* rep = NULL;
    rep = opendir(REPERTOIRE_NID); /* Ouverture d'un dossier */

    if (rep == NULL)
     { /* Si le dossier n'a pas pu être ouvert */
         cout << "Le dossier "<< REPERTOIRE_NID << " n'a pas pu être ouvert !!\n";
     	 return;
     }
	//cout << "Dossier ouvert\n";
	lireDossier(REPERTOIRE_NID,rep);

    if (closedir(rep) == -1)
    { /* S'il y a eu un souci avec la fermeture */
    	cout << "il y a eu un souci avec la fermeture\n";
	}
    return ;
}


