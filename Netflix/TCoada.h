/* Tararache Crina-Andreea, grupa 314CB */
/*-- TCoada.h --- tipul coada ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

typedef struct cel /* dimensiune variabila */
{ 
  struct cel * urm;
  void* info;
} TCel, *ACel;

typedef struct coada
{ 
  size_t dime; /* dim.element */
  ACel ic, sc; /* adr.prima, ultima celula */
} TCoada, *AQ;

/* --- Macrodefintii --- */
#define DIME(a) (((AQ)(a))->dime) //dimensiunea unui element 
#define SC(a) (((AQ)(a))->sc) //ultima celula 
#define IC(a) (((AQ)(a))->ic) //prima celula 

typedef void (*TF1)(void*, FILE*);

void* InitQ(size_t d); /* creeaza coada vida cu elemente de dimensiune d; */
int InsQ_vida(void* a, void* ae); /* adauga element la sfarsitul cozii */
int InsQ_nevida(void* a, void* ae);
void Afisare_coada(void*, FILE*, TF1);
int Coada_vida(void *a);
int ExtrQ(void*, void*);
