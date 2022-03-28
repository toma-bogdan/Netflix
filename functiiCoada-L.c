/*TOMA Bogdan-Nicolae-313CB*/
/*-- functiiCoada-V.c -- elementele cozii sunt memorate intr-o lista --*/
#include "TCoada-L.h"
#include "thash.h"
/* creeaza coada vida cu elemente de dimensiune d;*/
void* InitQ(size_t d)
{ 
	AQV a = (AQV)malloc(sizeof(TCoadaV));  	/* adresa descriptor alocat */
  	if (!a) 
		return NULL;           

 	a->dime = d;
    a->ic = NULL;
    a->sc = NULL;

  	return (void*)a;
}
int IntrQ(void* c, void* ae)
{
    TLista aux;
    aux = (TLista)malloc(sizeof(TCelula));
    if(!aux)
        return 0;
    
    aux->info = malloc(((AQV)c)->dime);
    memcpy(aux->info,ae,((AQV)c)->dime);
    aux->urm = NULL;
    if(VidaQ(c))
    {
        IC(c) = aux;
        SC(c) = aux;
        return 1;
    }

    SC(c)->urm = aux;
    SC(c) = aux;
    return 1;
}
int ExtrQ(void* c, void* ae, TF1 fel)
{
    if(VidaQ(c)){
        printf("coada e vida\n");
        return 0;
    }
    TLista aux = IC(c);
    IC(c) = aux->urm;

    memcpy(ae,aux->info,DimEQ(c));
    fel(aux->info);
    free(aux);

    if(IC(c) == NULL)
        SC(c) = NULL;

    return 1;
}
/* copiaza primul element din coada la adresa ae */
int PrimQ(void *a, void *ae)  
{ 
	if(VIDA(a)) 
		return 0;
  	memcpy(ae, IC(a)->info, DIME(a));  /* copiaza elementul de la inceputul cozii */
	return 1;
}
void* CautaCoada(void* c, char* nume, int* ok)
{
    if(VIDA(c)){
		return 0;
    }
    void* aux = InitQ(DimEQ(c));
    void* ae = malloc(DimEQ(c));
    void* r = malloc(DimEQ(c));
    while(VidaQ(c) == 0)
    {
        PrimQ(c,ae);
        if(strcmp(((Tserial*)ae)->nume, nume) == 0){
            ExtrQ(c,r,free);
            *ok = 1;
        }else
        {
            ExtrQ(c,ae,free);
            IntrQ(aux,ae);
        }
        
    }
    MutaQ(c,aux);
    DistrQ(aux,free);
    free(ae);
    return (void*)r;
}
void add_sezQ(void* c, void* sezon, char* nume, int* ok, FILE* out)
{
    if(VIDA(c)){
		return ;
    }
    void* aux = InitQ(DimEQ(c));
    void* ae = malloc(DimEQ(c));
    while(VidaQ(c) == 0)
    {
        ExtrQ(c,ae,free);

        if(strcmp(((Tserial*)ae)->nume, nume) == 0){
            IntrQ(((Tserial*)ae)->sezoane,sezon);
            fprintf(out,"Serialul %s are un sezon nou.\n",nume);
            *ok = 1;
        }
        IntrQ(aux,ae);
        
    }
    MutaQ(c,aux);
    DistrQ(aux,free);
    free(ae);
}
/* afiseaza stiva */
void AfiQ( TF3 AfiElem, void *a, FILE* out)
{
    fprintf(out,"Categoria later: [");
    TLista p = IC(a);
    for(;p != NULL; p = p->urm){
		AfiElem(p->info,out);
        if(p->urm != NULL)
            fprintf(out,", ");
    }
  	fprintf(out,"].\n");
}

int NrEQ(void* a)
{
    int nr = 0;
    TLista p = IC(a);
    for(;p != NULL; p = p->urm)
        nr++;
    return nr;
}
/* test coada vida */
int VidaQ(void *a)         
{ 
	return VIDA(a); 
}
/* dimensiunea elementelor din coada */
size_t DimEQ(void *a)      
{ 
	return DIME(a); 
}
int MutaQ(void *ad, void *as)
{
    if(VIDA(as)){
		return 0;
    }
    void *ae = malloc(DimEQ(as));
    while(VidaQ(as) == 0)
    {
        ExtrQ(as,ae,free);
        IntrQ(ad,ae);
    }
    free(ae);
    return 1;
}
void ResetQ(void* a,TF1 fel)
{
    TLista aux;
    while(IC(a))
        {
        aux = IC(a);
        IC(a) = aux->urm;
        fel(aux->info);
        free(aux);
    }
    IC(a) = NULL;
    SC(a) = NULL;
}

void DistrQ(void* aa, TF1 fel)
{
    TLista aux;
    while(IC(aa))
        {
        aux = IC(aa);
        IC(aa) = aux->urm;
        aux->urm = NULL;
        fel(aux->info);
        free(aux);
    }
    IC(aa) = NULL;
    SC(aa) = NULL;
	free(aa);
  	aa = NULL;
}
void DistrSerial(void *serial)
{
    void *sezoane = ((Tserial*)serial)->sezoane;
    TLista aux;
    while(IC(sezoane))
    {
        aux = IC(sezoane);
        IC(sezoane) = aux->urm;
        aux->urm = NULL;
        DistrQ(aux->info,free);
        free(aux);
    }
    IC(((Tserial*)serial)->sezoane) = NULL;
    SC(((Tserial*)serial)->sezoane) = NULL;
	free(((Tserial*)serial)->sezoane); 
  	((Tserial*)serial)->sezoane = NULL;
    free(((Tserial*)serial)->nume);
    free(serial);
}
