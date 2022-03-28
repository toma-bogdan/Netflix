/*TOMA Bogdan-Nicolae-313CB*/
/*-- functiiStiva-V.c -- elementele stivei sunt memorate intr-un vector --*/
#include "TStiva-L.h"
#include "thash.h"
/* creeaza stiva vida cu elemente de dimensiune d;*/
void *InitS(size_t d)      
{ 
	ASt s;
    s = (ASt)malloc(sizeof (TStiva));			/* adresa descriptor alocat */
  	if (!s) 
		return NULL;


  	s->dime = d;
    s->vf = NULL;

  	return (void *)s;
}

/* pune element in varful stivei */
int Push(void *s, void *ae)     
{ 
    TLista aux;
    aux = (TLista)malloc(sizeof(TCelula));
    if(!aux)
        return 0;
    
    aux->info = malloc(((ASt)s)->dime);
    memcpy(aux->info,ae,((ASt)s)->dime);
    aux->urm = ((ASt)s)->vf;
    ((ASt)s)->vf = aux;

  	return 1;
}

/* extrage elementul din varful stivei la adresa ae */
int Pop(void *s, void *ae,TF1 fel)      
{ 
	TLista aux;
	aux = ((ASt)s)->vf;
    if(aux == NULL)
        return 0;
    
    memcpy(ae,aux->info,((ASt)s)->dime);
    ((ASt)s)->vf = aux->urm;
    fel(aux->info);
    free(aux);

  	return 1;
}

/* copiaza elementul din varful stivei la adresa ae */
int Top(void *a, void *ae)    
{ 
	if(VIDA(a)) 
		return 0;
  	memcpy (ae, VF(a)->info, DIME(a));   /* copiaza elementul din varful stivei */
  	return 1;
}

void AfiStiva(TF3 AfiElem, void *a, FILE* out)
{
    fprintf(out,"Categoria watching: [");
    TLista p = ((ASt)a)->vf;
    for(;p != NULL; p = p->urm){
		AfiElem(p->info,out);
        if(p->urm != NULL)
            fprintf(out,", ");
    }
    fprintf(out,"].\n");
}
void AfiStiva_history(TF3 AfiElem, void *a, FILE* out)
{
    fprintf(out,"Categoria history: [");
    TLista p = ((ASt)a)->vf;
    for(;p != NULL; p = p->urm){
		AfiElem(p->info,out);
        if(p->urm != NULL)
            fprintf(out,", ");
    }
    fprintf(out,"].\n");
}
/* test stiva vida */
int VidaS(void *a)               
{ 
	return VF(a) == NULL; 
}
/* dimensiunea elementelor din stiva */
size_t DimES(void *a)           
{ 
	return DIME(a); 
}
int NrES(void* a)
{
    int nr = 0;
    TLista p = VF(a);
    for(;p != NULL; p = p->urm)
        nr++;
    return nr;
}
void ResetS(void* a,TF1 fel)
{
    TLista aux;
    while(VF(a))
        {
        aux = VF(a);
        VF(a) = aux->urm;
        fel(aux->info);
        free(aux);//!
    }
    VF(a) = NULL;
}
int RastoarnaS(void* ad, void* as)
{
    if(VIDA(as)){
		return 0;
    }
    void* ae = malloc(DimES(as));
    while(VidaS(as) == 0)
    {
        Pop(as,ae,free);
        Push(ad,ae);
    }
    free(ae);
    return 1;
}
void* CautaStiva(void *s, char* nume, int* ok)
{
    if(VIDA(s)){
		return 0;
    }
    void* aux = InitS(DimES(s));
    void* ae = malloc(DimES(s));
    void* r = malloc(DimES(s));
    while(VidaS(s) == 0)
    {
        Top(s,ae);
        if(strcmp(((Tserial*)ae)->nume, nume) == 0){
            Pop(s,r,free);
            *ok = 1;
        }else
        {
            Pop(s,ae,free);
            Push(aux,ae);
        }
    }
    RastoarnaS(s,aux);
    DistrS(aux,free);
    free(ae);
    return (void*)r;
}

void DistrS(void* aa, TF1 fel)
{
    TLista aux;
    while(VF(aa))
        {
        aux = VF(aa);
        VF(aa) = aux->urm;
        aux->urm = NULL;
        fel(aux->info);
        free(aux);
    }
    VF(aa) = NULL; 		/* elibereaza spatiul ocupat de vector */
	free(aa); 			/* elibereaza spatiul alocat pentru descriptor */
  	aa = NULL;
}
void DistrSerialS(void *serial)
{
    void *sezoane = ((Tserial*)serial)->sezoane;
    TLista aux;
    while(VF(sezoane))
        {
        aux = VF(sezoane);
        VF(sezoane) = aux->urm;
        aux->urm = NULL;
        DistrS(aux->info,free);
        free(aux);
    }
    VF(((Tserial*)serial)->sezoane) = NULL;
	free(((Tserial*)serial)->sezoane); 
  	((Tserial*)serial)->sezoane = NULL;
    free(((Tserial*)serial)->nume);
    free(serial);
}
