/*TOMA Bogdan-Nicolae-313CB*/
/*-- TCoada.h --- tipul coada ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "thash.h"


#ifndef _FUNCTII_
#define _FUNCTII_
  typedef void (*TF1)(void *);
  typedef void (*TF3)(void *, FILE* out);
  typedef int (*TF2)(const void *, const void *);
#endif

#ifndef COADA
#define COADA

void* InitQ(size_t d); /* creeaza coada vida cu elemente de dimensiune d; */
void AfiQ( TF3 AfiElem, void *a, FILE* out);
int IntrQ(void* a, void* ae); /* adauga element la sfarsitul cozii */
int ExtrQ(void* c, void* ae, TF1 fel); /* extrage primul element din coada la adresa ae */
int PrimQ(void* a, void* ae); /* copiaza primul element din coada la adresa ae */
int VidaQ(void* a);           /* test coada vida */
int NrEQ(void* a);         /* numarul de elemente din coada */
size_t DimEQ(void* a);        /* dimensiunea elementelor din coada */
void* CautaCoada(void* c, char* nume, int* ok);//returneaza serialul cautat, stergandu-l din lista
void add_sezQ(void* c, void* sezon, char* nume, int* ok, FILE* out);//adauga inca o coada de episoade la serialul cu numele dat
void ResetQ(void* a, TF1 fel);         /* transforma coada in coada vida */
void DistrQ(void* aa, TF1 fel);
void DistrSerial(void *serial);

int MutaQ(void *ad, void *as);  	/* muta in coada dest. primul element din sursa */

#endif
