#include "Cortex_Adulte_Femelle.h"
#include "../../constantes.h"
#include "../Cocix.h"

#include <cstring>
#include <iostream>
#include <iomanip>
#include <math.h>

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

Cortex_Adulte_Femelle::Cortex_Adulte_Femelle()
{
	strcpy(nom,"Adulte Femelle");
}

void Cortex_Adulte_Femelle::gestion_Etat(Cocix* cocix, const bool verbal)
{
	Cortex_Adulte::gestion_Etat(cocix,verbal);
}

bool Cortex_Adulte_Femelle::decide_Desire(Cocix* cocix, const bool verbal)
{
	if(Cortex_Adulte::decide_Desire(cocix , verbal))
	{
		// on continue ici les choix

		//FEMELLE      				
       	if(verbal) cout << "FEMELLE ==> ";

       	if(cocix->cycle_sexuel() >=0  && cocix->cycle_sexuel() < 3 )
       	{	
       		if(cocix->fecondee())
       		{	// non fécondable
       			if(cocix->compassion())				cocix->Desire = new Soigner();	
       			
       			else if(cocix->agressive())			cout << "Agresser()  ...non implémenté...";
       								//Desire = new Agresser();					
       			else
       			{
  					//recolte
  					if(cocix->pleine())				cocix->Desire = new Deposer();
        							
        			else							cocix->Desire = new Recolter();
        		}
       		}
       		else
       		{
       			//Fertile
        		if(cocix->agressive())				cout << "Agresser()  ...non implémenté...";
       								//Desire = new Agresser();
       			else if(cocix->compassion())		cocix->Desire = new Soigner();
       			
       			else								cocix->Desire = new Se_Reproduire();
           	}
   		}
       	else
       	{
       		// non fertile
       		if(cocix->agressive())					cout << "Agresser()  ...non implémenté...";
       							//Desire = new Agresser();
       		else if(cocix->compassion())			cocix->Desire = new Soigner();
       						
       		else
       		{
       			//recolte
       			if(cocix->pleine())					cocix->Desire = new Deposer();
        						
        		else								cocix->Desire = new Recolter();
        	}
        }

	}	

	cocix->Desire->affiche_desire(false);
	return true;
}