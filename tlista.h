/*TOMA Bogdan-Nicolae-313CB*/
/*-- tlista.h --- LISTA SIMPLU INLANTUITA cu elemente de tip intreg ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#ifndef _LISTA_SIMPLU_INLANTUITA_
#define _LISTA_SIMPLU_INLANTUITA_

typedef struct celula
{ void* info;
  struct celula * urm;
} TCelula, *TLista; /* tipurile Celula, Lista */

#define VidaL(L) ((L) == NULL)

/*-- operatii elementare --*/

TLista AlocCelula(int);          /* adresa celulei create sau NULL */
void   DistrugeL (TLista*);       /* elimina toate celulele din lista */
int InsL(TLista *l, void * e, FILE *out);
int InsLT10(TLista *l, void *e, int poz, FILE* out);
void AfisareL (TLista L);



#endif

