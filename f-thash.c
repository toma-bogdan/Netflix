/*TOMA Bogdan-Nicolae-313CB*/
/*  functii-tabHash.c - functii tabela hash */
#include "TCoada-L.h"
#include "thash.h"

TH* IniTH(size_t M)
{
    TH* h = (TH *) calloc(sizeof(TH), 1);
    if (!h) {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->v = (TLista *) calloc(M, sizeof(TLista));
    if(!h->v) {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    return h;
}
int InsTH(TH*a, void* ae, TFCmp f,int cod,FILE* out)
{
    int rez;
    TLista el;

    for(el = a->v[cod - 1]; el != NULL; el = el->urm) {
        if (f(el->info, ae) == 1)
            return 0;
    }
    rez = InsL(a->v+cod-1, ae,out);
    return rez;
}
int InsTop10(TH*a, void* ae, TFCmp f,int poz,FILE* out)
{
    int rez;
    TLista el;

    for(el = a->v[3]; el != NULL; el = el->urm) {
        if (f(el->info, ae) == 1)
            return 0;
    }
    rez = InsLT10(a->v+3, ae, poz, out);
    return rez;
}
void* findTH(TH* h,char* nume)
{
    TLista p, el,ant;
    void * ae;
    int i, ok = 0;
    for(i = 0; i < h->M; i++) {
        p = h->v[i];  
        if(p) {
            for(ant = NULL, el = p; el != NULL;ant = el, el = el->urm){
                if(strcmp(((Tserial*)el->info)->nume, nume) == 0){
                    
                    ae = el->info;

                    if(ant == NULL){
                        TLista aux = el;
                        h->v[i] = h->v[i]->urm;
                        free(aux);
                    }
                    else
                    {
                        ant->urm = el->urm;
                        free(el);
                    }
                    ok = 1;
                    break;
                }
            }
        }
        if(ok == 1)
            break;
    }
    return (void*)ae;  
}
void add_sezTH(TH* h, void* sezon, char* nume, FILE* out)
{
    TLista p, el;
    int i, ok = 0;
    for(i = 0; i < h->M; i++) {
        p = h->v[i];  
        if(p) {
            for(el = p; el != NULL; el = el->urm){
                if(strcmp(((Tserial*)el->info)->nume, nume) == 0){
                    IntrQ(((Tserial*)el->info)->sezoane,sezon);
                    fprintf(out,"Serialul %s are un sezon nou.\n",nume);
                    ok = 1;
                }
            }
        }
        if(ok == 1)
            break;
    }
}
int showTH(TH *h, TF afiel, FILE *out, int n)
{
    TLista p;
    p = h->v[n-1];

    fprintf(out,"Categoria %d: [",n);
    for(; p != NULL; p = p->urm){
        afiel(p->info,out);
        if(p->urm != NULL)
            fprintf(out,", ");
    }
    fprintf(out,"].\n");
    return 1;
}
int showTop10(TH *h, TF afiel, FILE *out)
{
    TLista p;
    p = h->v[3];

    fprintf(out,"Categoria top10: [");
    for(; p != NULL; p = p->urm){
        afiel(p->info,out);
        if(p->urm != NULL)
            fprintf(out,", ");
    }
    fprintf(out,"].\n");
    return 1;
}
void DistrTH(TH** ah, TF5 fe)
{
    TLista * p, el, aux;

    //parcurgere cu pointeri
    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) {
        //daca exista elemente corespunzatoare acestui hash
        //eliberam info din celula si apoi eliberam celula
        for(el = *p; el != NULL; ) {
            aux = el;
            el = el->urm;
            fe(aux->info);
            free(aux);
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}