#ifndef DEF_CLASS_PONDRE
#define DEF_CLASS_PONDRE
#include "Actions.h"

class Pondre : public Actions
{
	public:
		Pondre();
		void go(Cocix*,bool=false);
		bool valide_Action(const Cocix* , const bool = false);

	private:
		void charge();
};

#endif