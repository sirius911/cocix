/* Fichiers fonctions du monde
*/
#include <iostream>
#include <iomanip>
#include <map>
#include "constantes.h"

#include "monde.h"
#include "io.h"

using namespace std;

float temperature(const short num_case){

	struct ligneCase caseMonde;
	caseMonde = lirecase(num_case);
	return caseMonde.temperature;
}

float nourriture(const short num_case){
	struct ligneCase caseMonde;
	caseMonde = lirecase(num_case);
	return caseMonde.nourriture;
}

float humidite(const short num_case){
	struct ligneCase caseMonde;
	caseMonde = lirecase(num_case);
	return caseMonde.humidite;
}

float radioactivite(const short num_case){
	struct ligneCase caseMonde;
	caseMonde = lirecase(num_case);
	return caseMonde.radioactivite;
}
void affiche_case(short num_case, bool info){
	struct ligneCase caseMonde;
	struct struct_xy xy;
	
	caseMonde = lirecase(num_case);
	
	xy = case_to_xy(num_case);

	cout << "Case # " << num_case << " (" << xy.x << "," << xy.y <<") ";
	if(info){
		cout << caseMonde.nourriture << " Ca -- " << caseMonde.humidite << " uL -- " << caseMonde.temperature << " °C -- " << 
		caseMonde.radioactivite << " Rad ";
		cout << " -- " << nbCocix(num_case) << " CoCiX";
	}
	cout << "\n";
}

float prend_element(const short num_case, float quantite, int type){
	// fonction renvoyant la quantité prise réelle et mettant à jour la base monde
	struct ligneCase _case;
	float ancienne_quantite, nouvelle_quantite;
	if(num_case > 0 && num_case <= 10000) {
			_case = lirecase(num_case);

			switch(type){
				case EAU:
					ancienne_quantite = _case.humidite;
					break;
				case NOURRITURE:
					ancienne_quantite = _case.nourriture;
					break;
				default:
					cout << "ERREUR le type dans prend_element() de monde.cpp est mauvais : " << type << "!\n";
					exit(-1);
					break;
			}
			
			nouvelle_quantite = ancienne_quantite - quantite;
			
			if(nouvelle_quantite < 0) nouvelle_quantite = 0;

			switch(type){
				case EAU:
					_case.humidite = nouvelle_quantite;
					break;
				case NOURRITURE:
					_case.nourriture = nouvelle_quantite;
					break;
				default:
					cout << "ERREUR le type dans prend_element() de monde.cpp est mauvais : " << type << "!\n";
					exit(-1);
					break;
			}
			
			// Sauvegarde
			
			ecrireligne(num_case , &_case);
			if((ancienne_quantite - quantite) > 0) {
				// il reste de la nourriture on a donc pris la quantité demandée
				return(quantite);
			} else {
				// il n'y avait pas assez de nourriture et on a pris ce qu'il y avait
				return(ancienne_quantite);
			}
 	}
	return 0;
}


struct_xy case_to_xy(const short num_case) {
	// transforme un numero de case en structure (x,y)
	struct struct_xy xy;
	xy.x = 0;
	xy.y = 0;

	if(num_case > 0 && num_case <= 10000) {
	
	
		xy.x = num_case % 100;
	
		if(xy.x == 0) xy.x = 100;
	
		xy.y = ((num_case - xy.x)/100) +1;
		
	} else 	cout << "Erreur dans case_to_xy() num_case = " << num_case << "\n";


	return xy;

}

short xy_to_case(const short x,const short y){
	return(((y-1)*100)+x);	
}

short xy_to_case(const struct_xy xy){
	return(((xy.y-1)*100)+xy.x);
}

short valide_case( const short numCase ){
	if(numCase <= 0 ) return(numCase+10000);
	if(numCase > 10000) return(numCase-10000);
	return numCase;
}

bool libre(short numCase) {
	int nombreCocix;
	if(numCase > 0 && numCase <= 10000){

		// on compte combien il y a de CoCiX sur numCase
		nombreCocix = nbCocix(numCase);
		return (nombreCocix < MAX_PAR_CASE);
	
	} else {
	
		return(false);
	
	}
}

int nbCocix( const short num_Case){
	//renvoi le nombre de Cocix sur num_Case
	struct ligneCase caseMonde;
	//cout << " J'envoi lirecase("<<num_Case<<")\n";
	caseMonde = lirecase(num_Case);
	//cout << " J'ai reçu caseMonde ";
	int i = 0,total = 0;
	do
	{
		if(caseMonde.cocix[i] > 0)
				total++;
	} while(++i < MAX_PAR_CASE);
	return total;
}

void efface_trace(const short num_case, const int id , const bool verbal)
{
	struct ligneCase caseMonde;
	caseMonde = lirecase(num_case);
	bool trouve = false;

	if(verbal) cout << "Effacement trace sur " << num_case;
	if(id == 0) 
		cout << " -> ";
	else
		cout << " du CoCiX N° " << id << " -> ";
	int i = 0;
	do
	{
		if(id == 0)
		{
			caseMonde.cocix[i] = 0;
			if(verbal) cout <<"x";
		}
		else
		{
			if(caseMonde.cocix[i] == id)
			{
				caseMonde.cocix[i] = 0;
				if(verbal) cout <<"x";
				trouve = true;
			}
			
		}
		
	} while( ++i < MAX_PAR_CASE);
	if( (id==0 && verbal) || (id !=0 && verbal && trouve) ) cout << "\n";
	if( id!=0 && verbal && !trouve) cout << " pas trouvé(e)!\n";
	ecrireligne(num_case, &caseMonde);
}
bool marque_trace(const short num_case, const int id, const bool verbal)
{
	struct ligneCase caseMonde;
	caseMonde= lirecase(num_case);
	int i = 0;
	i = existe(num_case, id,verbal);
	if( i >=0 )
	{
		if(verbal) cout << "Déjà sur la case en position " << i << " !\n";
		return true;
	}
	i = 0;
	
	do
	{
		if(caseMonde.cocix[i] == 0)
		{
			caseMonde.cocix[i] = id;
			ecrireligne(num_case, & caseMonde);
			if(verbal) cout << "Je marque le CoCiX en position " << i+1 << "\n";
			return true;
		}
	} while( ++i < MAX_PAR_CASE);
	cout << "Il n'y a plus de place !\n";
	return false;
}

int existe(const short num_case, const int id, const bool verbal)
{
	struct ligneCase caseMonde;
	caseMonde= lirecase(num_case);
	int i = 0;
	if(verbal) cout << "Je cherche CoCiX N° " << id << " sur la case " << num_case << " => ";
	do
	{
		if(caseMonde.cocix[i] == id)
		{
			if(verbal) cout << "Trouvé en position : " << i+1 << "\n";
			return i;
		} 
	}while(++i < MAX_PAR_CASE);
	if(verbal) cout << "NON Trouvé(e) !\n";
	return(-1);
}

/***********************************************************************************************************************
                                                                            
			#####  ###### #####  #        ##    ####  ###### #    # ###### #    # ##### 
			#    # #      #    # #       #  #  #    # #      ##  ## #      ##   #   #   
			#    # #####  #    # #      #    # #      #####  # ## # #####  # #  #   #   
			#    # #      #####  #      ###### #      #      #    # #      #  # #   #   
			#    # #      #      #      #    # #    # #      #    # #      #   ##   #   
			#####  ###### #      ###### #    #  ####  ###### #    # ###### #    #   #   					*/

bool bouge(const int numCocix, const short depart, const short arrivee, const bool verbal ){
	struct ligneCase caseDepart,caseArrivee;
	
	if(depart == arrivee)
	{
		return true;
	}
	if(depart > 0 && depart <= MAX_CASE && arrivee > 0 && arrivee <= MAX_CASE)
	{
		caseDepart = lirecase(depart);
		caseArrivee = lirecase(arrivee);

		// je recherche la présence de numCocix parmis caseDepart.cocix[] et l'efface
		
		if( existe( depart , numCocix , verbal) >= 0)
		{
			efface_trace(depart , numCocix, verbal);
		}
		else
		{
			if(verbal) cout << "ATTENTION, je n'ai pas trouvé le CoCiX n°" << numCocix << " sur la case N°" << depart << " !\n";
		}
		
		// j'inscrit la présence du CoCiX sur la caseDepart.cocix[].
		return marque_trace(arrivee,numCocix,verbal);
	}
	else
	{
		cout << "ERREUR Dans les numéros de cases : bouge("<<numCocix<<","<<depart<<","<<arrivee<<")\n";
		return false; 
	}
}

short monte( short numCase ){
	numCase -= 100;
	return ( valide_case( numCase ) );
}

short descend( short numCase ){
	numCase += 100;
	return ( valide_case( numCase ) );
}

short gauche( short numCase ){
	numCase--;
	return ( valide_case( numCase ) );
}
         
short droite( short numCase ){
	numCase++;
	return ( valide_case( numCase ) );
}

short monte_gauche( short numCase ){
	short etape = monte( numCase );
	etape = gauche( etape );
	return ( valide_case( etape ) );
}

short monte_droite( short numCase ){
	short etape = monte( numCase );
	etape = droite( etape );
	return ( valide_case( etape) );
}

short descend_gauche( short numCase ){
	short etape = descend( numCase );
	etape = gauche( etape) ;
	return ( valide_case( etape ) );
}
short descend_droite( short numCase ){
	short etape = descend( numCase );
	etape = droite( etape );
	return ( valide_case( etape ) );
}

/*
					######  ####  #    #  ####  ##### #  ####  #    #  ####  
					#      #    # ##   # #    #   #   # #    # ##   # #      
					#####  #    # # #  # #        #   # #    # # #  #  ####  
					#      #    # #  # # #        #   # #    # #  # #      # 
					#      #    # #   ## #    #   #   # #    # #   ## #    # 
					#       ####  #    #  ####    #   #  ####  #    #  ####  
					                                                         
                                                   
						#####  # #    # ###### #####   ####  ######  ####  
						#    # # #    # #      #    # #      #      #      
						#    # # #    # #####  #    #  ####  #####   ####  
						#    # # #    # #      #####       # #           # 
						#    # #  #  #  #      #   #  #    # #      #    # 
						#####  #   ##   ###### #    #  ####  ######  ####  

*/

void affiche_map(const multimap< float, short, greater<float> > &m )
{
	multimap<float, short, greater<float> >::const_iterator im;
	for (im=m.begin() ; im!=m.end(); im++)
	{
		cout << "il y a " << (*im).first << " uml sur ";
		affiche_case((*im).second, false);
		cout << "\n";
	}


}

short meilleur_case(short case_centrale, int info, bool doit_etre_libre, bool verbal){
	/* Fonction renvoyant le num case de la meilleur info (float)
		EAU NOURRITURE ETC
		libre indique si il peut y doit y avoir une place libre
	*/
	short case_haut_gauche,case_haut,case_haut_droite,case_droite,case_gauche,case_bas_droite,case_bas,case_bas_gauche;
	
	multimap<float, short, greater<float> > zoneRecherche;	// Map des zones recherche trouvée
	bool trouve = false;
	short case_trouvee;
	float (* adr_fonction)(short);		// pointeur sur la fonction qui recherchera
		
		// case de recherche
	case_haut_gauche = monte_gauche(case_centrale);
	case_haut = monte(case_centrale);
	case_haut_droite = monte_droite(case_centrale);
	case_droite = droite(case_centrale);
	case_gauche = gauche(case_centrale);
	case_bas_droite = descend_droite(case_centrale);
	case_bas = descend(case_centrale);
	case_bas_gauche = descend_gauche(case_centrale);

	switch(info){
		case EAU:
			// on recherche par la fonction humidite()
			adr_fonction = humidite;
			break;
		case NOURRITURE:
			// on recherche par la fonction nourriture();
			adr_fonction = nourriture;
			break;
		default:
			cout << "ERREUR dans Monde.cpp -> je n'ai pas l'info de recherche : " << info << "\n";
			return 0;
	}
	// on execute la recherche

	if(doit_etre_libre){
		// les places doivent être libres
		if((*adr_fonction)(case_haut_gauche) > 0 && libre(case_haut_gauche)) {

		/*		x..
				.o.
				...			*/

			if(verbal) cout << "La case en haut à gauche est libre et a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_haut_gauche), case_haut_gauche));
			trouve = true;

		}
		if((*adr_fonction)(case_haut) > 0 && libre(case_haut)) {

		/*		.x.
				.o.
				...			*/		

			if(verbal) cout << "La case en haut est libre et a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_haut), case_haut));
			trouve = true;

		}	
		if((*adr_fonction)(case_haut_droite) > 0 && libre(case_haut_droite)) {

		/*		..x
				.o.
				...			*/		

			if(verbal) cout << "La case en haut à droite est libre et a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_haut_droite), case_haut_droite));
			trouve = true;

		}
		if((*adr_fonction)(case_droite) > 0 && (*adr_fonction)(case_droite)) {

		/*		...
				.ox
				...			*/

			if(verbal) cout << "La case à droite est libre et a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_droite), case_droite));
			trouve = true;

		}
		if((*adr_fonction)(case_gauche) > 0 && libre(case_gauche)) {

		/*		...
				xo.
				...			*/
			if(verbal) cout << "La case à gauche  est libre et a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_gauche), case_gauche));
			trouve = true;

		} 
		if((*adr_fonction)(case_bas_droite) > 0 && libre(case_bas_droite)) {
		/*		...
				.o.
				..x			*/	

			if(verbal) cout << "La case en bas à droite est libre et a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_bas_droite), case_bas_droite));
			trouve = true;

		} 
		if((*adr_fonction)(case_bas) > 0 && libre(case_bas)){
		/*		...
				.o.
				.x.			*/		

			if(verbal) cout << "La case en bas est libre et a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_bas), case_bas));
			trouve = true;

		}
		if((*adr_fonction)(case_bas_gauche) > 0 && libre(case_bas_gauche)) {
		/*		...
				.o.
				x..			*/
			if(verbal) cout << "La case en bas à gauche est libre et a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_bas_gauche), case_bas_gauche));
			trouve = true;

		}

	} else {
		//on a pas besoins de d'avoir une place libre
		if(libre(case_haut_gauche)) {

		/*		x..
				.o.
				...			*/

			if(verbal) cout << "La case en haut à gauche a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_haut_gauche), case_haut_gauche));
			trouve = true;

		}
		if( libre(case_haut)) {

		/*		.x.
				.o.
				...			*/		

			if(verbal) cout << "La case en haut a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_haut), case_haut));
			trouve = true;

		}	
		if(libre(case_haut_droite)) {

		/*		..x
				.o.
				...			*/		

			if(verbal) cout << "La case en haut à droite  a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_haut_droite), case_haut_droite));
			trouve = true;

		}
		if(libre(case_droite)) {

		/*		...
				.ox
				...			*/

			if(verbal) cout << "La case à droite est libre et a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_droite), case_droite));
			trouve = true;

		}
		if( libre(case_gauche)) {

		/*		...
				xo.
				...			*/
			if(verbal) cout << "La case à gauche a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_gauche), case_gauche));
			trouve = true;

		} 
		if(libre(case_bas_droite)) {
		/*		...
				.o.
				..x			*/	

			if(verbal) cout << "La case en bas à droite a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_bas_droite), case_bas_droite));
			trouve = true;

		} 
		if(libre(case_bas)){
		/*		...
				.o.
				.x.			*/		

			if(verbal) cout << "La case en bas  a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_bas), case_bas));
			trouve = true;

		}
		if( libre(case_bas_gauche)) {
		/*		...
				.o.
				x..			*/
			if(verbal) cout << "La case en bas à gauche  a l'information demandée...\n";
			zoneRecherche.insert(make_pair((*adr_fonction)(case_bas_gauche), case_bas_gauche));
			trouve = true;

		} 

	}

	if(trouve){
		if(verbal)
		{
			cout << "il y a " << zoneRecherche.size() << " case(s) possible.\n";
			affiche_map(zoneRecherche);
		} 
		multimap<float, short, greater<float> >::const_iterator im;
		im = zoneRecherche.begin();
		case_trouvee = (*im).second;
		return case_trouvee;

	} else {
			if(verbal) cout << "Il n'y a pas l'information demandée autour de moi !\n";
		return 0;
	}

}

void affiche_grille(short numCase){
	short case1,case2,case3,case4,case5,case6,case7,case8,case9,case10,case11,case12,case13,case14,
	case15,case16,case17,case18,case19,case20,case21,case22,case23,case24,case25;
	
	case1 = monte_gauche(monte_gauche(numCase));
	case2 = monte_gauche(monte(numCase));
	case3 = monte(monte(numCase));
	case4 = monte_droite(monte(numCase));
	case5 = monte_droite(monte_droite(numCase));
	case6 = monte_gauche(gauche(numCase));
	case7 = monte_gauche(numCase);
	case8 = monte(numCase);
	case9 = monte_droite(numCase);
	case10 = monte_droite(droite(numCase));
	case11 = gauche(gauche(numCase));
	case12 = gauche(numCase);
	case13 = numCase;
	case14 = droite(numCase);
	case15 = droite(droite(numCase));
	case16 = descend_gauche(gauche(numCase));
	case17 = descend_gauche(numCase);
	case18 = descend(numCase);
	case19 = descend_droite(numCase);
	case20 = descend_droite(droite(numCase));
	case21 = descend_gauche(descend_gauche(numCase));
	case22 = descend_gauche(descend(numCase));
	case23 = descend(descend(numCase));
	case24 = descend_droite(descend(numCase));
	case25 = descend_droite(descend_droite(numCase));

	cout << fixed;
	cout << "_________________________________________________________________________________\n";
	cout << "|n : "<<setw(3)<<setprecision(0)<<nourriture(case1)<<"  "<<setw(5)<<case1<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case2)<<"  "<<setw(5)<<case2<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case3)<<"  "<<setw(5)<<case3<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case4)<<"  "<<setw(5)<<case4<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case5)<<"  "<<setw(5)<<case5<<" |\n";
	cout << "|h : "<<setw(3)<<setprecision(0)<<humidite(case1)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case2)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case3)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case4)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case5)<<"        |\n";
	cout << "|t : "<<setw(2)<<setprecision(0)<<temperature(case1)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case2)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case3)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case4)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case5)<<"°C       |\n";
	cout << "|r : "<<setw(3)<<setprecision(0)<<radioactivite(case1)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case2)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case3)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case4)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case5)<<"        |\n";
	cout << "|  "<<nbCocixGraph(case1)<<"   |  "<<nbCocixGraph(case2)<<"   |  "<<nbCocixGraph(case3)<<"   |  "<<nbCocixGraph(case4)<<"   |  "<<nbCocixGraph(case5)<<"   |\n";
	cout << "|---------------|---------------|---------------|---------------|---------------|\n";
	cout << "|n : "<<setw(3)<<setprecision(0)<<nourriture(case6)<<"  "<<setw(5)<<case6<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case7)<<"  "<<setw(5)<<case7<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case8)<<"  "<<setw(5)<<case8<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case9)<<"  "<<setw(5)<<case9<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case10)<<"  "<<setw(5)<<case10<<" |\n";
	cout << "|h : "<<setw(3)<<setprecision(0)<<humidite(case6)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case7)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case8)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case9)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case10)<<"        |\n";
	cout << "|t : "<<setw(2)<<setprecision(0)<<temperature(case6)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case7)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case8)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case9)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case10)<<"°C       |\n";
	cout << "|r : "<<setw(3)<<setprecision(0)<<radioactivite(case6)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case7)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case8)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case9)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case10)<<"        |\n";
	cout << "|  "<<nbCocixGraph(case6)<<"   |  "<<nbCocixGraph(case7)<<"   |  "<<nbCocixGraph(case8)<<"   |  "<<nbCocixGraph(case9)<<"   |  "<<nbCocixGraph(case10)<<"   |\n";
	cout << "|---------------|---------------|---------------|---------------|---------------|\n";
	cout << "|n : "<<setw(3)<<setprecision(0)<<nourriture(case11)<<"  "<<setw(5)<<case11<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case12)<<"  "<<setw(5)<<case12<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case13)<<"  "<<setw(5)<<case13<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case14)<<"  "<<setw(5)<<case14<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case15)<<"  "<<setw(5)<<case15<<" |\n";
	cout << "|h : "<<setw(3)<<setprecision(0)<<humidite(case11)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case12)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case13)<<"     \u263A  |h : "<<setw(3)<<setprecision(0)<<humidite(case14)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case15)<<"        |\n";
	cout << "|t : "<<setw(2)<<setprecision(0)<<temperature(case11)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case12)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case13)<<"°C   XXX |t : "<<setw(2)<<setprecision(0)<<temperature(case14)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case15)<<"°C       |\n";
	cout << "|r : "<<setw(3)<<setprecision(0)<<radioactivite(case11)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case12)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case13)<<"   /   \\|r : "<<setw(3)<<setprecision(0)<<radioactivite(case14)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case15)<<"        |\n";
	cout << "|  "<<nbCocixGraph(case11)<<"   |  "<<nbCocixGraph(case12)<<"   |  "<<nbCocixGraph(case13)<<"   |  "<<nbCocixGraph(case14)<<"   |  "<<nbCocixGraph(case15)<<"   |\n";
	cout << "|---------------|---------------|---------------|---------------|---------------|\n";
	cout << "|n : "<<setw(3)<<setprecision(0)<<nourriture(case16)<<"  "<<setw(5)<<case16<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case17)<<"  "<<setw(5)<<case17<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case18)<<"  "<<setw(5)<<case18<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case19)<<"  "<<setw(5)<<case19<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case20)<<"  "<<setw(5)<<case20<<" |\n";
	cout << "|h : "<<setw(3)<<setprecision(0)<<humidite(case16)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case17)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case18)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case19)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case20)<<"        |\n";
	cout << "|t : "<<setw(2)<<setprecision(0)<<temperature(case16)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case17)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case18)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case19)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case20)<<"°C       |\n";
	cout << "|r : "<<setw(3)<<setprecision(0)<<radioactivite(case16)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case17)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case18)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case19)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case20)<<"        |\n";
	cout << "|  "<<nbCocixGraph(case16)<<"   |  "<<nbCocixGraph(case17)<<"   |  "<<nbCocixGraph(case18)<<"   |  "<<nbCocixGraph(case19)<<"   |  "<<nbCocixGraph(case20)<<"   |\n";
	cout << "|---------------|---------------|---------------|---------------|---------------|\n";
	cout << "|n : "<<setw(3)<<setprecision(0)<<nourriture(case21)<<"  "<<setw(5)<<case21<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case22)<<"  "<<setw(5)<<case22<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case23)<<"  "<<setw(5)<<case23<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case24)<<"  "<<setw(5)<<case24<<" |n : "<<setw(3)<<setprecision(0)<<nourriture(case25)<<"  "<<setw(5)<<case25<<" |\n";
	cout << "|h : "<<setw(3)<<setprecision(0)<<humidite(case21)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case22)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case23)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case24)<<"        |h : "<<setw(3)<<setprecision(0)<<humidite(case25)<<"        |\n";
	cout << "|t : "<<setw(2)<<setprecision(0)<<temperature(case21)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case22)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case23)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case24)<<"°C       |t : "<<setw(2)<<setprecision(0)<<temperature(case25)<<"°C       |\n";
	cout << "|r : "<<setw(3)<<setprecision(0)<<radioactivite(case21)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case22)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case23)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case24)<<"        |r : "<<setw(3)<<setprecision(0)<<radioactivite(case25)<<"        |\n";
	cout << "|  "<<nbCocixGraph(case21)<<"   |  "<<nbCocixGraph(case22)<<"   |  "<<nbCocixGraph(case23)<<"   |  "<<nbCocixGraph(case24)<<"   |  "<<nbCocixGraph(case25)<<"   |\n";
	cout << "|---------------|---------------|---------------|---------------|---------------|\n";
}

struct_xy operator -( struct_xy &a ,  struct_xy &b)
{
		struct_xy result;
		result.x = (a.x - b.x);
		result.y = (a.y - b.y);
		return (result);
}

struct_xy operator +( struct_xy &a ,  struct_xy &b)
{
		struct_xy result;
		result.x = (a.x + b.x);
		result.y = (a.y + b.y);
		return (result);
}

short aller(const short depart, const short arrivee, const bool verbal)
{	// renvoi la case intermédière pour bouger départ à arrivée danz un monde fermé
	short case_aller = 0;
	struct_xy aller;
	struct_xy Dep = case_to_xy(depart);
	struct_xy Arr = case_to_xy(arrivee);
	if(verbal)
	{
		cout << "Je dois aller de ";
		affiche_case(depart, false);
		cout << " à ";
		affiche_case(arrivee, false);
		cout << "\n";
	}
	if(depart == arrivee)
	{
		cout << "J'y suis !\n";
		return arrivee;
	}

	struct_xy Delta = Arr - Dep;

	//cout << "\t Deltat = (" << Delta.x<<","<<Delta.y<<") -Control Monde fermé => ";

	if( Delta.x >= -50 && Delta.x <= 50 && Delta.x !=0)
	{
		Delta.x = (Delta.x / abs(Delta.x)); // on ne change pas de signe de delta
	}
	else if(Delta.x !=0)
	{
		Delta.x = (Delta.x / abs(Delta.x)) * -1;	// on change le signe de delta
	} else {
		Delta.x = 0;
	}

	if( Delta.y >= -50 && Delta.y <= 50 && Delta.y !=0)
	{
		Delta.y = (Delta.y / abs(Delta.y)); // on ne change pas de signe de delta
	}
	else if(Delta.y != 0)
	{
		Delta.y = (Delta.y / abs(Delta.y)) * -1; // on change le signe de delta
	} else {
		Delta.y = 0;
	}
	//cout << "\tDeltat = (" << Delta.x<<","<<Delta.y<<")\n";

	aller = Dep + Delta;

	if(verbal) cout << "\t\tCase interm : ("<< aller.x << ","<<aller.y<<") => case n° ";

	case_aller =valide_case( xy_to_case(aller));

	if(verbal) cout << case_aller << "\n";
	return case_aller;
}

const char* nbCocixGraph(const short numCase){			   
	const char *chaine[11] = {"          ","     *    ","    **    ","   ***    ","   ****   ","  *****   ","  ******  "," *******  "," ******** "," *********","**********"};
	int nombreCocix = nbCocix( numCase );
	
	return ( chaine[ nombreCocix ] );
}

