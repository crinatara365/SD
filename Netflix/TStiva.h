/* Tararache Crina-Andreea, grupa 314CB */
/*-- TStiva.h --- tipul stiva ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

typedef struct celst
{ 
  struct celst *urm; /* adr.urmatoarei celule */
  void* info; /* adresa informatie */
} TCelSt, *ACelSt;

typedef struct stiva
{ 
  size_t dime; /* dim.element */
  ACelSt vf; /* adresa celulei din varf */
} TStiva, *ASt;

/* --- Macrodefintii --- */
#define dime(a) (((ASt)(a))->dime)
#define VF(a) (((ASt)(a))->vf)

void* InitS(size_t d);    /* initializeaza stiva cu elem.de dimensiune d; */
int Push(void* a, void* ae);  /* pune element in varful stivei */
int Pop (void* a, void* ae);  /* extrage elementul din varful stivei la adresa ae */

