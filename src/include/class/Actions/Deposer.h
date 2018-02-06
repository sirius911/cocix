#ifndef DEF_CLASS_DEPOSER
#define DEF_CLASS_DEPOSER
#include "Actions.h"

class Deposer : public Actions
{
	public:
		Deposer();
		void go(Cocix*,bool=false);
		bool valide_Action(const Cocix* , const bool = false);

	private:
		void charge();
};

#endif