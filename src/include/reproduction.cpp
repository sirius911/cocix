#include "reproduction.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <map>
//#include <vector>
#include "constantes.h"

#include "monde.h"
#include "io.h"
#include "class/Cocix.h"
#include "class/JourNuit.h"
#include "class/Actions/Dormir.h"

//#include "class/Gene.h"


int partenaire(const short num_case, const Cocix *cocix, const bool verbal)
{
	// fonction renvoyant un id cocix partenaire potentiel sur num_case 
	struct ligneCase caseMonde;
	int num_partenaire = 0;

	Cocix *partenaire_potentiel;
	
	caseMonde = lirecase(num_case);
	int i=0;
	do
	{
		if(caseMonde.cocix[i] != 0 && caseMonde.cocix[i] != cocix->get_id())
		{
			// ni vide ni moi même

			partenaire_potentiel = new Cocix(caseMonde.cocix[i]);

			// on teste la potentialité de ce cocix
			if (partenaire_potentiel->get_id() !=0)
			{
				if(verbal) cout << "\tPartenaire potentiel = " << partenaire_potentiel->get_id() << "\n";
				if(cocix->sexe != partenaire_potentiel->sexe)
				{
					if(verbal) cout << "\t\tSexuellement compatible.\n";

					if((partenaire_potentiel->sexe == MALE && partenaire_potentiel-> cycle_sexuel() >= 0) || (partenaire_potentiel->sexe == FEMELLE && partenaire_potentiel->cycle_sexuel() < 3 
						&& partenaire_potentiel->cycle_sexuel() >= 0 && !partenaire_potentiel->balises.fecondee))
					{
						if(verbal) cout << "\t\t\tDisponible.\n";

						if(!partenaire_potentiel->balises.coma)
						{
							// ok
							// il faut ici faire les criteres de consanguinité
							num_partenaire = partenaire_potentiel->get_id();
							if(verbal) cout << "\t\t\t\tPartenaire retenu\n";
						}
						else
						{
							if(verbal) cout << "\t\t\t\tDans le coma !\n";
						}
					}
					else
					{
						if(verbal) cout << "\t\t\tNon disponible.\n";
					}
				}
				else
				{
					if(verbal) cout << "\t\tDu même sexe!\n";
				}
			}
		}
	} while( ++i < MAX_PAR_CASE);

	return num_partenaire;
}

short meilleur_case_partenaire(short case_centrale, Cocix *cocix, bool verbal){
	/* Fonction renvoyant le num case du meilleur partenaire 
	*/
	short case_haut_gauche,case_haut,case_haut_droite,case_droite,case_gauche,case_bas_droite,case_bas,case_bas_gauche;
	int part_haut_gauche,part_haut,part_haut_droite,part_droite,part_gauche,part_bas_droite,part_bas,part_bas_gauche;
		
		// case de recherche
	case_haut_gauche = monte_gauche(case_centrale);
	case_haut = monte(case_centrale);
	case_haut_droite = monte_droite(case_centrale);
	case_droite = droite(case_centrale);
	case_gauche = gauche(case_centrale);
	case_bas_droite = descend_droite(case_centrale);
	case_bas = descend(case_centrale);
	case_bas_gauche = descend_gauche(case_centrale);

	// on execute la recherche

	part_haut_gauche = partenaire(case_haut_gauche, cocix, verbal);
	part_haut = partenaire(case_haut, cocix, verbal);
	part_haut_droite = partenaire(case_haut_droite, cocix, verbal);
	part_droite = partenaire(case_droite, cocix, verbal);
	part_bas_droite = partenaire(case_bas_droite, cocix, verbal);
	part_bas = partenaire(case_bas, cocix, verbal);
	part_bas_gauche = partenaire(case_bas_gauche, cocix, verbal);
	part_gauche = partenaire(case_gauche, cocix, verbal);
	
		// les places doivent être libres
		if( part_haut_gauche > 0 && libre(case_haut_gauche) ) {

		/*		x..
				.o.
				...			*/

			if(verbal) cout << "La case en haut à gauche est libre et a un partenaire...\n";
			return case_haut_gauche;
			

		}
		if( part_haut > 0 && libre(case_haut)) {

		/*		.x.
				.o.
				...			*/		

			if(verbal) cout << "La case en haut est libre et a un partenaire...\n";
			return case_haut;

		}	
		if( part_haut_droite > 0 && libre(case_haut_droite)) {

		/*		..x
				.o.
				...			*/		

			if(verbal) cout << "La case en haut à droite est libre et a un partenaire...\n";
			return case_haut_droite;

		}
		if( part_droite > 0 && libre(case_droite)) {

		/*		...
				.ox
				...			*/

			if(verbal) cout << "La case à droite est libre et a un partenaire...\n";
			return case_droite;

		}
		if( part_bas_droite > 0 && libre(case_bas_droite)) {

		/*		...
				xo.
				...			*/
			if(verbal) cout << "La case à gauche  est libre et a un partenaire...\n";
			return case_bas_droite;

		} 
		if(part_bas > 0 && libre(case_bas) ) {
		/*		...
				.o.
				..x			*/	

			if(verbal) cout << "La case en bas à droite est libre et a un partenaire...\n";
			return case_bas;

		} 
		if( part_bas_gauche > 0 && libre(case_bas_gauche)){
		/*		...
				.o.
				.x.			*/		

			if(verbal) cout << "La case en bas est libre et a un partenaire...\n";
			return case_bas_gauche;

		}
		if(part_gauche > 0 && libre(case_gauche) ) {
		/*		...
				.o.
				x..			*/
			if(verbal) cout << "La case en bas à gauche est libre et a un partenaire...\n";
			return case_gauche;

		}
	return 0;
}


int procreation (Cocix *Male, Cocix *Femelle, bool verbal)
{
	JourNuit Jour_Nuit;
	Cocix Oeuf_Cocix;

	if(verbal)
	{
		cout << "je dois faire un oeuf avec :\n";
		Male->affiche(false);
		cout << "Et\n";					
		Femelle->affiche(false);
	}

	// récuperation du numéro de l'oeuf
	int num_oeuf = Jour_Nuit.incremente_indexCocix();
	if(verbal) cout << "Numéro du prochain CoCiX = " << num_oeuf << " -> ";			//id
	Oeuf_Cocix.set_id(num_oeuf);

	// sexe
	bool x_sexe = ((bool)aleatoire(0,1));
	if(verbal) cout << ((x_sexe)?"Male":"Femelle");									//sexe
	Oeuf_Cocix.set_sexe(x_sexe);	

	// fichier
	char x_fichier[30];
	sprintf(x_fichier, "%d.oeuf", num_oeuf);										//fichier
	if(verbal) cout << "Nom de fichier : " << x_fichier << "\n";
	Oeuf_Cocix.set_fichier(x_fichier);

	// nom
	char x_nom[10];
	sprintf(x_nom,"%s%d", ((x_sexe)? "M":"F"), num_oeuf);							//nom
	if(verbal) cout << "Nom = " << x_nom << "\n";
	Oeuf_Cocix.set_nom(x_nom);

	//id père & mère
	Oeuf_Cocix.set_idPere(Male->get_id());											//idPere
	Oeuf_Cocix.set_idMere(Femelle->get_id());										//idMere

	// case de naissance, date de naissance  et de mort et Vieux
	Oeuf_Cocix.set_case_naissance(0);												//case_naissance
	Oeuf_Cocix.set_date_naissance(0);												//date_naissance
	Oeuf_Cocix.set_date_mort(0);													//date_mort
	//Oeuf_Cocix.set_vieux(0);	// peut etre pas indispensable puisque intialisé normalement													//vieux

	// intialisation divers paramètres
	Oeuf_Cocix.set_id_partenaire(0);												//id_partenaire
	Oeuf_Cocix.set_case_presence(0);												//case_presence
	Oeuf_Cocix.set_recolte(0);														//recolte
	Oeuf_Cocix.set_id_oeuf(0);														//id_oeuf

	// GenoGenese
	// pour chaque gene de 0 à nbgene ( on considère pour l'instant qu'ils ont le meme nombre de gène)
	if(Male->genome.size() != Femelle->genome.size())
	{
		cout << "ATTENTION Ils n'ont pas le même nombre de gènes .... pas possible !\n";
		return 0;
	}


#define MERE 0
#define PERE 1
#define GP_P 2
#define GP_M 3
#define GM_P 4
#define GM_M 5


	int numeroGene = 0;
	int mode_transmission, i, id_gene,hazardius;
	char nomGene[30];
	bool pourc;
	float tableau_gene[6];
	string tableau_trans[6] = {"de la Mère","du Père","du Grand-père Paternel","du Grand-père Maternel","de la Grand-mère Paternelle","de la Grand-mère Maternelle"};

	do
	{
		strcpy(nomGene, Male->genome[numeroGene].nom);		// on prend le nom du gene chez le mâle

		id_gene = Male->genome[numeroGene].id;
		tableau_gene[MERE] = Femelle->genome[numeroGene].valeur;	//valeur de la femelle
		tableau_gene[PERE] = Male->genome[numeroGene].valeur;		// valeur du male
		tableau_gene[GP_P] = Male->genome[numeroGene].pere;		// gp_pere => valeur du pere du pere
		tableau_gene[GP_M] = Femelle->genome[numeroGene].pere;	// gp_mere => valeur du pere de la mere
		tableau_gene[GM_P] = Male->genome[numeroGene].pere;		//gm_pere => valeur de la mere du pere
		tableau_gene[GM_M] = Femelle->genome[numeroGene].mere;	//gm_mere => valeur de la mere de la mere
		

		if(verbal)
		{
			cout << "------------------------------------------\n";
			cout << "Transmission du gène : " << nomGene << "\n";
			cout << "type de transmission : " << Male->genome[numeroGene].trans() << setprecision(3) << "\n";
			for(i = 0 ; i < 6 ;i++)
			{
				cout << "\tValeur " << tableau_trans[i] << " = " << tableau_gene[i] << "\n";
			}
		}

		// on recupere le flag pourc
		pourc = Male->genome[numeroGene].pourc;

		// on doit récuperer le mode de transmission du gène
		mode_transmission = Male->genome[numeroGene].mod_trans;
		switch(mode_transmission)
		{
		
		case P:					// P => transmission par le père
			hazardius = PERE;
			break;
		case M:					// M => transmission par la mère
			hazardius = MERE;
			break;
		case PM:				// PM => transmission par le père OU la mère
			hazardius = aleatoire(MERE,PERE);
			break;
		case pm:				// pm => transmission de père en fils ou de mère en fille
			if(Oeuf_Cocix.male())
				hazardius = aleatoire(PERE,GP_M);	// que les mâles
			else
			{
				hazardius = aleatoire(3,GM_M);
				if(hazardius == 3 ) hazardius = MERE;
			}
			break;
		case GP:				// GP => transmission par un des deux Grands pères (saute une génération)
			hazardius = aleatoire(GP_P,GP_M);
			break;
		case GM:				// GM => transmission par une des deux grands mères
			hazardius = aleatoire(GM_P,GM_M);
			break;
		case H:					// H => transmission par les mâles p, gp_m, gp_p
			hazardius = aleatoire(PERE,GP_M);
			break;
		case F:					// F => transmission par les femelles m, gm_m , gm_p
			hazardius = aleatoire(3,GM_M);
			if(hazardius == 3) hazardius = MERE;	// => 0, 4 ou 5
			break;
		case m6:				// m6 => transmission par les 6 membres
			hazardius = aleatoire(MERE,GM_M);
			break;
		default:
			hazardius = aleatoire(MERE,GM_M);
			break;
		}

		if(verbal)
		{
			cout << "\tValeur rentenue, celle " << tableau_trans[hazardius] << " = ";
			if(pourc) cout << (tableau_gene[hazardius] * 100) << "%";
			else cout << tableau_gene[hazardius];
			
			cout << "\n";
		} 	
		
		// les modificateurs
		float valeur;
		float modif_generale = 5.0f ,modif_radioactive,modificateur;

		valeur = tableau_gene[hazardius];
		modif_generale = 5;		//5%
		modif_radioactive = (int) (radioactivite(Femelle->get_case_presence()) / 10);
		modificateur = ( ( modif_generale + modif_radioactive) - aleatoire( 1 , ( modif_generale + modif_radioactive) * 2 ));
		valeur = ( valeur + ( modificateur / 100.0f * valeur) );
		if(verbal) {
			cout << "\t modif radioactivite = " << modif_radioactive << " \n";
			cout << "\t modificateurs aléatoires ==> " << modificateur << "%\n";
			cout << "Valeur enregistrée ====> ";
			if(pourc) cout << ( valeur * 100 ) << "%\n";
			else cout << valeur << "\n";
		}

		
		// on récupère les infos pour l'oeuf en fonction du gène

		switch(id_gene)
		{
			case VIEUX:
				if(verbal) cout << "Initialisation du paramètre 'Vieux' \n";
				Oeuf_Cocix.set_vieux(valeur);
				break;
			case VIVACITE:
				if(verbal) cout << "Initialisation de la vivacite \n";
				Oeuf_Cocix.set_vivacite(valeur);
				break;
			case SANTE:
				if(verbal) cout << "Initialisation de la santé\n";
				// on suppose le capital Sante des parents > 0 !!
				float correction;
				correction =  ( Femelle->Sante.get_valeur() - Femelle->Sante.get_capacite()) / Femelle->Sante.get_capacite();
				correction += ( Male->Sante.get_valeur() - Male->Sante.get_capacite()) / Male->Sante.get_capacite();
				if(verbal) cout << "Correction de Santé (parents) = " << ( correction * 100.0f ) << "\n";
				valeur += valeur * correction;
				if(verbal) cout << "Valeur du Capital Sante = " << valeur << " pdv\n";
		}

		// création du gene
		
		Oeuf_Cocix.genome.insert( Oeuf_Cocix.genome.end() , Gene( nomGene , id_gene, valeur, tableau_gene[PERE], tableau_gene[MERE],tableau_gene[GP_M],tableau_gene[GP_P],tableau_gene[GM_M],tableau_gene[GM_P], mode_transmission,pourc));
		if(verbal) Oeuf_Cocix.genome[id_gene].affiche();


	} while(++numeroGene < Male->get_nb_genes());

	Oeuf_Cocix.set_nb_genes(Male->get_nb_genes());

	// les paramètres d'Etats
	if(verbal)
	{
		cout << "**********************************************\n";
		cout << " paramètres d'états : \n";
	} 
	Oeuf_Cocix.Sante = Param_Etat("Param Santé","Pdv",Oeuf_Cocix.genome[SANTE].valeur,Oeuf_Cocix.genome[SANTE].valeur,
		Oeuf_Cocix.genome[SEUIL_MALADE].valeur * Oeuf_Cocix.genome[SANTE].valeur, (float)NULL,
		Oeuf_Cocix.genome[SEUIL_COMA].valeur * Oeuf_Cocix.genome[SANTE].valeur, (float)NULL,
		Oeuf_Cocix.genome[SEUIL_MALADE].valeur * Oeuf_Cocix.genome[SANTE].valeur,(float)NULL,
		(float) SOUFFRANCE_MALADIE,0.0f,Oeuf_Cocix.genome[SANTE].valeur);	// plafond est Capacite
	if(verbal) Oeuf_Cocix.Sante.affiche(true,verbal);

	Oeuf_Cocix.Calorie = Param_Etat("Calories","Cal",Oeuf_Cocix.genome[CALORIE].valeur,Oeuf_Cocix.genome[CALORIE].valeur,
		(float)NULL,(float) NULL,	
		Oeuf_Cocix.genome[CALORIE].valeur * (float) COMA_CALORIE,	(float)NULL,
		Oeuf_Cocix.genome[SOUFFRE_FAIM].valeur * Oeuf_Cocix.genome[CALORIE].valeur,(float)NULL,
		(float) SOUFFRANCE_CALORIQUE,0.0f,Oeuf_Cocix.genome[CALORIE].valeur);
	if(verbal) Oeuf_Cocix.Calorie.affiche(false,verbal);

	Oeuf_Cocix.Hydro = Param_Etat("Param Hydro","muL",Oeuf_Cocix.genome[HYDRO].valeur,Oeuf_Cocix.genome[HYDRO].valeur,
		(float)NULL,(float) NULL,	
		Oeuf_Cocix.genome[HYDRO].valeur * (float)COMA_HYDRO, (float)NULL,	
		Oeuf_Cocix.genome[SOUFFRE_SOIF].valeur * Oeuf_Cocix.genome[HYDRO].valeur, (float)NULL,		
		(float) SOUFFRANCE_HYDRIQUE,0.0f,Oeuf_Cocix.genome[HYDRO].valeur);
	if(verbal) Oeuf_Cocix.Hydro.affiche(false,verbal);

	Oeuf_Cocix.Temperature = Param_Etat("Température","°C",37.5f,37.5f,
		(float)NULL, 40.0f,
		36.0f,42.0f,
		36.0f,40.0f,
		(float) SOUFFRANCE_THERMIQUE, 35.5f, 43.5f);	
	if(verbal) Oeuf_Cocix.Temperature.affiche(false,verbal);
	
	// balises etat
	Oeuf_Cocix.balises.fecondee = false;
	Oeuf_Cocix.balises.vivant = true;
	Oeuf_Cocix.balises.mort = false;
	Oeuf_Cocix.balises.malade = false;
	Oeuf_Cocix.balises.coma = false;
	Oeuf_Cocix.balises.agressive = false;
	Oeuf_Cocix.balises.froid = false;
	Oeuf_Cocix.balises.faim = false;
	Oeuf_Cocix.balises.soif = false;

	Oeuf_Cocix.Desire = new Dormir();
	Oeuf_Cocix.Action = new Dormir();

	// on sauvegarde l'oeuf
	Oeuf_Cocix.sauvegarde(verbal);

	return num_oeuf;
}