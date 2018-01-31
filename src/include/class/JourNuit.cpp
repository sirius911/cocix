#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <cstring>

#include "../constantes.h"

#include "../monde.h"
#include "../io.h"
#include "JourNuit.h"


using namespace std;

JourNuit::JourNuit(){
	lireDonnees();
		/*marche = true;
  	  	time(&bigbang);
  	  	vitesse = 4;
		minute = 49;
		heure = 9;
		jour_nuit = 1;
		jours = 138;
		heure_nuit = 21;
		heure_jour = 7;
		time(&date);
		time(&date_temp);
		temp_N = 16;
		temp_NE = 17;
		temp_E = 18;
		temp_SE = 19;
		temp_S = 20;
		temp_SO = 21;
		temp_O = 22;
		temp_NO = 23;
		temp_C = 19.5f;
		ecrireDonnees();*/
}

JourNuit::JourNuit(bool x_marche, time_t x_bigbang, short x_vitesse, short x_minute, short x_heure, short x_jour_nuit, int x_jours,
	short x_heure_nuit, short x_heure_jour, time_t x_date, time_t x_date_temp, float x_temp_N, float x_temp_NE, float x_temp_E
	, float x_temp_SE, float x_temp_S, float x_temp_SO, float x_temp_O, float x_temp_NO, float x_temp_C){

		marche = x_marche;
  	  	bigbang = x_bigbang;
  	  	vitesse = x_vitesse;
		minute = x_minute;
		heure = x_heure;
		jour_nuit = x_jour_nuit;
		jours = x_jours;
		heure_nuit = x_heure_nuit;
		heure_jour = x_heure_jour;
		date = x_date;
		date_temp = x_date_temp;
		temp_N = x_temp_N;
		temp_NE = x_temp_NE;
		temp_E = x_temp_E;
		temp_SE = x_temp_SE;
		temp_S = x_temp_S;
		temp_SO = x_temp_SO;
		temp_O = x_temp_O;
		temp_NO = x_temp_NO;
		temp_C = x_temp_C;
		ecrireDonnees();
	/*
  	  	marche = true;
  	  	time(&bigbang);
  	  	vitesse = 4;
		minute = 49;
		heure = 9;
		jour_nuit = 1;
		jours = 138;
		heure_nuit = 21;
		heure_jour = 7;
		time(&date);
		time(&date_temp);
		temp_N = 16;
		temp_NE = 17;
		temp_E = 18;
		temp_SE = 19;
		temp_S = 20;
		temp_SO = 21;
		temp_O = 22;
		temp_NO = 23;
		temp_C = 19.5f;
		ecrireDonnees();
		*/
}

void JourNuit::lireDonnees(){

	// lecture dans fichier 
    ifstream fichier(FICHIER_JOUR_NUIT, std::ios::binary);
  	if (!fichier){
      	cout << "\nImpossible de lire dans le fichier " << FICHIER_JOUR_NUIT << "\n";
      	
    } else {
    	fichier.read((char*) this, sizeof(*this));
    	
  	 	fichier.close();
 
	}
}
void JourNuit::ecrireDonnees(){

	ofstream f (FICHIER_JOUR_NUIT, ios::out | ios::binary);
	maj_date();
  	if(!f.is_open())
    {
      cout << "\nImpossible d'ouvrir le fichier '" <<  FICHIER_JOUR_NUIT << "' en ecriture !" << "\n";
      f.close();
      
    } else {
    	f.write ((char*) this, sizeof (*this));
 	}
 	f.close();

}

void JourNuit::_date(){
	char date_text[80];
	struct tm * timeinfo;
	timeinfo = localtime(&date);
	strftime(date_text,80,"%a %d/%m/%Y  - %R",timeinfo);
	cout << date_text;
}

void JourNuit::_bigbang(){
	char date_text[80];
	struct tm * timeinfo;
	timeinfo = localtime(&bigbang);
	strftime(date_text,80,"%a %d/%m/%Y  - %R",timeinfo);
	cout << date_text;
}

void JourNuit::_date_temp(){
	char date_text[80];
	struct tm * timeinfo;
	timeinfo = localtime(&date_temp);
	strftime(date_text,80,"%a %d/%m/%Y  - %R",timeinfo);
	cout << date_text;
}

void JourNuit::_jour_nuit(){
	char jourNuitText[10];
	if(jour_nuit == JOUR)
		strcpy(jourNuitText , "Jour");
	else if(jour_nuit == NUIT)
		strcpy(jourNuitText , "Nuit");
	else 
		strcpy(jourNuitText , "Crépuscule");
	cout << jourNuitText;
}
void JourNuit::status(){

	cout << "\n\n********* SERVEUR **********\n";
	cout << "|                          |\n";
	if(marche) 	cout << "|        en marche         |\n";
	else 		cout << "|          Arrêté          |\n";
	
	cout << "|--------------------------|\n";
	cout << "|   Dernière Sauvegarde    |\n";
	cout << "| ";
	_date();
	cout << "  |\n";
	cout << "|--------------------------|\n";
	cout << "|       Date Bigbang       |\n";
	cout << "| ";
	_bigbang();
	cout << "  |\n";
	cout << "|--------------------------|\n";
	cout << "| Jour N° " << setw(4) << jours << "   " << setw(2) << heure << "h" << setw(2) << minute << "     |\n";
	switch(jour_nuit){
		case JOUR:
			cout << "|           JOUR           |\n";
			break;
		case NUIT:
			cout << "|           NUIT           |\n";
			break;
		case CREPUSCULE:
			cout << "|        CREPUSCULE        |\n";
			break;
	}
	cout << "|    Vitesse : x" << setw(4) << vitesse << " mn    |\n";
	cout << "| Nuit à " << setw(2) << heure_nuit << "h | Jour à " << setw(2) << heure_jour << "h  |\n";
	cout << "|--------------------------|\n";
	cout << "|         Météo au         |\n";
	cout << "| ";
	_date_temp();
	cout << "  |\n";
	cout << "|--------------------------|\n";
	cout << "|        |        |        |\n";
	cout << fixed << setprecision(1) << "| " << setw(4) << temp_NO << "°C | " << setw(4) << temp_N << "°C | " << setw(4) << temp_NE << "°C |\n";
	cout << "|________|________|________|\n";
	cout << "|        |        |        |\n";
	cout << "| " << setw(4) << temp_O << "°C | " << setw(4) << temp_C << "°C | " << setw(4) << temp_E << "°C |\n";
	cout << "|________|________|________|\n";
	cout << "|        |        |        |\n";
	cout << "| " << setw(4) << temp_SO << "°C | " << setw(4) << temp_S << "°C | " << setw(4) << temp_SE << "°C |\n";
	cout << "|________|________|________|\n";
}

void JourNuit::meteo(){
	cout << "METEO à " << ctime(&date_temp);
	cout << temp_N << " °C au Nord\n";
	cout << temp_NE << " °C au Nord-Est\n";
	cout << temp_E << " °C à Est\n";
	cout << temp_SE << " °C au Sud-Est\n";
	cout << temp_S << " °C au Sud\n";
	cout << temp_SO << " °C au Sud-Ouest\n";
	cout << temp_O << " °C à l'Ouest N\n";
	cout << temp_NO << " °C au NOrd-Ouest\n";
}

void JourNuit::maj_date(){
	time(&date);
}
void JourNuit::maj_bigbang(){
	time(&bigbang);
}

void JourNuit::maj_jour_nuit(){
	
		// détermination de la luminosité : 
		// couché du soleil à 21h
		// et levé à 7h

	if((heure == (heure_nuit - 2)) || (heure == (heure_nuit -1))) {
				jour_nuit = (short) CREPUSCULE; // une heure avant le couché du soleil
				//cout << "Il va bientôt faire nuit !\n";
		} else {
			
			if(heure >= heure_nuit || heure < heure_jour) {
					// il fait nuit
					jour_nuit = (short) NUIT;
					//cout << "Il fait nuit !\n";
			} else {					// il fait jour
					//cout << "Il fait jour !\n";
					jour_nuit = (short) JOUR;
			}
		}
}
