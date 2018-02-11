#ifndef DEF_CLASS_CHERCHE_CASE_LIBRE
#define DEF_CLASS_CHERCHE_CASE_LIBRE
#include "Actions.h"
#include "../Cocix.h"

class Cherche_Case_Libre : public Actions
{
	public:

		Cherche_Case_Libre();
		void go(Cocix*, const bool=false);
		bool valide_Action(const Cocix* , const bool = false) ;

	private:
		void charge();
};

#endif