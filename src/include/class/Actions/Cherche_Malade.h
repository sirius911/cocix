#ifndef DEF_CLASS_CHERCHE_MALADE
#define DEF_CLASS_CHERCHE_MALADE
#include "Actions.h"
#include "../Cocix.h"

class Cherche_Malade : public Actions
{
	public:

		Cherche_Malade();
		void go(Cocix*, const bool=false);
		bool valide_Action(const Cocix* , const bool = false) ;

	private:
		void charge();
};

#endif