/* Tararache Crina-Andreea, grupa 314CB */
/*--- functiiLista.c -- operatii de baza pentru lista simplu inlantuita generica---*/
#include "TLista.h"

/* inserare la inceput */
int InsLG(TLG* aL, void* ae) 
{
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0;
	aux->info = ae;
	aux->urm = *aL;
	*aL = aux;
	return 1;
}

/* inserare la sfarsit */
int InsSF(TLG l, void* ae)
{
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0;
	for(; l->urm != NULL; l = l->urm);
	aux->info = ae;
	l->urm = aux;
	aux->urm = NULL;
	return 1;
}

void EliminaLG(TLG l)
{
	TLG aux = l;
	while(aux->urm->urm != NULL)
	{
		aux = aux->urm;
	}
	aux->urm = NULL;
}

TLG AlocCelula(void *x) 
{
	TLG aux = (TLG) malloc(sizeof(TCelulaG));
	if(!aux) return 0;
	aux->info = x;
	aux->urm = NULL;
	return aux;
} 

/* afisare lista */
void Afisare(TLG* aL, TF afiEL, FILE* output)
{
	if(*aL == NULL)
		fprintf(output, "[].\n");
	else
	{
		fprintf(output, "[");
		for(; *aL; aL = &(*aL)->urm) {
			afiEL((*aL)->info, output);
    
		if((*aL)->urm == NULL)
			fprintf(output, "].\n");
		else
			fprintf(output, ", ");
		}
	}
}

/* numarul de elemente din lista */
int LungimeLG(TLG *l)
{
	int lungime = 0;
	TLG p = *l;
	for( ; p != NULL; p = p->urm)
		lungime++;
	return lungime;
}
