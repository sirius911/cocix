#ifndef DEF_CLASS_CORTEX_OEUF
#define DEF_CLASS_CORTEX_OEUF

#include "Cortex.h"
#include "../Cocix.h"


class Cortex_Oeuf : public Cortex{
public:
		Cortex_Oeuf();
		Cortex_Oeuf(bool);
		void gestion_Etat(Cocix*, const bool verbal = false);
		bool decide_Desire(Cocix*, const bool verbal = false);

};


#endif