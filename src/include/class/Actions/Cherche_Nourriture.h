#ifndef DEF_CLASS_CHERCHE_NOURRITURE
#define DEF_CLASS_CHERCHE_NOURRITURE
#include "Actions.h"
#include "../Cocix.h"

class Cherche_Nourriture : public Actions
{
	public:

		Cherche_Nourriture();
		Cherche_Nourriture(short);
		void go(Cocix *cocix, const bool=false);
		bool valide_Action(const bool = false) ;

	private:
		void charge();
		short case_nourriture;
};

#endif