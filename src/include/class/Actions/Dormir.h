#ifndef DEF_CLASS_DORMIR
#define DEF_CLASS_DORMIR
#include "Actions.h"

class Dormir : public Actions
{
	public:
		Dormir();
		void faire();
		bool valide_Action();
		void go(Cocix*,bool=false);
};

#endif