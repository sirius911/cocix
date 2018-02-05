#ifndef DEF_CLASS_DORMIR
#define DEF_CLASS_DORMIR
#include "Actions.h"

class Dormir : public Actions
{
	public:
		Dormir();
		bool valide_Action(const Cocix*,const bool verbal = false);
		void go(Cocix*,bool=false);
};

#endif