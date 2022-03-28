/*TOMA Bogdan-Nicolae-313CB*/
/*-- TCoada-V.h -- elementele cozii sunt memorate intr-o lista simplu inlantuita --*/
#include "TCoada.h"
#include "tlista.h"

#ifndef _COADA_VECTOR_
#define _COADA_VECTOR_

typedef struct
{ 
	size_t 	dime; 		/* dimensiunea unui element din coada  		*/
	TLista 	ic; 		/* adresa primului element din coada 		*/
	TLista 	sc; 		/* adresa de sfarsit a cozii 				*/
} TCoadaV, *AQV;

/*- macrodefinitii - acces campuri -*/
#define IC(a) 	(((AQV)(a))->ic)
#define SC(a) 	(((AQV)(a))->sc)
#define DIME(a) (((AQV)(a))->dime)

/*- teste si prelucrari -*/
/* verifica daca doua cozi au elemente de dimensiuni diferite 			*/
#define DIMDIF(s,d) 	(DIME(s) != DIME(d))  
/* verifica daca o coada este vida 										*/
#define VIDA(a) 		(IC(a) == NULL && SC(a) == NULL)

#endif
