#ifndef DEF_CLASS_CORTEX_ADULTE
#define DEF_CLASS_CORTEX_ADULTE

#include "Cortex.h"
#include "../Cocix.h"


class Cortex_Adulte : public Cortex{
public:
		Cortex_Adulte();
		void gestion_Etat(Cocix*, const bool verbal = false);
		bool decide_Desire(Cocix*, const bool verbal = false);

};


#endif