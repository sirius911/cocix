#ifndef DEF_CLASS_CORTEX_ADULTE_FEMELLE
#define DEF_CLASS_CORTEX_ADULTE_FEMELLE

#include "Cortex_Adulte.h"
#include "../Cocix.h"


class Cortex_Adulte_Femelle : public Cortex_Adulte{
public:
		Cortex_Adulte_Femelle();
		void gestion_Etat(Cocix*, const bool verbal = false);
		bool decide_Desire(Cocix*, const bool verbal = false);

};


#endif