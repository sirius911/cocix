#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

#include "Param_Etat.h"

Param_Etat::Param_Etat(){

}

Param_Etat::Param_Etat(const char x_nom[20], const char x_unite[3], float x_capacite, float x_valeur, 
	float x_limite_basse_malade, float x_limite_haute_malade, 
	float x_limite_basse_coma, float x_limite_haute_coma,  
	float x_limite_basse_souffrance,float x_limite_haute_souffrance,  
	float x_correction_souffrance){
	strcpy(nom, x_nom);
	strcpy(unite, x_unite);
	capacite = x_capacite;
	valeur = x_valeur;
	if(valeur > capacite) valeur = capacite;

	//Limite rendant malade
	limite_haute_malade = x_limite_haute_malade;
	limite_basse_malade = x_limite_basse_malade;
	limite_haute_coma = x_limite_haute_coma;
	limite_basse_coma = x_limite_basse_coma;

	//limite causant de la souffrance;
	limite_haute_souffrance = x_limite_haute_souffrance;
	limite_basse_souffrance = x_limite_basse_souffrance;
	correction_souffrance = x_correction_souffrance;
}

//méthodes

	void Param_Etat::affiche(bool pourcentage, bool limite){
		bool tab1=false,tab2 = false;
		cout << "<" << fixed <<  setw(7) << nom << ">\t => " << setprecision(2)<< setw(9);
		if(pourcentage)
			cout << _valeur(pourcentage)*100 << "\%\t\t";
		else
			cout << valeur << unite << " / " << capacite << unite;
		if(limite){
			cout << "\t\t\t*** LIMITES ***\n";
			cout << "\t Mal [";
			if(limite_basse_malade == (float) NULL){
				cout << "*";
				tab1 = true;
			}
			else 
				cout << limite_basse_malade;
			cout << " , ";
			if(limite_haute_malade == (float) NULL){
			 	cout << "*]";
			 	tab2 = true;
			}
			else
			 	cout << limite_haute_malade << "]";
			 if(tab1 & tab2) cout << "\t";
			cout << "\t coma [";
			if(limite_basse_coma == (float) NULL)
				cout << "*";
			else
				cout << limite_basse_coma;
			cout << " , ";
			if(limite_haute_coma == (float) NULL)
				cout << "*";
			else
				cout << limite_haute_coma;
			cout << "] \t souffre - [";
			if(limite_basse_souffrance == (float) NULL)
				cout << "*";
			else
				cout << limite_basse_souffrance;
			cout  << " , ";
			if(limite_haute_souffrance == (float) NULL)
				cout <<  "*";
			else
				cout <<limite_haute_souffrance;
			cout << "]\t corr : " << correction_souffrance * 100 << "%\n";
		} else
			cout << "\n";
	}

	float Param_Etat::_valeur( bool pourcentage){
		if(pourcentage)	return ((capacite == 0.0f)? 0:valeur/capacite) ;
		else return valeur;
	}

	void Param_Etat::_valeur(float x_valeur, struct_balises *balises){
		valeur = x_valeur;
		maj_balises(balises);
	}

	void Param_Etat::modif(float modificateur, struct_balises * balises, bool verbal){
		if(verbal) cout << "Modif : " << nom << " -> " << modificateur << unite;
		valeur = valeur + modificateur;
		if(capacite != (float) NULL  && valeur > capacite){
			// la valeur du paramètre ne peut dépacer sa capacité sauf si la capacité est NULL (Température)
			valeur = capacite;
		}
		if(verbal) cout << " nouvelle valeur = " << valeur << unite <<"\n";
		maj_balises(balises);

	}

	void Param_Etat::maj_balises(struct_balises *balises, bool verbal){
		// On met à jours les balises en fonction des limites
		// Question peut on mettre un float dans une valeur comme null ou vide afin d'indiquer qu'on 
		// ne veut pas de limite (actuellement c'est -1 ce qui nous interdit d'avoir des valeurs négatives)
		if(verbal) cout << "		** Controle des limites **\n";
		//cout << "Avant maj_balises() : Malade -> " << ((balises->malade)?"Oui":"Non") << " -- Coma -> " << ((balises->coma)?"Oui":"Non") << "\n";
		if(verbal) cout << "Maladie -->\n";
		if(limite_haute_malade == (float) NULL )
		{
			if (limite_basse_malade == (float)NULL)
			{
				if(verbal) cout << "\t\tAucun dépassement de limite maladie ";
				// [*,*] aucun changement sur la balise malade
			} else 
			{
				 // [x,*] malade si valeur < limite inf
				if(verbal) cout << "\t\t Malade si " << nom <<" <= " << limite_basse_malade << unite;
				balises->malade = (balises->malade | ( valeur <= limite_basse_malade));
			} 
		} else 
		{
			if(limite_basse_malade == (float)NULL)
			{
				// [*,x]
				// malade si valeur > limite haute
				if(verbal) cout << "\t\t Malade si " << nom << " >= " << limite_haute_malade << unite;
				balises->malade = (balises->malade | (valeur >= limite_haute_malade));
			} else 
			{
				// [x,y] malade si pas entre limite nasse et haute
				if(verbal) cout << "\t\t Malade si " << limite_basse_malade << unite << " <= " << nom << "<= " << limite_haute_malade << unite; 
				balises->malade = (balises->malade | !( (limite_haute_malade <= valeur) & (valeur <= limite_basse_malade)));
			}
		}
		if(verbal) cout << " (" << valeur << unite << " )\n";
		if(verbal) cout << "Coma -->\n";
		// meme chose pour les limites du coma
		if(limite_haute_coma == (float)NULL)
		{
			if (limite_basse_coma == (float)NULL)
			{
				// [-1,-1] aucun changement sur la balise malade
				if(verbal) cout << "\t\tAucun dépassement de limite coma ";
			} else 
			{
				 // [x,-1] malade si valeur < limite inf
				if(verbal) cout << "\t\t Coma si " << nom <<" <= " << limite_basse_coma << unite;
				balises->coma = (balises->coma | ( valeur <= limite_basse_coma));
			} 
		} else {
			if(limite_basse_coma == (float)NULL)
			{
				// [-1,x]
				if(verbal) cout << "\t\t Coma si " << nom << " >= " << limite_haute_coma << unite;
				balises->coma = (balises->coma| (valeur >= limite_haute_coma));
			} else 
			{
				// [x,y] malade si pas entre limite nasse et haute
				if(verbal) cout << "\t\t Coma si " << limite_basse_coma << unite << " <= " << nom << "<= " << limite_haute_coma << unite; 
				balises->coma = (balises->coma | ( valeur >= limite_haute_coma || valeur <= limite_basse_coma));
			}
		}
		if(verbal) cout << " (" << valeur << unite << " )\n";
		if(verbal) cout << "\nAprès maj_balises() : Malade -> " << ((balises->malade)?"Oui":"Non") << " \t Coma -> " << ((balises->coma)?"Oui":"Non") << "\n"; 
		if(verbal) cout << "**********************\n";
	}

	void Param_Etat::souffrance(Param_Etat *XSante, const bool coma)
	{
		// mise à jour de la Santé en fonction des dépacements de limite du Paramètre
		bool je_souffre = false;
		if (XSante->valeur > 0.0f)
		{
			if(limite_haute_souffrance == (float) NULL )
			{
				if (limite_basse_souffrance == (float)NULL)
				{
					// [-1,-1] aucune souffrance
				} else 
				{
				 	// [x,-1] souffre si valeur < limite basse
					je_souffre = ( valeur <= limite_basse_souffrance);
				} 
			} else 
			{
				if(limite_basse_souffrance == (float)NULL)
				{
					// [-1,x]
					// soufre si valeur > limite haute
					je_souffre = (valeur >= limite_haute_souffrance);
				} else 
				{
					// [x,y] souffre si pas entre limite basse et haute
					je_souffre = ( valeur >= limite_haute_souffrance || valeur <= limite_basse_souffrance);
				}
			}
			if(coma)
				XSante->valeur -= (XSante->valeur * SOUFFRANCE_COMA);	// On utilise la correction coma
			else if(je_souffre)
					XSante->valeur -= (XSante->valeur * correction_souffrance);

		}
	}

	int Param_Etat::sauvegarde(ofstream *f){
		f->write ((char*) &nom, sizeof (char[20]));
		f->write ((char*) &unite, sizeof (char[4]));
		f->write ((char*) &capacite, sizeof(float));
		f->write ((char*) &valeur, sizeof(float));
		f->write ((char*) &limite_haute_malade, sizeof(float));
		f->write ((char*) &limite_basse_malade, sizeof(float));
		f->write ((char*) &limite_haute_coma, sizeof(float));
		f->write ((char*) &limite_basse_coma, sizeof(float));
		f->write ((char*) &limite_haute_souffrance, sizeof(float));
		f->write ((char*) &limite_basse_souffrance, sizeof(float));
		f->write ((char*) &correction_souffrance, sizeof(float));
		return 0;
	}

	int Param_Etat::charge(ifstream *f){
		f->read((char*) &nom, sizeof(char[20]));
		f->read((char*) &unite, sizeof(char[4]));
		f->read((char*) &capacite, sizeof(float));
    	f->read ((char*) &valeur, sizeof(float));
		f->read ((char*) &limite_haute_malade, sizeof(float));
		f->read ((char*) &limite_basse_malade, sizeof(float));
		f->read ((char*) &limite_haute_coma, sizeof(float));
		f->read ((char*) &limite_basse_coma, sizeof(float));
		f->read ((char*) &limite_haute_souffrance, sizeof(float));
		f->read ((char*) &limite_basse_souffrance, sizeof(float));
		f->read ((char*) &correction_souffrance, sizeof(float));
		return 0;
	}