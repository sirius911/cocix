#ifndef DEF_CLASS_BOIRE
#define DEF_CLASS_BOIRE
#include "Actions.h"
#include "../Cocix.h"

class Boire : public Actions
{
	public:

		Boire();
		void go(Cocix*,bool=false);
		bool valide_Action(const Cocix* , const bool = false);

	private:
		void charge();
		short case_boisson;
};

#endif