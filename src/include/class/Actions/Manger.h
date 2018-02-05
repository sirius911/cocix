#ifndef DEF_CLASS_MANGER
#define DEF_CLASS_MANGER
#include "Actions.h"

class Manger : public Actions
{
	public:
		Manger();

		void go(Cocix*,bool=false);
		bool valide_Action(const Cocix* , const bool = false);

	private:
		void charge();
};

#endif