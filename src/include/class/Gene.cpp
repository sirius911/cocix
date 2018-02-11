#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>
#include "Gene.h"
#include "../constantes.h"

using namespace std;

Gene::Gene()
{
	//std::cout<<"Construction gène à l'adresse : " << this <<"\n";
}

Gene::Gene(const char x_nom[30], int x_id, float x_valeur, float x_pere, float x_mere, float x_gp_mere, float x_gp_pere, float x_gm_mere, float x_gm_pere, int x_mod_trans, bool x_pourc)
{
	strcpy(nom,x_nom);
	id = x_id;
	valeur = x_valeur;
	pere = x_pere;
	mere = x_mere;
	gp_mere = x_gp_mere;
	gp_pere = x_gp_pere;
	gm_mere = x_gm_mere;
	gm_pere = x_gm_pere;
	mod_trans = x_mod_trans;
	pourc = x_pourc;
	affiche();
}

void Gene::affiche(){

	cout <<"GENE # " << id << ": " << nom << " => " << affiche(valeur) << " (" << affiche(pere) << ","
	 << affiche(mere) << "," << affiche(gp_mere) << "," << affiche(gp_pere) << "," << affiche(gm_mere) << ","
	  << affiche(gm_pere) << trans() << ")\n";
}

/*
float Gene::affiche(float x)
{
	if(pourc)
		return (x*100);
	else
		return x;
}
*/

const string Gene::affiche(const float x)
{
	ostringstream sortie;
	
	if(pourc)
	{
		//sprintf(sortie,"%f %%",x*100);
		sortie << (x*100) << "%";
	}
	else
	{
		//sprintf(sortie,"%7.3f",x);
		sortie << x;
	}
	return sortie.str();
}


const char* Gene::trans()
{
	switch(mod_trans)
	{
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
		case P:
			return "<P>";
			break;
		case M:
			return  "<M>";
			break;
		case PM:
			return  "<PM>";
			break;
		case pm:
			return  "<pm>";
			break;
		case GP:
			return "<GP>";
			break;
		case GM:
			return "<GM>";
			break;
		case H:
			return "<H>";
			break;
		case F:
			return "<F>";
			break;
		case m6:
			return "<m6>";
			break;
		default:
			return "<\?\?>";
			break;
	}
}

int Gene::sauvegarde(ofstream *f){
		f->write ((char*) &nom, sizeof (char[30]));
		f->write ((char*) &id, sizeof(int));
		f->write ((char*) &valeur, sizeof(float));
		f->write ((char*) &pere, sizeof(float));
		f->write ((char*) &mere, sizeof(float));
		f->write ((char*) &gp_mere, sizeof(float));
		f->write ((char*) &gp_pere, sizeof(float));
		f->write ((char*) &gm_mere, sizeof(float));
		f->write ((char*) &gm_pere, sizeof(float));
		f->write ((char*) &mod_trans, sizeof(int));
		f->write ((char*) &pourc, 1);
		
		return 0;
	}

	int Gene::charge(ifstream *f){
		//float x_capacite;
		f->read((char*) &nom, sizeof(char[30]));
		f->read((char*) &id, sizeof(int));
    	f->read ((char*) &valeur, sizeof(float));
		f->read ((char*) &pere, sizeof(float));
		f->read ((char*) &mere, sizeof(float));
		f->read ((char*) &gp_mere, sizeof(float));
		f->read ((char*) &gp_pere, sizeof(float));
		f->read ((char*) &gm_mere, sizeof(float));
		f->read ((char*) &gm_pere, sizeof(float));
		f->read ((char*) &mod_trans, sizeof(int));
		f->read ((char*) &pourc, 1);
		
		return 0;
	}