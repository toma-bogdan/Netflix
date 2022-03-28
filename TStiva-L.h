/*TOMA Bogdan-Nicolae-313CB*/
/*-- TStiva-V.h -- elementele stivei sunt memorate intr-o lista simplu inlantuita --*/
#include "TStiva.h"
#include "tlista.h"

#ifndef _STIVA_VECTOR_
#define _STIVA_VECTOR_

typedef struct
{ 
	size_t 	dime; 		/* dimensiunea unui element al stivei 			*/
	TLista 	vf; 		/* varful stivei 								*/
} TStiva, *ASt;

/*- macrodefinitii - acces campuri */
#define DIME(a) (((ASt)(a))->dime)
#define VF(a) 	(((ASt)(a))->vf)

/*- teste -*/
/* verifica daca doua stive au elemente de dimensiuni diferite */
#define DIMDIF(s,d)	(DIME(s) != DIME(d))
/* verifica daca o stiva este vida */
#define VIDA(a)  	(VF(a) == NULL)

#endif