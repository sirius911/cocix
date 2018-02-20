#ifndef DEF_CLASS_CORTEX_BEBE
#define DEF_CLASS_CORTEX_BEBE

#include "Cortex.h"
#include "../Cocix.h"


class Cortex_Bebe : public Cortex{
public:
		Cortex_Bebe();
		void gestion_Etat(Cocix*, const bool verbal = false);
		bool decide_Desire(Cocix*, const bool verbal = false);

};


#endif