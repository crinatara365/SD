/* Tararache Crina-Andreea, grupa 314CB */
/*-- functiiStiva-V.c -- elementele stivei sunt memorate intr-o lista generica simplu inlantuita --*/
#include "TStiva.h"

/* creeaza stiva vida cu elemente de dimensiune d */
void *InitS(size_t d)       
{
	ASt s;
	s = (ASt)malloc(sizeof(TStiva));
	if(!s) return NULL;
	s->dime = d;
	s->vf = NULL;
	return (void*)s;
}

/* pune element in varful stivei */
int Push(void* s, void* ae) //ok
{
	ACelSt aux;
	aux = (ACelSt)malloc(sizeof(TCelSt));
	if(!aux) return 0;
	aux->info = ae; //ae trebuit alocat per element 
	aux->urm = ((ASt)s)->vf; 
	((ASt)s)->vf = aux;
	return 1;
}

/* extrage elementul din varful stivei la adresa ae */
int Pop(void *s, void *ae) //ok     
{ 
	ACelSt aux = VF(s); //varful stivei
	if(aux == NULL) return 0;
	memcpy(ae, aux->info, dime(s));
	VF(s) = aux->urm;
	free(aux);
	return 1;
}
