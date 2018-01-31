#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>

#include "include/constantes.h"
#include "include/io.h"
#include "include/monde.h"

using namespace std;

/*
champs par défaut : 
250 calories
100 micro Litre
20 °C
0 Fourmiz
0 Fourmiz
Vide
0 rad
*/

int main(){

	int calorie_defaut,hydro_defaut,i,j;
	int cocix[MAX_PAR_CASE] = {0};
	
	float nombre_aleatoire,nourriture,humidite,temperature,radioactivite;
	
	long totalLigne = 0;

	calorie_defaut = 250;
	hydro_defaut = 100;

	srand(time(NULL));
	
	cout << "-------------------\n";
	cout << "CoCiX " << VERSION_LOGICIEL << "\n";
	cout << "-------------------\n\n";
	cout << "Initialisation de " << FICHIER_MONDE << "\n";
	ofstream f (FICHIER_MONDE, ios::out | ios::binary);

	if(!f.is_open()){
    	 cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
    	return -1;
    }
    i = 0;
	do{
		nombre_aleatoire = rand();
		nourriture = (int)(nombre_aleatoire * (calorie_defaut+1 - 0) / RAND_MAX + 0 );
		nombre_aleatoire = rand();
		humidite = (int)(nombre_aleatoire * (hydro_defaut+1 - 0) / RAND_MAX + 0 );
		nombre_aleatoire = rand();
		temperature = (int)(nombre_aleatoire * (35+1 - 10) / RAND_MAX + 10 );
		nombre_aleatoire = rand();
		radioactivite = (int)(nombre_aleatoire * (100+1 - 0) / RAND_MAX + 0 );
		f.write ((char *)&nourriture, sizeof(float));
		totalLigne += sizeof(float);
     	f.write ((char *)&humidite, sizeof(float));
     	totalLigne += sizeof(float);
     	f.write ((char *)&temperature, sizeof(float));
     	totalLigne += sizeof(float);
     	f.write ((char *)&radioactivite, sizeof(float));
     	totalLigne += sizeof(float);
     	// Tableau de 10 int
   		j = 0;
   		do {
   			f.write((char *) &cocix[j], sizeof(int));
   			totalLigne += sizeof(int);
   		} while(++j < MAX_PAR_CASE);
   		cout << "# " << i+1 << "\t";
		cout << nourriture << " Ca -- " << humidite << " uL -- " << temperature << " °C -- " << 
		radioactivite << " Rad => " << totalLigne << " Oc\n";
		totalLigne = 0;
	} while (++i < MAX_CASE - 1);
	cout << "Terminée\n";
    f.close();
	
	return 0;
}
