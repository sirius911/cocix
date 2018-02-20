#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define VERSION_LOGICIEL "0.4 Beta"
#ifndef DEBUG
	#define DEBUG false
#endif
#define MUET false

#define COMA_CALORIE 0.05			// 5%de Calorie en dessous duquel => COMA
#define SOUFFRANCE_CALORIQUE 0.001	// correction à apporter si souffrance calorique
#define COMA_HYDRO	0.08				// 8%de CH en dessous duquel => COMA
#define SOUFFRANCE_HYDRIQUE 0.0017	// Correction à apporter si souffrance hydrique
#define SOUFFRANCE_MALADIE 0.00014	// Correction à apporter si souffrance Maladie
#define SOUFFRANCE_COMA 0.00007		// Correction à apporter si souffrance Coma
#define SOUFFRANCE_THERMIQUE 0.001	// Correction à apporter si souffrance thermique
#define TEMPERATURE_SOIF 35			// Température exterieur déclanchant la soif

#define FICHIER_MONDE "data/monde.dat"
#define LONGUEUR_LIGNE 56		// Longueur d'une ligne monde dans monde.dat en Octets
#define MAX_CASE 10000
#define MAX_PAR_CASE 10			// Nombre de CoCiX par case

#define FICHIER_JOUR_NUIT "./data/cycles.dat"
#define REPERTOIRE_NID "./data/nid/"
#define REPERTOIRE_CIMETIERE "./data/nid/cimetiere/"

struct struct_balises
		{
			bool fecondee;
			bool vivant;
			bool mort;
			bool malade;
			bool coma;
			bool agressive;
			bool froid;
			bool faim;
			bool soif;
		};


#endif