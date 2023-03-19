/* Tararache Crina-Andreea, grupa 314CB */
/*-- TLista.h --- LISTA SIMPLU INLANTUITA GENERICA ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

//#ifndef _LISTA_GENERICA_
//#define _LISTA_GENERICA_

typedef struct celulag
{
  void* info;           /* adresa informatie */
  struct celulag *urm;   /* adresa urmatoarei celule */
} TCelulaG, *TLG; /* tipurile Celula, Lista  */

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*, FILE*);     /* functie afisare/eliberare un element */

/* functii lista generica */
int InsLG(TLG*, void*);  /*- inserare la inceput reusita sau nu (1/0) -*/
int InsSF(TLG, void*);
void EliminaLG(TLG);
TLG AlocCelula(void*);
int LungimeLG(TLG*);
/* afiseaza elementele din lista, folosind o functie de tip TFAfi */
void Afisare(TLG*, TF, FILE*);


//#endif