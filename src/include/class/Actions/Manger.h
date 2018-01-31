#ifndef DEF_CLASS_MANGER
#define DEF_CLASS_MANGER
#include "Actions.h"

class Manger : public Actions
{
	public:
		Manger();
		Manger(short);

		void go(Cocix*,bool=false);
		bool valide_Action(const bool = false);

	private:
		void charge();
		short case_nourriture;
};

#endif