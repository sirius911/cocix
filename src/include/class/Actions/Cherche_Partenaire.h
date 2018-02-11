#ifndef DEF_CLASS_CHERCHE_PARTENAIRE
#define DEF_CLASS_CHERCHE_PARTENAIRE
#include "Actions.h"
#include "../Cocix.h"

class Cherche_Partenaire : public Actions
{
	public:

		Cherche_Partenaire();
		void go(Cocix*, const bool=false);
		bool valide_Action(const Cocix* , const bool = false) ;

	private:
		void charge();
};

#endif