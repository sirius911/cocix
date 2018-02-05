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
#include "include/class/Actions/Cherche_Eau.h"
#include "include/class/Actions/Cherche_Nourriture.h"
#include "include/class/Actions/Rentrer.h"
#include "include/class/Actions/Se_Soigner.h"

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
	char choix[] = "";
	Cocix *CoCiX = NULL;
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
				vector<char*> listeFichiers = affiche_nid(true);
				cout << "Entrez le Num du CoCiX : ";
				cin >> choix;
				int i = atoi(choix);
				if(i > 0 && i <= (int) listeFichiers.size())
				{
					CoCiX = new Cocix(listeFichiers[i-1],verbal);

					if(CoCiX->get_id() > 0 )
					{ 
						strcpy(nomCocix,CoCiX->nom);
						CoCiX->affiche(false);
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
				}
				else
				{
					cout << "Mauvais numéro !\n";
				}
				
			} else if((strcmp(commande,"aller")==0))
			{
				if( ! (CoCiX == (void*) NULL ))
					{
						cout << "Case où le CoCiX veut aller ? : ";
						cin >> i;
						CoCiX->deplace( aller (CoCiX->case_presence,i,verbal),verbal);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
				
			}
			else if((strcmp(commande,"help")==0) || (strcmp(commande,"h") == 0))
			{

					cout << "Commandes : \n";
					cout << "\taction\t\tAffiche l'Action en cours du CoCiX chargé.\n";
					cout << "\taffiche\t\tAffiche les infos du CoCiX chargé.\n";
					cout << "\tafficheCase\t\tAffiche les infos d'une case.\n";
					cout << "\tbalises\t\tAffiche les balises du CoCiX chargé.\n";
					cout << "\tcortexEtat\t\tLance la méthode cortex_etat() du CoCiX chargé.\n";
					cout << "\tcorteAction\t\tLance la méthode cortex_action() du CoCiX chargé.\n";
					cout << "\tdeplace\t\tDéplace le CoCiX sur une case.\n";
					cout << "\tdesire\t\tAffiche le désire en cours du CoCiX chargé.\n";
					cout << "\teau\t\tAffiche la quantité d'eau sur une case.\n";
					cout << "\teffacePresence\t\tEfface les présences sur une case.\n";
					cout << "\tforceAction\t\tForce une action pour le CoCiX chargé.\n";
					cout << "\tforceDesire\t\tForce un Désire pour le CoCiX chargé.\n";
					cout << "\tgenetique\t\tAffiche le genome du CoCiX chargé.\n";
					cout << "\tgo\t\tLance la methode go() du CoCiX chargé.\n";
					cout << "\tgrille\t\tAffiche les 25 cases (5x5) autour du CoCiX.\n";
					cout << "\tmarquePresence\t\tMarque la présence du Cocix sur sa case dans Monde\n";
					cout << "\tmodeSauvegarde\t\tPermute le mode de sauvegarde automatique.\n";
					cout << "\tmuet\t\tPermute en mode 'MUET'.\n";
					cout << "\tnid\t\tAffiche le nid.\n";
					cout << "\tnouriture\t\tAffiche la quantité de nourriture sur une case.\n";
					cout << "\tpresence\t\tAffiche le nombre de CoCiX sur une case.\n";
					cout << "\tquit\t\tPour quitter le programme.\n";
					cout << "\tsauvegarde\t\tSauvegarde le CoCiX chargé.\n";
					cout << "\tverbal\t\tPasse en mode 'Verbal'.\n";
					cout << "\tversion\t\tDonne la version du logiciel.\n";
					

			} else if((strcmp(commande,"quit")==0) || (strcmp(commande,"QUIT") == 0) || (strcmp(commande,"q") == 0)){
					sortie = true;
					//if( ! (CoCiX == (void*) NULL ))
					//	delete CoCiX;
			
			} else if((strcmp(commande,"version")==0) ){
					cout << "\f";
					cout << " _____   _____   _____   _  __    __ \n";
					cout << "/  ___| /  _  \\ /  ___| | | \\ \\  / / \n";
					cout << "| |     | | | | | |     | |  \\ \\/ /  \n";
					cout << "| |     | | | | | |     | |   }  {   \n";
					cout << "| |___  | |_| | | |___  | |  / /\\ \\  \n";
					cout << "\\_____| \\_____/ \\_____| |_| /_/  \\_\\ \n";
					cout << "		" << VERSION_LOGICIEL << "\n";
					cout << "   ******************************\n";
					
			
			} else if((strcmp(commande,"effacePresence")==0))
			{
					cout << "Entrez le numéro de la case : ";
					cin >> choix;
					int i = atoi(choix);
					if(i > 0 && i <= MAX_CASE)
					{
						efface_trace(valide_case(i),0,verbal);
					}
					else
					{
						cout << "Erreur de n° de case ![1-10000]\n";
					}

			}else if((strcmp(commande,"marquePresence")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						CoCiX->marque_presence(verbal);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}

			} else if((strcmp(commande,"nid")==0))
			{
					affiche_nid(false);

			} else if((strcmp(commande,"balises")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						CoCiX->affiche_balises();
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			} else if((strcmp(commande,"affiche")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						CoCiX->affiche(false,verbal);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
					
			} else if((strcmp(commande,"sauvegarde")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						CoCiX->sauvegarde(verbal);
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
					if( ! (CoCiX == (void*) NULL ))
					{
						CoCiX->affiche(true);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			}  else if((strcmp(commande,"cortexetat")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						CoCiX->cortex_Etat(verbal);
						if(sauvegarde)
							CoCiX->sauvegarde(verbal);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			} else if((strcmp(commande,"cortexaction")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						CoCiX->cortex_Action(verbal);
						if(sauvegarde)
							CoCiX->sauvegarde(verbal);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}

			} else if((strcmp(commande,"grille")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						affiche_grille(CoCiX->case_presence);
					} else 
					{
						cout << "Numero de case ? : ";
						cin >> i;
						affiche_grille(valide_case(i));
					}

			} else if((strcmp(commande,"affichecase")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						affiche_case(CoCiX->case_presence,verbal);
					} else 
					{
						cout << "Numero de case ? : ";
						cin >> i;
						affiche_case(valide_case(i), verbal );
					}

			}else if((strcmp(commande,"eau")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						cout << "Il y a "<< humidite(CoCiX->case_presence) << "uml sur " <<CoCiX->case_presence<<"\n";
					} else 
					{
						cout << "Numero de case ? : ";
						cin >> i;
						cout << "Il y a "<< humidite(valide_case(i)) << "uml sur " <<i<<"\n";
					}
			}else if((strcmp(commande,"nourriture")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						cout << "Il y a "<< nourriture(CoCiX->case_presence) << "cal sur " <<CoCiX->case_presence<<"\n";
					} else 
					{
						cout << "Numero de case ? : ";
						cin >> i;
						cout << "Il y a "<< nourriture(valide_case(i)) << "cal sur " <<i<<"\n";
					}
			} else if((strcmp(commande,"presence")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						nbCocix(CoCiX->case_presence);
					} else 
					{
						cout << "Numero de case ? : ";
						cin >> i;
						cout << "il y a " << nbCocix(valide_case(i)) << " CoCix\n";
					}

			} else if ((strcmp(commande,"desire")==0))
			{
					if( ! (CoCiX == (void*) NULL )){
						cout << "Désire => ";
						CoCiX->Desire->affiche_desire(verbal);
						cout << "\n";
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			} else if ((strcmp(commande,"vie")==0))
			{
					if( ! (CoCiX == (void*) NULL )){
						CoCiX->vie(verbal);
						cout << "\n";
						if(sauvegarde)
							CoCiX->sauvegarde(verbal);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			} else if((strcmp(commande,"deplace")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						int arrivee;
						cout << "Numero case d'arrivée : ";
						cin >> arrivee;
						CoCiX->deplace(valide_case(arrivee),verbal);
						
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}


			} else if((strcmp(commande,"action")==0))
			{
					if( ! (CoCiX == (void*) NULL )){
						cout << "Action => ";
						CoCiX->Action->affiche_action(verbal);
						cout << "\n";
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}

			} else if((strcmp(commande,"go")==0))
			{
				if( ! (CoCiX == (void*) NULL )){
						CoCiX->Desire->go(CoCiX, verbal);
						CoCiX->affiche(false);
						if(sauvegarde)
							CoCiX->sauvegarde(verbal);
						
				} else {
						cout << "Aucune CoCix chargée ... (load)\n";
				}

			} else if((strcmp(commande,"forceAction")==0) || (strcmp(commande,"forceDesire")==0))
			{
				if( ! (CoCiX == (void*) NULL )){
						cout << "Choisissez : \n";
						cout << BOIRE << " -> Boire()\n";
						cout << CHERCHE_EAU << " -> Cherche_Eau()\n";
						cout << CHERCHE_NOURRITURE << " -> Cherche_Nourriture()\n";
						cout << DORMIR << " -> Dormir()\n";
						cout << MANGER << " -> Manger()\n";
						cout << RENTRER << " -> Rentrer()\n";
						cout << SE_SOIGNER << " ->Se_Soigner()\n";
						cout << "\t votre choix : ";
						cin >> i;
						switch(i){
							case DORMIR:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Dormir();
								else
									CoCiX->Desire = new Dormir();
								break;
							case MANGER:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Manger();
								else
									CoCiX->Desire = new Manger();
								break;
							case BOIRE:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Boire();
								else
									CoCiX->Desire = new Boire();
								break;
							case CHERCHE_EAU:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Cherche_Eau();
								else
									CoCiX->Desire = new Cherche_Eau();
								break;
							case CHERCHE_NOURRITURE:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Cherche_Nourriture();
								else
									CoCiX->Desire = new Cherche_Nourriture();
								break;
							case RENTRER:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Rentrer();
								else
									CoCiX->Desire = new Rentrer();
								break;
							case SE_SOIGNER:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Se_Soigner();
								else
									CoCiX->Desire = new Se_Soigner();
								break;
							default:
								cout << "ERREUR: de numero.\n";		
						}
						cout << "Je désire ";
						CoCiX->affiche_desire();
						cout << ".\t - Actuellement ";
						CoCiX->affiche_action();
						cout << ".\n";
						if(sauvegarde)
							CoCiX->sauvegarde(verbal);
				} else {
						cout << "Aucune CoCix chargée ... (load)\n";
				}

			} else if((strcmp(commande,"creerToto")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
						delete CoCiX;

					cout << "Création du CoCiX Toto :";
					CoCiX = new Cocix();
					CoCiX->creation_Toto( 1 , verbal);
					delete CoCiX;
					cout << " Création du CoCiX Titi : ";
					CoCiX = new Cocix();
					CoCiX->creation_Titi( 2 , verbal);
					cout << "Fin\n";
					delete CoCiX;
					strcpy(nomCocix,"Aucun CoCiX");
					strcpy(prompt,"<");
					strcat(prompt, nomCocix);
					strcat(prompt, (sauvegarde)?" [Sav]":" [noSav]");
					strcat(prompt, (verbal)?"[verbal]>":"[muet]>");

			} else {
				cout << commande << " Non compris !\n";
			}

		} while(!sortie);
		cout << "Au revoir !\n";
		delete CoCiX;
		return 0;
	}


}
