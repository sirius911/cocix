#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define VERSION_LOGICIEL "0.3 Beta"
#ifndef DEBUG
	#define DEBUG false
#endif
#define MUET false

#define MALE 1
#define FEMELLE 0

#define JOUR 1
#define NUIT -1
#define CREPUSCULE 0

#define COMA_CALORIE 0.05			// 5%de CC en dessous duquel => COMA
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

// ETAPE CoCiX
#define ETAT_OEUF 0
#define ETAT_BEBE 1
#define ETAT_ADULTE 2
#define ETAT_VIEUX 3
#define MATURITE 4	// Age de la maturité sexuelle en jours
#define IMMATURE -1


//  **************************************************      GENETIQUE
/*
		Modes de transmission:
		P => transmission par le père
		M => transmission par la mère
		PM => transmission par le père OU la mère
		pm => transmission de père en fils ou de mère en fille
		GP => transmission par un des deux Grands pères (saute une génération)
		GM => transmission par une des deux grands mères
		H => transmission par les males p, gp_m, gp_p
		F => transmission par les femelles m, gm_m , gm_p
		m6 => transmission par les 6 membres
		*/
#define P 0
#define M 1
#define PM 3
#define pm 4
#define GP 5
#define GM 6
#define H 7
#define F 8
#define m6 9


#define MAX_GEN 23

#define ASSIMILATION_CALORIQUE 0
#define ASSIMILATION_HYDRIQUE 1
#define CALORIE 2
#define FAIM 3
#define FROID 4
#define HYDRO 5
#define SANTE 6
#define SATIETE 7
#define SOIF 8
#define TEMP 9
#define VIEUX 10
#define SOUFFRE_FAIM 11
#define SOUFFRE_SOIF 12
#define RECUP_SOMMEIL 13
#define RECOLTE 14
#define AGRESSIVITE 15
#define VIVACITE 16
#define SOINS 17
#define SEUIL_MALADE 18
#define SEUIL_COMA 19
#define VIEILLISSEMENT 20
#define SEUIL_ACCEL_VIEILLE 21
#define COMPASSION 22

//   ****************************************************************** Actions

#define BOIRE 1
#define CHERCHE_EAU 2
#define CHERCHE_NOURRITURE 3
#define CHERCHE_PARTENAIRE 4
#define DORMIR 6
#define MANGER 8
#define PONDRE 9
#define CHERCHE_CASE_LIBRE 10
#define RENTRER 11
#define SE_REPRODUIRE 12
#define SE_SOIGNER 14
#define RECOLTER 15
#define DEPOSER 16
#define CHERCHE_RECOLTE 17

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

// POUR LES INFOS A CHERCHER DANS MONDE
#define EAU 1			// recherche d'eau
#define NOURRITURE 2	// recherche nourriture

#endif