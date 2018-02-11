#include "Boire.h"
#include <cstring>
#include <iostream>
#include "../../monde.h"
#include "Cherche_Eau.h"
#include "../Cocix.h"

using namespace std;

Boire::Boire(){
	charge();
	Action_alternative = new Cherche_Eau();
}

bool Boire::valide_Action(const Cocix* cocix , bool verbal){
	if(verbal) cout << " Y-a-t-il de l'eau sur ma case ?... ";
	return(humidite(cocix->case_presence) > 0);
}

void Boire::charge(){
	set_id( 1 );
	strcpy(action, "Je bois");
	strcpy(desire, "boire");
	set_chaleur(-0.05f);
	set_eau(0.0f);
	set_calorie(0.3f);
	set_duree(5);
	deplacement = false;
	peut_etre_stoppee = false;
}

//   *************************************** A C T I O N ***********************
void Boire::go(Cocix *cocix,bool verbal){
	

	float quantite_prise, dim_temp;
	struct struct_xy xy;

	case_boisson = cocix->case_presence;
	xy  = case_to_xy(case_boisson);

	cout <<  "...................................................\n";
	if(verbal) Actions::index();
	cout << "ACTION => BOIT ....\n";
		
	// On met à jour la base de donnée du monde
	if(verbal) cout << "En case N° " << case_boisson << " (" << xy.x << "," << xy.y << ") Il y a " << humidite(case_boisson) << "uL avant.\n";
	quantite_prise = prend_element(case_boisson,cocix->genome[ASSIMILATION_HYDRIQUE].valeur,EAU);
	cocix->Hydro.modif(quantite_prise, &cocix->balises,verbal);
		
	//On incrémente le temps de l'action
	le_temps_s_ecoule(verbal);
		
	// Diminution de la température corporel 1% de la quantite prise
	dim_temp = (0.01 * quantite_prise);
	cocix->Temperature.modif(-dim_temp, &cocix->balises,verbal);
	
	if(verbal) cout << "Il y a maintenant "<< humidite(case_boisson) << "uL.\n";
	if(verbal) cout << "Diminution de " << dim_temp << "°C => température = " << cocix->Temperature.get_valeur() << "°C \n";
	

	// on verifie la satiété pour l'eau la CoCiX n' plus soif si hydro==CH
		if(cocix->Hydro.get_valeur() == cocix->Hydro.get_capacite()) {
		
			if(verbal) cout << "La Capacité hydrique est atteinte...\n";	
			set_action_terminee(true);
			cocix->balises.soif = false;
		}
		
		if(! valide_Action(cocix , verbal)){
			if(verbal) cout << "NON ! \n";
			set_action_terminee(true);
		} else {
			if(verbal) cout << "OUI !\n";
		}
	cout << "\n";
	Actions::affiche_action(false);
	cout << "...................................................\n";
}
