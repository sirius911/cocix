#ifndef DEF_CLASS_CHERCHE_EAU
#define DEF_CLASS_CHERCHE_EAU
#include "Actions.h"
#include "../Cocix.h"

class Cherche_Eau : public Actions
{
	public:

		Cherche_Eau();
		void go(Cocix *cocix, const bool=false);
		bool valide_Action(const Cocix* , const bool = false) ;

	private:
		void charge();
};

#endif