/* Tararache Crina-Andreea, grupa 314CB */
/*-- functiiCoada-V.c -- elementele cozii sunt memorate intr-un vector --*/
#include "TCoada.h"

typedef struct
{ 
	int ID; //ID-ul serialului
	char *nume; // numele serialului
	float rating; //ratingul serialului
	int nr_sezoane;
	TCoada* coada_sezoane;
}TSerial; 


/* creeaza coada vida cu elemente de dimensiune d; */
void* InitQ(size_t d) //ok
{ 
	AQ aux;
	aux = (AQ)malloc(sizeof(TCoada));
	if(!aux) return NULL;
	aux->dime = d;
	aux->sc = NULL;
	aux->ic = NULL;
	return (void*)aux;
}

/* inserare in coada vida */
int InsQ_vida(void *a, void *ae) //ok
{
	ACel aux;
	aux = (ACel)malloc(sizeof(TCel));
	if(!aux) return 0;
	aux->info = ae; //ae e alocata per element
	aux->urm = NULL;
	IC(a) = aux; 
	SC(a) = aux;
	return 1;
}

/* inserare in coada nevida */
int InsQ_nevida(void* a, void *ae) //ok
{
	ACel aux;
	aux = (ACel)malloc(sizeof(TCel));
	if(!aux) return 0;
	aux->info = ae; //ae e alocata per element
	aux->urm = NULL;
	SC(a)->urm = aux;
	SC(a) = aux;
	return 1;
}

/* afisare coada */
void Afisare_coada(void* a, FILE* output, TF1 af)
{
	if(IC(a) == NULL) //coada vida
		fprintf(output, "[].\n");
	else
	{
		ACel aux;
		aux = IC(a);
		fprintf(output, "[");
		while(aux != NULL)
		{
			af(aux->info, output);
			aux = aux->urm;
			if(aux == NULL)
				fprintf(output, "].\n");
			else
				fprintf(output, ", ");
		}
	}
} 




 




