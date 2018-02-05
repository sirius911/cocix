#ifndef DEF_CLASS_RENTRER
#define DEF_CLASS_RENTRER
#include "Actions.h"

#include "../Cocix.h"

class Rentrer : public Actions
{
	public:
		Rentrer();
		

		void go(Cocix*,bool=false);
		bool valide_Action(const Cocix* , const bool = false);

	private:
		void charge();
};

#endif