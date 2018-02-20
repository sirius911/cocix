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
#include "include/class/Actions/Recolter.h"
#include "include/class/Actions/Cherche_Recolte.h"
#include "include/class/Actions/Deposer.h"
#include "include/class/Actions/Se_Reproduire.h"
#include "include/class/Actions/Cherche_Partenaire.h"
#include "include/class/Actions/Cherche_Case_Libre.h"
#include "include/class/Actions/Pondre.h"
#include "include/class/Actions/Soigner.h"
#include "include/class/Actions/Cherche_Malade.h"

#include "include/constantes.h"
#include "include/io.h"
#include "include/monde.h"

using namespace std;

void consanguinite_case(short i)
{

}

int main(int nbArg, char* argv[])
{
	JourNuit Jour_Nuit;
	srand(time(NULL));

	char commande[20] = "";
	char choix[] = "";
	Cocix *CoCiX = NULL;
	//Cocix *CoCiX = new Cocix("1.cox",true);
	int i;
	bool sortie = false;
	bool verbal = true;
	bool sauvegarde = false;
	char prompt[31] = "<[noSav][verbal] Aucun CoCiX >";
	char nomCocix[15] = "Aucun CoCiX";
	char nomFichier[30];

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

	cout << "Action spéciale : ";
	CoCiX = new Cocix(2,false,true);
	CoCiX->set_id_oeuf(7);
	CoCiX->balises.fecondee = true;
	CoCiX->sauvegarde(true);

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
				vector<char*> listeFichiers = affiche_nid(true, 2);
				cout << "Entrez le Num du CoCiX : ";
				cin >> choix;
				int i = atoi(choix);
				if(i > 0 && i <= (int) listeFichiers.size())
				{
					if( ! (CoCiX == (void*) NULL ))
						delete CoCiX;

					strcpy(nomFichier,listeFichiers[i-1]);
					CoCiX = new Cocix(nomFichier,verbal);

					if(CoCiX->get_id() > 0 )
					{ 
						strcpy(nomCocix,CoCiX->nom);
						CoCiX->affiche(false);
						strcpy(prompt,"<");
						strcat(prompt, (sauvegarde)?" [Sav]":" [noSav]");
						strcat(prompt, (verbal)?"[verbal] ":"[muet] ");
						strcat(prompt, nomCocix);
						strcat(prompt, ">");
					}
					else
					{
						cout << "CoCiX non trouvé !\n";
						strcpy(nomCocix,"Aucun CoCiX");
						strcpy(prompt,"<");
						strcat(prompt, (sauvegarde)?" [Sav]":" [noSav]");
						strcat(prompt, (verbal)?"[verbal] ":"[muet] ");
						strcat(prompt, nomCocix);
						strcat(prompt, ">");
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
						CoCiX->deplace( aller (CoCiX->get_case_presence(),i,verbal),verbal);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
				
			} else if((strcmp(commande,"parents") == 0))
			{
					if( !(CoCiX == (void*) NULL ))
					{	
						cout << "Père : " << CoCiX->get_idPere() << "\n";
						cout << "Mère : " << CoCiX->get_idMere() << "\n";
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			}
			else if((strcmp(commande,"setAncetre")==0))
			{
					if( !(CoCiX == (void*) NULL ))
					{	
						int i = 0;
						int val;
						do
						{
							cout << "Ancetre N° " << i << " : ";
							cin >> val;
							CoCiX->set_ancetre(i,val);
						} while (++i < 30);
						CoCiX->ancetre();
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			} else if((strcmp(commande,"ancetre")==0))
			{
					if( !(CoCiX == (void*) NULL ))
					{	
						CoCiX->ancetre();
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
					cout << "\tancetre\t\tAffiche les ancetres du CoCiX\n";
					cout << "\tconsanguinite\t\tDonne la consanguinité des CoCix d'une case.\n";
					cout << "\tcortex\t\tAffiche le cortex actuel du CoCiX\n";
					cout << "\tcortexEtat\t\tLance la méthode cortex_etat() du CoCiX chargé.\n";
					cout << "\tcortexAction\t\tLance la méthode cortex_action() du CoCiX chargé.\n";
					cout << "\tcouveuse\t\tAffiche les oeufs.\n";
					cout << "\tdeplace\t\tDéplace le CoCiX sur une case.\n";
					cout << "\tdesire\t\tAffiche le désire en cours du CoCiX chargé.\n";
					cout << "\teau\t\tAffiche la quantité d'eau sur une case.\n";
					cout << "\teffacePresence\t\tEfface les présences sur une case.\n";
					cout << "\tforceAction\t\tForce une action pour le CoCiX chargé.\n";
					cout << "\tforceDesire\t\tForce un Désire pour le CoCiX chargé.\n";
					cout << "\tgenetique\t\tAffiche le genome du CoCiX chargé.\n";
					
					cout << "\tgrille\t\tAffiche les 25 cases (5x5) autour du CoCiX.\n";
					cout << "\tmarquePresence\t\tMarque la présence du Cocix sur sa case dans Monde\n";
					cout << "\tmeurt\t\tFait mourrir le CoCiX\n";
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

			}else if((strcmp(commande,"cortex")==0))
			{
					if(CoCiX)
					{
						cout << "Le cortex est : " << CoCiX->get_nom_cortex() << "\n";
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			}
			else if((strcmp(commande,"marquePresence")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						CoCiX->marque_presence(verbal);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}

			} else if((strcmp(commande,"nid")==0))
			{
					affiche_nid(false, 0);

			} else if((strcmp(commande,"consanguinite")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						// on charge une CoCiX
						vector<char*> listeFichiers = affiche_nid(false, 2);
						cout << "Entrez le Num d'un CoCiX : ";
						cin >> choix;
						int i = atoi(choix);
						if(i > 0 && i <= (int) listeFichiers.size())
						{
							CoCiX->consanguinite( i , true);
						}
						else
						{
							cout << "Mauvais numéro !\n";
						}
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			}
			else if((strcmp(commande,"couveuse")==0))
			{
					affiche_nid(false, 1);
			}
			else if((strcmp(commande,"balises")==0))
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
			}  else if((strcmp(commande,"cortexEtat")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
					{
						CoCiX->cortex_Etat(verbal);
						if(sauvegarde)
							CoCiX->sauvegarde(verbal);
					} else {
						cout << "Aucune CoCix chargée ... (load)\n";
					}
			} else if((strcmp(commande,"cortexAction")==0))
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
						affiche_grille(CoCiX->get_case_presence());
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
						affiche_case(CoCiX->get_case_presence(),verbal);
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
						cout << "Il y a "<< humidite(CoCiX->get_case_presence()) << "uml sur " <<CoCiX->get_case_presence()<<"\n";
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
						cout << "Il y a "<< nourriture(CoCiX->get_case_presence()) << "cal sur " <<CoCiX->get_case_presence()<<"\n";
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
						cout << "Il y a " << nbCocix(CoCiX->get_case_presence()) << " CoCiX\n";
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
			} else if ((strcmp(commande,"temperature")==0))
			{
					if( ! (CoCiX == (void*) NULL )){
						cout << "Valeur température : ";
						float entree;
						cin >> entree;
						CoCiX->Temperature.set_valeur(entree,&CoCiX->balises,false);
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

			} else if((strcmp(commande,"meurt")==0))
			{
				if( ! (CoCiX == (void*) NULL )){

						CoCiX->meurt(verbal);
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
						cout << "Boire()\t ->\t " << Actions::BOIRE << "\n";
						cout << "Cherche_Case_Libre()\t ->\t " << Actions::CHERCHE_CASE_LIBRE << "\n";
						cout << "Cherche_Eau()\t ->\t " << Actions::CHERCHE_EAU << "\n";
						cout << "Cherche_Malade()\t ->\t " << Actions::CHERCHE_MALADE << "\n";
						cout << "Cherche_Nourriture()\t ->\t " << Actions::CHERCHE_NOURRITURE << "\n";
						cout << "Cherche_Partenaire()\t ->\t " << Actions::CHERCHE_PARTENAIRE << "\n";
						cout << "Cherche_Recolte()\t ->\t " << Actions::CHERCHE_RECOLTE << "\n" ;
						cout << "Deposer()\t ->\t " << Actions::DEPOSER << "\n";
						cout << "Dormir()\t ->\t " << Actions::DORMIR << "\n";
						cout << "Manger()\t ->\t " << Actions::MANGER << "\n";
						cout << "Pondre()\t ->\t " << Actions::PONDRE << "\n";
						cout << "Recolter()\t ->\t " << Actions::RECOLTER << "\n";
						cout << "Rentrer()\t ->\t " << Actions::RENTRER << "\n";
						cout << "Se_Reproduire()\t ->\t " << Actions::SE_REPRODUIRE << "\n";
						cout << "Se_Soigner()\t ->\t " << Actions::SE_SOIGNER << "\n";
						cout << "Soigner()\t ->\t " << Actions::SOIGNER << "\n";
						cout << "\t votre choix : ";
						cin >> choix;
						i = atoi(choix);
						switch(i){
							case Actions::DORMIR:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Dormir();
								else
									CoCiX->Desire = new Dormir();
								break;
							case Actions::Actions::MANGER:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Manger();
								else
									CoCiX->Desire = new Manger();
								break;
							case Actions::BOIRE:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Boire();
								else
									CoCiX->Desire = new Boire();
								break;
							case Actions::CHERCHE_EAU:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Cherche_Eau();
								else
									CoCiX->Desire = new Cherche_Eau();
								break;
							case Actions::CHERCHE_NOURRITURE:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Cherche_Nourriture();
								else
									CoCiX->Desire = new Cherche_Nourriture();
								break;
							case Actions::RENTRER:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Rentrer();
								else
									CoCiX->Desire = new Rentrer();
								break;
							case Actions::SE_SOIGNER:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Se_Soigner();
								else
									CoCiX->Desire = new Se_Soigner();
								break;
							case Actions::RECOLTER:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Recolter();
								else
									CoCiX->Desire = new Recolter();
								break;
							case Actions::CHERCHE_RECOLTE:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Cherche_Recolte();
								else
									CoCiX->Desire = new Cherche_Recolte();
								break;
							case Actions::DEPOSER:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Deposer();
								else
									CoCiX->Desire = new Deposer();
								break;
							case Actions::SE_REPRODUIRE:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Se_Reproduire();
								else
									CoCiX->Desire = new Se_Reproduire();
								break;
							case Actions::CHERCHE_PARTENAIRE:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Cherche_Partenaire();
								else
									CoCiX->Desire = new Cherche_Partenaire();
								break;
							case Actions::PONDRE:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Pondre();
								else
									CoCiX->Desire = new Pondre();
								break;
							case Actions::CHERCHE_CASE_LIBRE:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Cherche_Case_Libre();
								else
									CoCiX->Desire = new Cherche_Case_Libre();
								break;
							case Actions::SOIGNER:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Soigner();
								else
									CoCiX->Desire = new Soigner();
								break;
							case Actions::CHERCHE_MALADE:
								if((strcmp(commande,"forceAction")==0))
									CoCiX->Action = new Cherche_Malade();
								else
									CoCiX->Desire = new Cherche_Malade();
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
					cout << "Fin\n";
					delete CoCiX;
					strcpy(nomCocix,"Aucun CoCiX");
					strcpy(prompt,"<");
					strcat(prompt, nomCocix);
					strcat(prompt, (sauvegarde)?" [Sav]":" [noSav]");
					strcat(prompt, (verbal)?"[verbal]>":"[muet]>");

			}else if((strcmp(commande,"creerTiti")==0))
			{
					if( ! (CoCiX == (void*) NULL ))
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
		if( ! (CoCiX == (void*) NULL ))
			delete CoCiX;
		return 0;
	}


}
