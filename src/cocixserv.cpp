#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

#include "include/constantes.h"
#include "include/class/JourNuit.h"

#define HELP "--help"

using namespace std;

void help(){
		cout << "Utilisation : cocixserv --commande [OPTION]\n";
		cout << "\nGestion du serveur des CoCiX et du cycle Jour/Nuit.\n";
		cout << "	--help                  Aide.\n";
		cout << "	--start                 Met le serveur en marche.\n";
		cout << "	--stop                  Stoppe le serveur.\n";
		cout << "	--status                Affiche le status du serveur.\n";
		cout << "	--version               Affiche la version du logiciel.\n";
		cout << "	--incremente [vitesse]  Avance le cycle à la vitesse donnée.\n";	
		cout << "	--index [XX]			Affiche ou initalise l'indexCocix\n";
		cout << "	--heurenuit [hh]        Affiche ou initialise l'heure de tombée de la nuit [0-24].\n";
		cout << "	--heurejour [hh]        Affiche ou initialise l'heure du lever de soleil [0-24].\n";
		cout << "	--jour [jjj]            Affiche ou initialise le nombre de jours depuis le BigBang (jjj).\n";
		cout << "	--heure [xx]            Affiche ou initialise l'heure des CoCiX [0-24].\n";
		cout << "	--minute [xx]           Affiche ou initialise les minutes des CoCiX [0-60].\n\n";
		cout << "	--vitesse [vitesse]     Affiche ou initialise la vitesse d'Incrémentation en mn.\n";
		cout << "	-s                      Idem	--status\n";
		cout << "	-j [jjj]                Idem	--jour [jjj]\n";
		cout << "	-h [xx]                 Idem	--heure [xx]\n";
		cout << "	-m [xx]                 Idem	--minute [xx]\n\n";
		cout << "	-i [xx]                 Idem	--incremente [vitesse]\n";
		cout << "	-v [vitesse]            Idem	--vitesse [vitesse]\n";
		cout << "	-h                      Aide.\n";
}
void incremente( short vi, JourNuit * Jour_Nuit){
	//JourNuit Jour_Nuit;
	if(vi == 0 ) vi = Jour_Nuit->vitesse;
	if(Jour_Nuit->marche){
		cout << " *** SERVEUR EN MARCHE ***\n";
		cout << "Incrémentation du cycle journalier ...(Vitesse : " << vi << " mn)\n";
		cout << "Avant Jour N° " << Jour_Nuit->jours << " - " << Jour_Nuit->heure << ":" << Jour_Nuit->minute << "    ====>    ";
		Jour_Nuit->minute += vi;
		while( Jour_Nuit->minute >= 60 )
		{
			// une heure de passée
			Jour_Nuit->minute -= 60;
			Jour_Nuit->heure++;
			if(Jour_Nuit->heure >= 24) {
				// un jour de passé
				Jour_Nuit->heure -= 24;
				Jour_Nuit->jours++;
			}
		} 
		cout << "Après Jour N° " << Jour_Nuit->jours << " - " << Jour_Nuit->heure << ":" << Jour_Nuit->minute << "\n";

		Jour_Nuit->maj_jour_nuit();
		Jour_Nuit->ecrireDonnees();

	} else {
		cout << " *** SERVEUR ARRETE ***\n";
	}

}
int main(int nbArg, char* argv[]){
	JourNuit Jour_Nuit;

	if( nbArg == 1 || strcmp(argv[1],"--help") == 0 ){
		help();
		return 0;
	}

	if(strcmp(argv[1] , "--status") == 0 || strcmp(argv[1] , "-s") == 0){
		Jour_Nuit.status();
		return 0;
	}

	if(strcmp(argv[1] , "--start") == 0 ) {
		Jour_Nuit.marche = true;
		Jour_Nuit.ecrireDonnees();
		cout << "Serveur démaré !\n";
		return 0;
	}

	if(strcmp(argv[1] , "--stop") == 0 ){
		Jour_Nuit.marche = false;
		Jour_Nuit.ecrireDonnees();
		cout << "Serveur arrêté !\n";
		return 0;
	}

	if(strcmp(argv[1] , "--version") == 0  || strcmp(argv[1] , "-v") == 0){
		cout << " _____   _____   _____   _  __    __ \n";
		cout << "/  ___| /  _  \\ /  ___| | | \\ \\  / / \n";
		cout << "| |     | | | | | |     | |  \\ \\/ /  \n";
		cout << "| |     | | | | | |     | |   }  {   \n";
		cout << "| |___  | |_| | | |___  | |  / /\\ \\  \n";
		cout << "\\_____| \\_____/ \\_____| |_| /_/  \\_\\ \n";
		cout << "       " << VERSION_LOGICIEL << "\n";
		cout << "\n";
		return 0;
	}

	if(strcmp(argv[1] , "-i") == 0 || strcmp(argv[1] , "--incremente") == 0){
		if(nbArg > 2){
			int i;
			i = atoi( argv[2]);
			incremente((short) i, &Jour_Nuit );
		} else 
			incremente(0, &Jour_Nuit);
		
		return 0;
	}

	if(strcmp(argv[1] , "--index") == 0 || strcmp(argv[1] , "-x") == 0 ) 
	{
		if(nbArg > 2)
		{
			int i;
			i = atoi( argv[2] );
			if( i >= 0)
			{
				Jour_Nuit.set_indexCocix(i);
				cout << "Nouvel index = " << Jour_Nuit._indexCocix() << "\n";
			}
			else
			{
				cout << "!erreur... pas d'index correct !\n";
			}
		}
		else
		{
			cout << "Index actuel = " << Jour_Nuit._indexCocix() << "\n";
		}
		return 0;
	}

	if(strcmp(argv[1] , "--heurenuit") == 0 ){

		if(nbArg > 2 ){
			short i;
			i = (short) atoi( argv [2]);
			if( i >= 0 && i < 24){
				Jour_Nuit.heure_nuit = i;
				Jour_Nuit.maj_jour_nuit();
				Jour_Nuit.ecrireDonnees();
				cout << " La nuit tombe à " << Jour_Nuit.heure_nuit << "h00 ! \n";
				return 0;	
			} else
				help();
		} else 
			cout << " La nuit tombe à " << Jour_Nuit.heure_nuit << "h00 ! \n";		
		return 0;
	}

	if(strcmp(argv[1] , "--heurejour") == 0 ){

		if(nbArg > 2 ){
			short i;
			i = (short) atoi( argv [2]);
			if( i >= 0 && i < 24){
				Jour_Nuit.heure_jour = i;
				Jour_Nuit.maj_jour_nuit();
				Jour_Nuit.ecrireDonnees();
				cout << " Le soleil se lève à " << Jour_Nuit.heure_jour << "h00 ! \n";
				return 0;	
			} else
				help();
		} else 
			cout << " Le soleil se lève à " << Jour_Nuit.heure_jour << "h00 ! \n";		
		return 0;
 	}

 	if(strcmp(argv[1] , "--jour") == 0 || strcmp(argv[1] , "-j") == 0){

		if(nbArg > 2 ){
			short i;
			i = (short) atoi( argv [2]);
			if( i >= 0 && i < 5000){
				Jour_Nuit.jours = i;
				Jour_Nuit.ecrireDonnees();
				cout << "Jour N° " << Jour_Nuit.jours << "   " << Jour_Nuit.heure << "h" << Jour_Nuit.minute << "\n";
				return 0;	
			} else
				help();
		} else 
			cout << "Jour N° " << Jour_Nuit.jours << "   " << Jour_Nuit.heure << "h" << Jour_Nuit.minute << "\n";		
		return 0;
 	}

 	if(strcmp(argv[1] , "-h") == 0  || strcmp(argv[1] , "--heure") == 0){

		if(nbArg > 2 ){
			short i;
			i = (short) atoi( argv [2]);
			if( i >= 0 && i < 24){
				Jour_Nuit.heure = i;
				Jour_Nuit.maj_jour_nuit();
				Jour_Nuit.ecrireDonnees();
				cout << "Jour N° " << Jour_Nuit.jours << "   " << Jour_Nuit.heure << "h" << Jour_Nuit.minute << "\n";
				return 0;	
			} else
				help();
		} else 
			cout << "Jour N° " << Jour_Nuit.jours << "   " << Jour_Nuit.heure << "h" << Jour_Nuit.minute << "\n";		
		return 0;
 	}

 	if(strcmp(argv[1] , "-m") == 0 || strcmp(argv[1] , "--minute") == 0){

		if(nbArg > 2 ){
			short i;
			i = (short) atoi( argv [2]);
			if( i >= 0 && i < 60){
				Jour_Nuit.minute = i;
				Jour_Nuit.ecrireDonnees();
				cout << "Jour N° " << Jour_Nuit.jours << "   " << Jour_Nuit.heure << "h" << Jour_Nuit.minute << "\n";
				return 0;	
			} else
				help();
		} else
			cout << "Jour N° " << Jour_Nuit.jours << "   " << Jour_Nuit.heure << "h" << Jour_Nuit.minute << "\n";		
		return 0;
 	}

 	if(strcmp(argv[1] , "-v") == 0 || strcmp(argv[1] , "--vitesse") == 0){

		if(nbArg > 2 ){
			short i;
			i = (short) atoi( argv [2]);
			if( i >= 0 && i < 60){
				Jour_Nuit.vitesse = i;
				Jour_Nuit.ecrireDonnees();
				cout << "Vitesse = " << Jour_Nuit.vitesse << " mn par cycle.\n";
				return 0;	
			} else
				help();
		} else
			cout << "Vitesse = " << Jour_Nuit.vitesse << " mn par cycle.\n";
		
		return 0;

 	}
 	help();
	return 0;
}

