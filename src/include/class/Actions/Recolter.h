#ifndef DEF_CLASS_RECOLTER
#define DEF_CLASS_RECOLTER
#include "Actions.h"


class Recolter : public Actions
{
	public:
		Recolter();
		
		void go(Cocix*,bool=false);
		bool valide_Action(const Cocix* , const bool = false);

		private:
		void charge();
};

#endif