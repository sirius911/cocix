#ifndef DEF_CLASS_SE_RECHAUFFER
#define DEF_CLASS_SE_RECHAUFFER
#include "Actions.h"

#include "../Cocix.h"

class Se_Rechauffer : public Actions
{
	public:
		Se_Rechauffer();
		Se_Rechauffer(const short, const short);
		

		void go(Cocix*,bool=false);
		bool valide_Action(const bool = false);

	private:
		void charge();
		short case_presence;
		short case_naissance;
};

#endif