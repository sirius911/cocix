#ifndef DEF_CLASS_CHERCHE_RECOLTE
#define DEF_CLASS_CHERCHE_RECOLTE
#include "Actions.h"
#include "../Cocix.h"

class Cherche_Recolte : public Actions
{
	public:

		Cherche_Recolte();
		void go(Cocix*, const bool=false);
		bool valide_Action(const Cocix* , const bool = false) ;

	private:
		void charge();
};

#endif