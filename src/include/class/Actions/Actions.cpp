#include "Actions.h"

#include <iostream>
#include <fstream>

#include "../../constantes.h"
using namespace std;

//class Cocix;

Actions::Actions(){
	// Constructeur
	action_terminee = false;
	temps_ecoule = 0;

}

Actions::Actions(bool x_action_terminee , short x_temp_ecoule){
	action_terminee = x_action_terminee;
	temps_ecoule = x_temp_ecoule;
}

void Actions::affiche_action(bool info){

	cout << action;

	if(get_duree() == 0)
			cout << " ...en cours (action instantanée)\n";
	else
	{
			if(terminee())
				cout << " ...terminée.";
			else 
				cout << " depuis " << temps_ecoule << "mn";
	}
	if(info)
	{
			cout << " ( " << chaleur << "," << eau << "," << eau << "," << calorie << " - " <<
			duree << " - " << ((deplacement)?"T":"F") << " - " << ((peut_etre_stoppee)?"T":"F") << " )\n";
	}
	else
			cout << "\n";
}

void Actions::affiche_desire(bool verbal){
	if(verbal)
		cout << "Je désire " << desire << "\n";
	else
		cout << desire << "\n";
}

void Actions::go(Cocix*,const bool){
	cout << "Action NON IMPLÉMENTÉE !!\n";
}
bool Actions::valide_Action(const Cocix*, const bool verbal){
	if(verbal) cout << "Peut Toujours !\n";
	return true;
}


bool Actions::terminee(){
	return (temps_ecoule >= duree || peut_etre_stoppee || action_terminee);
}

void Actions::le_temps_s_ecoule(bool verbal){
	temps_ecoule++;
	if(verbal) cout << "temps écoulé : "<<temps_ecoule<<"\n";
}

bool Actions::equal(Actions A){
	return (get_id() == A.get_id());
}

/*******************************************************************************************************************
					SETTER
********************************************************************************************************************/

void Actions::set_id(short x_id){
	id = x_id;
}

void Actions::set_action_terminee(bool setbool){
	action_terminee = setbool;
}	

void Actions::set_temps_ecoule(short x_temp_ecoule){
	temps_ecoule = x_temp_ecoule;
}				

void Actions::set_duree(short x_duree){
	duree = x_duree;
}

void Actions::set_eau(float x_eau)
{
	eau = x_eau;
}

void Actions::set_chaleur(float x_chaleur)
{
	chaleur = x_chaleur;
}

void Actions::set_calorie(float x_calorie)
{
	calorie = x_calorie;
}

/********************************************************************************************************************
					GETTER
********************************************************************************************************************/

short Actions::get_id(){
	return id;
}

bool Actions::get_action_terminee(){
	return action_terminee;
}

short Actions::get_temps_ecoule(){
	return temps_ecoule;
}

short Actions::get_duree(){
	return duree;
}

float Actions::get_chaleur()
{
	return chaleur;
}

float Actions::get_eau()
{
	return eau;
}

float Actions::get_calorie()
{
	return calorie;
}

char* Actions::get_action()
{
	return action;
}

char* Actions::get_desire()
{
	return desire;
}
/********************************************************************************************************************
					FICHIER
********************************************************************************************************************/

int Actions::sauvegarde(ofstream *f){
	
	// Sauvegarde le num Action
    f->write ((char*) &id, sizeof(short));
    // sauvegarde les infos en cours de l'action.
    f->write ((char*) &temps_ecoule, sizeof(short));
    f->write ((char*) &action_terminee, 1);
    return 0;
}

void Actions::index(){
 		cout << "\t\t\t  ##    ####  ##### #  ####  #    # \n";
		cout << "\t\t\t #  #  #    #   #   # #    # ##   # \n";
		cout << "\t\t\t#    # #        #   # #    # # #  # \n";
		cout << "\t\t\t###### #        #   # #    # #  # # \n";
		cout << "\t\t\t#    # #    #   #   # #    # #   ## \n";
		cout << "\t\t\t#    #  ####    #   #  ####  #    # \n";
}



bool operator == ( Actions &action1 ,  Actions &action2){
	return (action1.get_id() == action2.get_id());
}

bool operator != ( Actions &action1 ,  Actions &action2){
	return !(action1.get_id() == action2.get_id());
}
/*
bool operator == ( Actions &action1 ,  Actions action2){
	return (action1.get_id() == action2.get_id());
}

bool operator != ( Actions &action1 ,  Actions action2){
	return !(action1.get_id() == action2.get_id());
}
*/
