#ifndef DEF_CLASS_PONDRE
#define DEF_CLASS_PONDRE
#include "Actions.h"

class Pondre : public Actions
{
	public:
		Pondre();
		void faire();
		bool valide_Action();
};

#endif