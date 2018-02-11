#ifndef DEF_CLASS_CHERCHE_NOURRITURE
#define DEF_CLASS_CHERCHE_NOURRITURE
#include "Actions.h"
#include "../Cocix.h"

class Cherche_Nourriture : public Actions
{
	public:

		Cherche_Nourriture();
		void go(Cocix*, const bool=false);
		bool valide_Action(const Cocix* , const bool = false) ;

	private:
		void charge();
		//bool recolte;	//si vrai alors on recolte et on ne mange pasmeilleur_case
};

#endif