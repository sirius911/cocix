#ifndef DEF_CLASS_SE_REPRODUIRE
#define DEF_CLASS_SE_REPRODUIRE
#include "Actions.h"

class Se_Reproduire : public Actions
{
	public:
		Se_Reproduire();
		void go(Cocix*,bool=false);
		bool valide_Action(const Cocix* , const bool = false);

	private:
		void charge();
};

#endif