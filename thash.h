/*TOMA Bogdan-Nicolae-313CB*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tlista.h"


#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*,FILE *out);     /* functie afisare un element */
typedef int (*TFHash)(void*,size_t);  /*functie hash*/
typedef void (*TF5)(void*);   /*functie eliberare un element*/

typedef struct
{
    size_t M;
    TLista *v;
} TH;

typedef struct
{
    int ID;
    char *nume;
    float rating;
    int nr_sezoane;
    void *sezoane;
}Tserial;


TH* IniTH(size_t M);
void AfiTH(TH* ah, TF afiEl,FILE* out);
int InsTH(TH*a, void* ae, TFCmp f,int cod,FILE* out);
int InsTop10(TH*a, void* ae, TFCmp f,int poz,FILE* out);
void* findTH(TH* h,char* nume);
int showTH(TH *h, TF afiel, FILE *out, int n);
int showTop10(TH *h, TF afiel, FILE *out);
void add_sezTH(TH* h, void* sezon, char* nume, FILE* out);
void DistrTH(TH** ah, TF5 fe);

#endif