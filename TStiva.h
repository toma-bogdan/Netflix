/*TOMA Bogdan-Nicolae-313CB*/
/*-- TStiva.h --- tipul stiva ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef _FUNCTII_
#define _FUNCTII_
  typedef void (* TF1)(void *);
  typedef void (*TF3)(void *, FILE* out);
  typedef int (* TF2)(const void *, const void *);
#endif

#ifndef STIVA
#define STIVA

void* InitS(size_t d);    /* initializeaza stiva cu elem.de dimensiune d; */
void AfiStiva(TF3 AfiElem, void *a,FILE *out);//afiseaza stiva watching
void AfiStiva_history(TF3 AfiElem, void *a, FILE* out);//afiseaza stiva history
int Push(void* a, void* ae);  /* pune element in varful stivei */
int Pop (void* a, void* ae,TF1 fel);  /* extrage elementul din varful stivei la adresa ae */
int Top (void* a, void* ae);  /* copiaza elementul din varful stivei la adresa ae */
int VidaS(void* a);           /* test stiva vida */
int NrES (void* a);        /* numarul de elemente din stiva */
size_t DimES(void* a);        /* dimensiunea elementelor din stiva */
void ResetS (void* a,TF1 fel);        /* transforma stiva in stiva vida */
void DistrS (void* aa, TF1 fel);      /* elibereaza intregul spatiu ocupat de stiva */
void DistrSerialS(void *serial);//eliberaza spatiul ocupat de un serial
void* CautaStiva(void *s, char* nume, int* ok);//cauta si intoarce serialul cu numele dat, extragandu-l  din stiva
int RastoarnaS(void* ad, void* as); /* suprapune inversul sursei peste destinatie */

#endif
