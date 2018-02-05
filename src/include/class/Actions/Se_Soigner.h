#ifndef DEF_CLASS_SE_SOIGNER
#define DEF_CLASS_SE_SOIGNER
#include "Actions.h"
class Se_Soigner : public Actions
{
	public:
		Se_Soigner();
		
		void go(Cocix*,bool=false);
		bool valide_Action(const Cocix*, const bool = false);

	private:
		void charge();
};

#endif