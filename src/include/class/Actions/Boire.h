#ifndef DEF_CLASS_BOIRE
#define DEF_CLASS_BOIRE
#include "Actions.h"
#include "../Cocix.h"

class Boire : public Actions
{
	public:

		Boire();
		Boire(short);
		void go(Cocix*,bool=false);
		bool valide_Action(const bool = false);

	private:
		void charge();
		short case_boisson;
};

#endif