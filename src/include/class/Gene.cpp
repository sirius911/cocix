#include <iostream>
#include <cstring>
#include "Gene.h"


Gene::Gene()
{
	//std::cout<<"Construction gène à l'adresse : " << this <<"\n";
}

Gene::Gene(const char x_nom[30], int x_id, float x_valeur, float x_pere, float x_mere, float x_gp_mere, float x_gp_pere, float x_gm_mere, float x_gm_pere)
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
}

void Gene::affiche(){

	std::cout<<"GENE # " << id << ": " << nom << " => " << valeur << " (" << pere << "," << mere << "," << gp_mere << "," << gp_pere << "," << gm_mere << "," << gm_pere << ")\n";
}