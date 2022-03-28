/*TOMA Bogdan-Nicolae-313CB*/

#include "tlista.h"
#include "thash.h"
#include "TCoada-L.h"

int InsL(TLista *l, void * e, FILE* out)
{
    TLista aux = malloc(sizeof(TCelula));
    if(!aux)
        return 0;

    aux->info = e;
    aux->urm = NULL;
    int poz = 1;
    //Inserare in lista vida:
    if(*l == NULL){
        *l = aux;
        fprintf(out,"Serialul %s a fost adaugat la pozitia %d.\n",((Tserial*)e)->nume,poz);
        return 1;
    }
    TLista p, ant = NULL, u;
    for(p = *l; p->urm != NULL; p = p->urm){;}
	u = p;

    for(p = *l; p != NULL; ant = p, p = p->urm)
    {
        poz++;
        if( ((Tserial*)p->info)->rating < ((Tserial*)aux->info)->rating )
        {
            if(ant == NULL){
                aux->urm = *l;
                *l = aux;
            }else
            {
                aux->urm = p;
                ant->urm = aux;
            }
            fprintf(out,"Serialul %s a fost adaugat la pozitia %d.\n",((Tserial*)e)->nume,poz-1);
            return 1;
        }
        if( ((Tserial*)p->info)->rating == ((Tserial*)aux->info)->rating )
        {
            while(p != NULL && ((Tserial*)p->info)->rating == ((Tserial*)aux->info)->rating){
                if( strcmp(((Tserial*)p->info)->nume, ((Tserial*)aux->info)->nume) >= 0){
                    //aux,p
                    if(ant == NULL){
                        aux->urm = *l;
                        *l = aux;
                    }else
                    {
                        aux->urm = p;
                        ant->urm = aux;
                    }
                    fprintf(out,"Serialul %s a fost adaugat la pozitia %d.\n",((Tserial*)e)->nume,poz-1);
                    return 1;
                }
                ant = p;
                p = p->urm;
                poz++;
            }
            if(p == NULL){
                u->urm = aux;
                fprintf(out,"Serialul %s a fost adaugat la pozitia %d.\n",((Tserial*)e)->nume,poz-1);
                return 1;
            }
            else
            {
                ant->urm = aux;
                aux->urm = p;
                fprintf(out,"Serialul %s a fost adaugat la pozitia %d.\n",((Tserial*)e)->nume,poz-1);
                return 1;
            }
        }
    }
    u->urm = aux;
    fprintf(out,"Serialul %s a fost adaugat la pozitia %d.\n",((Tserial*)e)->nume,poz);
    return 1;
}
int InsLT10(TLista *l, void *e, int poz, FILE* out)
{
    TLista aux = malloc(sizeof(TCelula));
    if(!aux)
        return 0;

    aux->info = e;
    aux->urm = NULL;
    //Inserare lista vida:
    if(*l == NULL)
    {
        aux->urm = *l;
        *l = aux;
        return 1;
    }
    int i = 1,ok = 0;
    TLista p, u,ant,ant_u;
    for(p = *l, ant = NULL; p != NULL;ant = p, p = p->urm){
        if(poz == i)
        {
            if(poz == 1)
            {
                aux->urm = *l;
                *l = aux;
                ok = 1;
            }else
            {
                aux->urm = p;
                ant->urm = aux;
                ok = 1;
            }
            
        }
        i++;
    }
    for(p = *l,ant = NULL; p->urm != NULL;ant = p, p = p->urm){;}
    ant_u = ant;
    u = p;
    
    if(ok == 0){
        u->urm = aux;
    }

    if(i > 10)
    {
        ant_u->urm = NULL;
        DistrSerial(u->info);
        free(u);
    }
    return 1;
}
