#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <cstdlib>

#include "include/class/Cocix.h"
#include "include/class/JourNuit.h"

#include "include/class/Actions/Actions.h"
#include "include/class/Actions/Dormir.h"
#include "include/class/Actions/Manger.h"
#include "include/class/Actions/Boire.h"
#include "include/constantes.h"
#include "include/io.h"
#include "include/monde.h"

using namespace std;

int main(int nbArg, char* argv[])
{
	//bool muet = false;
	JourNuit Jour_Nuit;
	srand(time(NULL));

	char commande[20] = "";
	Cocix CoCiX;
	int i;
	bool sortie = false;
	bool verbal = false;
	bool sauvegarde = false;
	char prompt[30] = "<Aucun CoCiX [noSav][muet]>";
	char nomCocix[15] = "Aucun CoCiX";
	

	cout << "\f";
	cout << " _____   _____   _____   _  __    __ \n";
	cout << "/  ___| /  _  \\ /  ___| | | \\ \\  / / \n";
	cout << "| |     | | | | | |     | |  \\ \\/ /  \n";
	cout << "| |     | | | | | |     | |   }  {   \n";
	cout << "| |___  | |_| | | |___  | |  / /\\ \\  \n";
	cout << "\\_____| \\_____/ \\_____| |_| /_/  \\_\\ \n";
	cout << "		" << VERSION_LOGICIEL << "\n";
	cout << "   ******************************\n";
	Jour_Nuit.status();

	cout << "\n";
	cout << "Tapez votre commande (quit pour quitter).\n";
	if( nbArg == 1){

		// Aucun argument
		do
		{
			strcpy(commande,"");
			cout << prompt;
			cin >> commande;
			//
			if(strcmp(commande,"load") == 0)
			{
				// on charge une CoCiX
				cout << "Entrez le N° du CoCiX (0 pour sortir) : ";
				cin >> i;
				if ( i != 0 )
				{
					CoCiX = Cocix(i);

					if(CoCiX.set_id() > 0 )
					{ 
						strcpy(nomCocix,CoCiX.nom);
						CoCiX.affiche(false);
						strcpy(prompt,"<");
						strcat(prompt, nomCocix);
						strcat(prompt, (sauvegarde)?" [Sav]":" [noSav]");
						strcat(prompt, (verbal)?"[verbal]>":"[muet]>");
					}
					else
					{
						cout << "CoCiX non trouvé !\n";
						strcpy(nomCocix,"Aucun CoCiX");
						strcpy(prompt,"<");
						strcat(prompt, nomCocix);
						strcat(prompt, (sauvegarde)?" [Sav]":" [noSav]");
						strcat(prompt, (verbal)?"[verbal]>":"[muet]>");
					}
				} else
					exit(0);
				
			} else if((strcmp(commande,"help")==0) || (strcmp(commande,"h") == 0))
			{

					cout << "Commandes : \n";
					cout << "\tquit\n";
					cout << "\taffiche\n";
					cout << "\taffichecase\n";
					cout << "\teau\n";
					cout << "\tnouriture\n";
					cout << "\tsauvegarde\n";
					cout << "\tmodesauvegarde\n";
					cout << "\tmuet\n";
					cout << "\tverbal\n";
					cout << "\tgenetique\n";
					cout << "\tcortexetat\n";
					cout << "\tgrille\n";
					cout << "\tpresence\n";
					cout << "\tdesire\n";
					cout << "\taction\n";
					cout << "\tgo\n";

			} else if((strcmp(commande,"quit")==0) || (strcmp(commande,"QUIT") == 0) || (strcmp(commande,"q") == 0)){
					sortie = true;
			
			} else if((strcmp(commande,"nid")==0))
			{
					affiche_nid();

			} else if((strcmp(commande,"affiche")==0))
			{
					if(CoCiX.id != 0)
					{
						CoCiX.affiche(verbal);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
					
			} else if((strcmp(commande,"sauvegarde")==0))
			{
					if(CoCiX.id != 0)
					{
						CoCiX.sauvegarde(verbal);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}

			} else if((strcmp(commande,"muet")==0))
			{
					verbal = false;
					cout << "Mode " <<((verbal)?"Verbal\n":"Muet\n");
					strcpy(prompt,"<");
					strcat(prompt, nomCocix);
					strcat(prompt, (sauvegarde)?" [Sav]":" [noSav]");
					strcat(prompt, "[muet]>");
			
			} else if((strcmp(commande,"verbal")==0))
			{
					verbal = true;
					cout << "Mode " <<((verbal)?"Verbal\n":"Muet\n");
					strcpy(prompt,"<");
					strcat(prompt, nomCocix);
					strcat(prompt, (sauvegarde)?" [Sav]":" [noSav]");
					strcat(prompt, "[verbal]>");
			
			
			} else if((strcmp(commande,"modesauvegarde")==0))
			{
					sauvegarde = !sauvegarde;
					if(sauvegarde) cout << "Sauvegarde activée.\n";
					else	cout << "Sauvegarde désactivée.( sauf déplacements)\n";
					strcpy(prompt,"<");
					strcat(prompt, nomCocix);
					strcat(prompt, (sauvegarde)?" [Sav]":" [noSav]");
					strcat(prompt, (verbal)?"[verbal]>":"[muet]>");

			} else if((strcmp(commande,"genetique")==0))
			{
					if(CoCiX.id != 0)
					{
						CoCiX.affiche(true);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			}  else if((strcmp(commande,"cortexetat")==0))
			{
					if(CoCiX.id != 0){
						CoCiX.cortex_Etat(verbal);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			} else if((strcmp(commande,"grille")==0))
			{
					if(CoCiX.id != 0)
					{
						affiche_grille(CoCiX.case_presence);
					} else 
					{
						cout << "Numero de case ? : ";
						cin >> i;
						affiche_grille(valide_case(i));
					}

			} else if((strcmp(commande,"affichecase")==0))
			{
					if(CoCiX.id != 0)
					{
						affiche_case(CoCiX.case_presence,verbal);
					} else 
					{
						cout << "Numero de case ? : ";
						cin >> i;
						affiche_case(valide_case(i), verbal );
					}

			}else if((strcmp(commande,"eau")==0))
			{
					if(CoCiX.id != 0)
					{
						cout << "Il y a "<< humidite(CoCiX.case_presence) << "uml sur " <<CoCiX.case_presence<<"\n";
					} else 
					{
						cout << "Numero de case ? : ";
						cin >> i;
						cout << "Il y a "<< humidite(valide_case(i)) << "uml sur " <<i<<"\n";
					}
			}else if((strcmp(commande,"nourriture")==0))
			{
					if(CoCiX.id != 0)
					{
						cout << "Il y a "<< nourriture(CoCiX.case_presence) << "cal sur " <<CoCiX.case_presence<<"\n";
					} else 
					{
						cout << "Numero de case ? : ";
						cin >> i;
						cout << "Il y a "<< nourriture(valide_case(i)) << "cal sur " <<i<<"\n";
					}
			} else if((strcmp(commande,"presence")==0))
			{
					if(CoCiX.id != 0)
					{
						nbCocix(CoCiX.case_presence);
					} else 
					{
						cout << "Numero de case ? : ";
						cin >> i;
						cout << "il y a " << nbCocix(valide_case(i)) << " CoCix\n";
					}

			} else if ((strcmp(commande,"desire")==0))
			{
					if(CoCiX.id != 0){
						cout << "Désire => ";
						CoCiX.Desire->affiche_desire(verbal);
						cout << "\n";
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			} else if ((strcmp(commande,"vie")==0))
			{
					if(CoCiX.id != 0){
						CoCiX.vie(verbal);
						cout << "\n";
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			} else if((strcmp(commande,"bouge")==0))
			{
					if(CoCiX.id != 0){
						int arrivee;
						cout << "Numero case d'arrivée : ";
						cin >> arrivee;
						if(bouge(CoCiX.id, CoCiX.case_presence,valide_case(arrivee)))
						{
							CoCiX.case_presence = arrivee;
							CoCiX.sauvegarde();
						}
						else
						{
							cout << "Problème de déplacement... je ne sauvegarde par " << CoCiX.nom << "\n";
						}
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}


			} else if((strcmp(commande,"action")==0))
			{
					if(CoCiX.id != 0){
						cout << "Action => ";
						CoCiX.Desire->affiche_action(verbal);
						cout << "\n";
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}

			} else if((strcmp(commande,"go")==0))
			{
				if(CoCiX.id != 0){
						CoCiX.Desire->go(&CoCiX);
						CoCiX.affiche(false);
						
				} else {
						cout << "Aucune CoCix chargée ... (load)\n";
				}

			} else {
				cout << commande << " Non compris !\n";
			}

		} while(!sortie);
		cout << "Au revoir !\n";
		return 0;
	}


}
