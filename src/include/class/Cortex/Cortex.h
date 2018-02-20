#ifndef DEF_CLASS_CORTEX
#define DEF_CLASS_CORTEX

#include "../../constantes.h"
#include "../Cocix.h"


using namespace std;

class Cocix;	// pour éviter la récurence d'un #include "Cocix.h"


class Cortex{

	protected:
		char nom[30];	
	public:
		Cortex();
		virtual void gestion_Etat(Cocix *, const bool verbal = false);
		virtual bool decide_Desire(Cocix *, const bool verbal = false);

		char* get_nom();

};


#endif