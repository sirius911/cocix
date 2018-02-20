#ifndef DEF_CLASS_CORTEX_ADULTE_MALE
#define DEF_CLASS_CORTEX_ADULTE_MALE

#include "Cortex_Adulte.h"
#include "../Cocix.h"


class Cortex_Adulte_Male : public Cortex_Adulte{
public:
		Cortex_Adulte_Male();
		void gestion_Etat(Cocix*, const bool verbal = false);
		bool decide_Desire(Cocix*, const bool verbal = false);

};


#endif