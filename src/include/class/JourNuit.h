#ifndef DEF_JOUR_NUIT
#define DEF_JOUR_NUIT

#include <ctime>

class JourNuit 
{
	public:
		//string nomFichier;
		bool marche;
		time_t bigbang;
		short vitesse;
		short minute;
		short heure;
		short jour_nuit;
		int jours;
		short heure_nuit;
		short heure_jour;
		time_t date;
		time_t date_temp;
		
		float temp_N;
		float temp_NE;
		float temp_E;
		float temp_SE;
		float temp_S;
		float temp_SO;
		float temp_O;
		float temp_NO;
		float temp_C;

		void lireDonnees();
		void ecrireDonnees();

	
		//constructeurs
		JourNuit();
		JourNuit(bool x_marche, time_t x_bigbang, short x_vitesse, short x_minute, short x_heure, short x_jour_nuit, int x_jours,
	short x_heure_nuit, short x_heure_jour, time_t x_date, time_t x_date_temp, float x_temp_N, float x_temp_NE, float x_temp_E
	, float x_temp_SE, float x_temp_S, float x_temp_SO, float x_temp_O, float x_temp_NO, float x_temp_C);

		void _date();
		void _bigbang();
		void _date_temp();
		void meteo();
		void status();
		void maj_date();
		void maj_bigbang();
		void maj_jour_nuit();
		void _jour_nuit();
};
#endif
