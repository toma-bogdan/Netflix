/*TOMA Bogdan-Nicolae-313CB*/
#include <stdio.h>
#include "tlista.h"
#include <string.h>
#include "thash.h"
#include "TCoada.h"
#include "TCoada-L.h"
#include "TStiva.h"

void AfiSerial(void *a,FILE *out)
{
	fprintf(out,"(%s, %0.1f)",((Tserial*)a)->nume,((Tserial*)a)->rating);
}
int cmpSerial(void *e1, void *e2)
{
	Tserial * serial1 = (Tserial*) e1;
    Tserial * serial2 = (Tserial*) e2;

	if(strcmp(serial1->nume,serial2->nume) != 0){
    	return 0;
    }
    return 1;
}

Tserial* creare_serial(){
	//Cream serialul:
	int i,j;
	Tserial *serial = malloc(sizeof(Tserial));
	serial->nume = malloc(33*sizeof(char));

	char *ID = strtok(NULL," ");
	serial->ID = atoi(ID);

	char *nume = strtok(NULL," ");
	strcpy(serial->nume,nume);

	char *rating = strtok(NULL," ");
	serial->rating = atof(rating);

	char *nrsez = strtok(NULL," ");
	serial->nr_sezoane = atoi(nrsez);

	//Cream coada de sezoane
	serial->sezoane = InitQ(sizeof(TCoadaV));
	for(i = 0; i < serial->nr_sezoane; i++)
	{
		char *nr_episoade = strtok(NULL," ");
		int nr = atoi(nr_episoade);

		//Cream coada de episoade apoi o adaugam la coada de sezoane:		
		void* c_episoade = InitQ(sizeof(int));
		for(j = 0; j < nr; j++)
		{
			char *durata_str =strtok(NULL," ");
			int durata = atoi(durata_str);
			int rez;
			rez = IntrQ(c_episoade,&durata);
			if(!rez)
				return NULL;
		}
		int r;
		r = IntrQ(serial->sezoane,c_episoade);
		if(!r)
			return NULL;
		free(c_episoade);
	}

	return serial;
}
void* crearesezon()
{
	void* sezon = InitQ(sizeof(int));
	char* nr = strtok(NULL," ");
	int nr_episoade = atoi(nr), i;

	for(i = 0; i < nr_episoade; i++)
	{
		char* durata_str = strtok(NULL," ");
		int durata = atoi(durata_str);
		IntrQ(sezon,&durata);
	}
	return (void*)sezon;
}
int watch(void* a,int* d, char* nume, FILE* out)
{
	void* sezoane = ((Tserial*)a)->sezoane;
	void* episoade = InitQ(sizeof(int));
	int ok = 0, durata_ep;
	while(VidaQ(sezoane) == 0)
	{
		ExtrQ(sezoane,episoade,free);

		while(VidaQ(episoade) == 0){
			ExtrQ(episoade,&durata_ep,free);
			if(*d > durata_ep){
				*d = *d - durata_ep;
			}else
			{
				durata_ep = durata_ep - *d;
				*d = -1;
				ok = 1;
				break;
			}
		}
		if(ok == 1)
			break;
	}

	if(*d < 0 && durata_ep != 0){
		IntrQ(episoade,&durata_ep);
	}
	if(VidaQ(episoade) == 0){
		IntrQ(sezoane,episoade);
	}
	free(episoade);

	if(VidaQ(sezoane)){
		fprintf(out,"Serialul %s a fost vizionat integral.\n",nume);
		return 1;
	}
	return 0;
}
void add_sezS(void *s, void* sezon, char* nume, int* ok, FILE* out)
{
    if(VidaS(s)){
		return ;
    }
    void* aux = InitS(sizeof(Tserial));
    void* ae = malloc(sizeof(Tserial));
    while(VidaS(s) == 0)
    {
        Pop(s,ae,free);
        if(strcmp(((Tserial*)ae)->nume, nume) == 0){
			IntrQ(((Tserial*)ae)->sezoane,sezon);
            fprintf(out,"Serialul %s are un sezon nou.\n",nume);
            *ok = 1;
        }
        Push(aux,ae);
    }
    RastoarnaS(s,aux);
    DistrS(aux,free);
    free(ae);
}
int main(int argc, char **argv)
{   
	char filename1[50], filename2[50];

	strcpy(filename1,argv[1]);
    strcpy(filename2,argv[2]);

	FILE *in = fopen(filename1,"rt");
    if(in == NULL){
        printf("eroare deschidere fisier");
        return -1;
    }
    FILE *out = fopen(filename2,"wr");
    if(out == NULL){
        printf("eroare deschidere fisier");
        return -1;
    }

	TH *h = NULL;
    h = (TH *)IniTH(4);
	void *c_later = InitQ(sizeof(Tserial));
	void *s_watch = InitS(sizeof(Tserial));
	void *s_history = InitS(sizeof(Tserial));

	char * line = NULL;
	size_t len = 0;

    while (getline(&line, &len, in) != -1){
        char * comanda = strtok(line, " ");
        if(comanda[strlen(comanda) - 1] == '\n'){
               comanda[strlen(comanda) - 1] = '\0';
        }

		if(strcmp(comanda,"add") == 0){
			Tserial* serial = creare_serial();

			InsTH(h,serial,cmpSerial,serial->ID,out);
		}

		if(strcmp(comanda,"add_sez") == 0){
			char* nume_sez = strtok(NULL," ");
			void* sezon = crearesezon();
			int ok = 0;
			add_sezS(s_watch,sezon,nume_sez,&ok,out);
			if(ok == 0)
				add_sezQ(c_later,sezon,nume_sez,&ok,out);
			if(ok == 0)
				add_sezTH(h,sezon,nume_sez,out);
			free(sezon);
		}

		if(strcmp(comanda,"show") == 0){
			char *N = strtok(NULL," ");

			if(N[0] == '1' || N[0] == '2' || N[0] == '3'){
				int n = atoi(N);
				showTH(h,AfiSerial,out,n);
			}
			if(strcmp(N,"top10\n") == 0 || strcmp(N,"top10") == 0){
				showTop10(h,AfiSerial,out);
			}
			if(strcmp(N,"later\n") == 0 || strcmp(N,"later") == 0){
				AfiQ(AfiSerial,c_later,out);
			}
			if(strcmp(N,"watching\n") == 0 || strcmp(N,"watching") == 0){
				AfiStiva(AfiSerial,s_watch,out);
			}
			if(strcmp(N,"history\n") == 0 || strcmp(N,"history") == 0){
				AfiStiva_history(AfiSerial,s_history,out);
			}
		}

		if(strcmp(comanda,"add_top") == 0){

			Tserial* serial = creare_serial();
			InsTop10(h,serial,cmpSerial,serial->ID,out);
			showTop10(h,AfiSerial,out);
		}
		if(strcmp(comanda,"later") == 0){
			char* nume_later = strtok(NULL," ");
			if(nume_later[strlen(nume_later) - 1] == '\n')
               nume_later[strlen(nume_later) - 1] = '\0';
        
			void* ae = findTH(h,nume_later);
			IntrQ(c_later,ae);
			fprintf(out,"Serialul %s se afla in coada de asteptare pe pozitia %d.\n",((Tserial*)ae)->nume,NrEQ(c_later));
			free(ae);
		}
		if(strcmp(comanda,"watch") == 0){
			char *nume_watch = strtok(NULL," ");
			if(nume_watch[strlen(nume_watch) - 1] == '\n')
               nume_watch[strlen(nume_watch) - 1] = '\0';
			char* durata_str = strtok(NULL," ");
			int durata = atoi(durata_str);

			int ok = 0;
			void * ae;
			ae = CautaStiva(s_watch,nume_watch,&ok);

			if(ok == 0){
				free(ae);
				ae = CautaCoada(c_later,nume_watch,&ok);
			}
			if(ok == 0){
				free(ae);
				ae = findTH(h,nume_watch);
			}
			int rez = watch(ae,&durata,nume_watch,out);
			if(rez){
				Push(s_history,ae);
			}else{
				Push(s_watch,ae);
			}
			
			free(ae);
		}
	}

	free(line);
	DistrS(s_watch,DistrSerialS);
	DistrS(s_history,DistrSerialS);
	DistrQ(c_later,DistrSerial);
	DistrTH(&h,DistrSerial);
	fclose(in);
	fclose(out);

    return 0;
}
