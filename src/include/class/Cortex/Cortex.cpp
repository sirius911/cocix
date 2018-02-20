#include "Cortex.h"
#include "../../constantes.h"
#include "../Cocix.h"
#include "../JourNuit.h"
#include <math.h>
#include <iomanip>
#include "../Actions/Actions.h"
//#include "../Actions/Agresser.h"
#include "../Actions/Boire.h"
#include "../Actions/Cherche_Eau.h"
#include "../Actions/Deposer.h"
#include "../Actions/Dormir.h"
#include "../Actions/Manger.h"
#include "../Actions/Pondre.h"
#include "../Actions/Recolter.h"
#include "../Actions/Cherche_Recolte.h"
#include "../Actions/Rentrer.h"
#include "../Actions/Se_Reproduire.h"
#include "../Actions/Se_Soigner.h"
#include "../Actions/Cherche_Partenaire.h"
#include "../Actions/Cherche_Case_Libre.h"
#include "../Actions/Soigner.h"
#include "../Actions/Cherche_Malade.h"



using std::cout;

Cortex::Cortex()
{

}

void Cortex::gestion_Etat(Cocix *cocix , const bool verbal)
{

	// gestion de base
	cout << "\n****     C O R T E X   E T A T     ****\n";
	cout <<  "              G E N E R A L\n";
	cocix->prend_temperature(verbal);
	cocix->raz_balises(verbal);
	if(verbal) cout << "Température ("<< cocix->get_temp_exterieur() << " °C): \n";

		/*
		¯|¯ |¯ |\/| |¯| |¯ |¯| /¯\ ¯|¯ | | |¯| |¯ 
 		 |  |¯ |  | |¯  |¯ |¯\ |¯|  |  |_| |¯\ |¯ 
      	 	 ¯           ¯                      ¯ 
		
				Echange avec l'extérieur
		*/
	
	float correction;	
	cout << "temp...";

	if(cocix->get_temp_exterieur() > cocix->Temperature.get_valeur() ){
			// si la température exterieur ext supérieur au augmente la température interne de Genes['temp']->valeur
			if(verbal) cout << " Temp ext > Temp corporel => \n"; 
			cocix->Temperature.modif(cocix->genome[Gene::TEMP].valeur, &cocix->balises,verbal);
	}
	else
	{
			// sinon rien ne change
			if(verbal) cout << " Temp ext <= temp corporel -> aucune modif\n";
	}


	// verification de la température extérieur < à 10°C
	if(cocix->get_temp_exterieur() < 10.0f) {
			
		if(verbal) cout << " Temp ext < 10°C<\n";
		cocix->Temperature.modif(-cocix->genome[Gene::TEMP].valeur, &cocix->balises,verbal); // on diminue la température de Genes.temp.valeur
			
	}


	//variation de température en fonction de l'action
	// la température ne descend pas en dessous de 36.5 quand elle Mange Dort ou BOIT

	// si je dort ou si je mange ou si bois et que ma température est inf à 36.5°C mon action ne bouge pas ma température
	if(cocix->Action->get_chaleur() <= 0 && cocix->Temperature.get_valeur() < 36.5f)
	{
		if(verbal)
		{
			cout << cocix->Action->get_action() << " ne me fait pas perdre de température car ma température < 36,5°C\n";
		}
	}
	else
	{
		cocix->Temperature.modif(cocix->Action->get_chaleur(), &cocix->balises,verbal);
		if(verbal) cout << cocix->Action->get_action() << " -> +" << cocix->Action->get_chaleur() << "°C = " << cocix->Temperature.get_valeur() << "°C\n";

	}

	cout << "ok\n";
	cout << "Hydro...";	
		
	// Calcul du facteur de correction de température
	correction = (cocix->Temperature.get_valeur() - 37.5f) * (cocix->Temperature.get_valeur() - 37.5f) * sqrt(cocix->Temperature.get_valeur());
	
	if(verbal) cout << "Facteur de correction  de Temperature = " << correction << "%\n";
		
		/*
						|¯\ |¯ |¯| |¯ |\| |¯  |¯ |¯    | | \| |¯\ |¯| | |¯|  | | |¯ 
						|_/ |¯ |¯  |¯ | |  ¯| |¯  ¯|   |¯|  | |_/ |¯\ | |_|¬ |_| |¯ 
     						¯      ¯      ¯   ¯  ¯                               ¯ 
		*/
		// depense en eau en fonction de l'action:
    float depense_eau;
	depense_eau = cocix->Action->get_eau() + (cocix->Action->get_eau() * correction / 100);
	if(cocix->fecondee()) 
		{
			depense_eau += ( depense_eau * 0.1f ); //si fécondée 10% en plus
			if(verbal) cout << "fécondée : + 10% ";
		}
		cocix->Hydro.modif(-depense_eau, &cocix->balises,verbal);
		if(verbal) cout << cocix->Action->get_action() << " -> -" << depense_eau << " muL = " << cocix->Hydro.get_valeur() << " muL\n";
	
	cout << "ok\n";
	cout << "Cal...";
		/*
						|¯\ |¯ |¯| |¯ |\| |¯  |¯ |¯    |¯ /¯\ |  |¯| |¯| | |¯|  | | |¯ 
						|_/ |¯ |¯  |¯ | |  ¯| |¯  ¯|   |_ |¯| |_ |_| |¯\ | |_|¬ |_| |¯ 
     						¯      ¯      ¯   ¯  ¯                                  ¯ 
		*/
		// depense en Calorie en fonction de l'action:
		
	float depense_calorie;
	depense_calorie = cocix->Action->get_calorie();
	if(cocix->fecondee())
	{
		depense_calorie += (depense_calorie * 0.1f);	// si fécondée 10% en plus
		if(verbal) cout << "fécondée : + 10% ";
	} 
	cocix->Calorie.modif(-depense_calorie, &cocix->balises);
	if(verbal) cout << cocix->Action->get_action() << " -> -" << depense_calorie <<" Cal = " << cocix->Calorie.get_valeur() << "Cal\n";

	cout << "ok\n";
	cout << "SA...";
		/*
		\ | /¯\ |¯| | /¯\ ¯|¯ | |¯| |\|   |¯\ |¯   |¯  /¯\ |\| ¯|¯ |¯ 
 		 \| |¯| |¯\ | |¯|  |  | |_| | |   |_/ |¯    ¯| |¯| | |  |  |¯ 
                                              ¯    ¯               ¯ 
		*/
		// Vieux ?	
		if(cocix->etape() == Cocix::ETAT_VIEUX) {
			cocix->vieillissement(verbal);
		}

	// Souffrances des Etats
	cout << "ok\n";
	cout << "Souffrances :\nHydro...";	
		cocix->Hydro.souffrance(&cocix->Sante,  cocix->balises.coma, true, verbal);
	cout << "\nCal...";
		cocix->Calorie.souffrance(&cocix->Sante,  cocix->balises.coma, true, verbal);
	cout << "\nTemp...";
		cocix->Temperature.souffrance(&cocix->Sante,  cocix->balises.coma, true, verbal);
	cout << "\nSant...";
		cocix->Sante.souffrance(&cocix->Sante,  cocix->balises.coma, true, verbal);
	cout << "\n";

			// GESTION DU SOMMEIL
	if(cocix->Action->equal(Dormir())) {
			// La CoCix Dort
			cout << "Sommeil...";
			cocix->Sante.modif(cocix->Sante.get_valeur() * cocix->genome[Gene::RECUP_SOMMEIL].valeur, &cocix->balises,verbal);	
			if(verbal) cout << "Action = DORMIR ==> Santé + " << setprecision(3) << ( cocix->Sante.get_valeur() * cocix->genome[Gene::RECUP_SOMMEIL].valeur )<< setprecision(2) <<  "% = " << cocix->Sante.get_valeur() << "\n";
			cout << "ok\n";
	}

	/*
                                +-+-+-+-+-+-+-+
								|B|A|L|I|S|E|S|
								+-+-+-+-+-+-+-+
	*/
    cocix->maj_balises(verbal);		
}

char* Cortex::get_nom()
{
	return nom;
}

bool Cortex::decide_Desire(Cocix *cocix, const bool verbal)	// renvoi vrai si on peut continuer le choix du Désire
{
		/*
					 ####  #    #  ####  # #    #    #####  ######  ####  # #####  ######  ####  
					#    # #    # #    # #  #  #     #    # #      #      # #    # #      #      
					#      ###### #    # #   ##      #    # #####   ####  # #    # #####   ####  
					#      #    # #    # #   ##      #    # #           # # #####  #           # 
					#    # #    # #    # #  #  #     #    # #      #    # # #   #  #      #    # 
 					####  #    #  ####  # #    #    #####  ######  ####  # #    # ######  ####  
		*/
	
/*IDEE :: Si on met un paramètre à cette methode pour affiner les besoins vitaux en fonction du cortex supérieur*/


	JourNuit Jour_Nuit;
	if(verbal) cout << "Choix du Désire => ";

   	if(cocix->coma())
   	{
   		if(verbal) cout << "Comas => ";
  		cocix->Desire = new Dormir();
   		cocix->Action = new Dormir();
   		return false;
  	} 

	switch(Jour_Nuit.jour_nuit)
	{
		case JourNuit::NUIT:
			if(verbal) cout << "Il fait nuit donc => ";
			cocix->Desire = new Dormir();
			return false;
		case JourNuit::CREPUSCULE:
			if(verbal) cout << "Crépuscule => ";
           	if(cocix->malade()) 	cocix->Desire = new Se_Soigner();
        	else if(cocix->soif())	cocix->Desire = new Boire();
        	else if(cocix->faim())	cocix->Desire = new Manger();
        	else	        		cocix->Desire = new Dormir();
			return false;
		case JourNuit::JOUR:
			if(cocix->malade()) 
        	{
        		cocix->Desire = new Se_Soigner();
        		return false;
        	}
        	else if(cocix->fecondee() && cocix->cycle_sexuel() == 4 && cocix->get_id_oeuf() !=0)
        	{
        		cocix->Desire = new Pondre();
        		return false;	
        	} 
        	else if(cocix->soif())
        	{
        		cocix->Desire = new Boire();
        		return false;
        	}         		
        	else if(cocix->faim())
        	{
        		cocix->Desire = new Manger();
        		return false;
        	}         		
        	else if(cocix->froid())
        	{
        		cocix->Desire = new Rentrer();
        		return false;
        	}
	}    	
	return true;
}