#ifndef DEF_CLASS_SOIGNER
#define DEF_CLASS_SOIGNER
#include "Actions.h"

class Soigner : public Actions
{
	public:
		Soigner();
		void go(Cocix*,bool=false);
		bool valide_Action(const Cocix* , const bool = false);

	private:
		void charge();
};

#endif