/* Tararache Crina-Andreea, grupa 314CB */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TCoada.h"
#include "TStiva.h"
#include "TLista.h"

/* structura unui serial */
typedef struct
{ 
	int ID; //ID-ul serialului
	char *nume; // numele serialului
	float rating; //ratingul serialului
	int nr_sezoane;
	TCoada* coada_sezoane;
}TSerial; 

/* structura unui sezon */
typedef struct 
{
	int nr_episoade;
	TCoada* coada_episoade;
}TSezon;

/* functie de afisare element */
void AfisElem(void* p, FILE* out)
{
	TSerial* a = (TSerial*)p;
	fprintf(out, "(%s, %0.1f)", a->nume, a->rating);
}

/* functie de sortare a serialelor in lista */
int SortLG(TLG* l) 
{
	if((*l)->urm == NULL) //daca avem un singur element in lista
	{
		return 0;
	}
	TLG a, ant;
	float aux1;
	char *aux2 = malloc(33);
	int contor;
	for(ant = *l; ant != NULL; ant = ant->urm)
	{
		TSerial* p = (TSerial*)(ant->info);
		for(a = ant->urm; a != NULL; a = a->urm)
		{
			TSerial* q = (TSerial*)(a->info);
			if(q->rating > p->rating)
			{
				aux1 = p->rating;
				p->rating = q->rating;
				q->rating = aux1;

				strcpy(aux2, p->nume);
				strcpy(p->nume, q->nume);
				strcpy(q->nume, aux2); 
			}
			if(q->rating == p->rating)
			{
				if(strcmp(p->nume, q->nume) > 0)
				{
					strcpy(aux2, p->nume);
					strcpy(p->nume, q->nume);
					strcpy(q->nume, aux2);
				}

			}
		}
	}
	return 1;
} 

/* functie care returneaza indicele unui element in lista */
int indice(TLG l, void* x)
{
	int contor = 1;
	
	for( ; l != NULL; l = l->urm)
	{
		TSerial* p = (TSerial*)(l->info);
		if(strcmp(p->nume, x) == 0)
		{	
			return contor;
		}
		contor++;
	}
}

/* functie care elimina din categorie si insereaza in coada later */
int Cauta_si_elimina(TLG* l, void* elem, void* coada) 
{
	int contor = 0;
	int pozitie = 1;
	int contor2 = 0;
	TLG a = *l;
	for( ; a != NULL; a = a->urm)
	{
		TSerial* p = (TSerial*)(a->info);
		if(strcmp(p->nume, elem) == 0)
		{
			contor++; //l-a gasit
			break;
		}	
		else
			pozitie++;
	}
	if(contor == 0) //nu l-a gasit
		return 0;
	if(contor != 0) 
	{
		TSerial* serial = (TSerial*)(a->info);
		/* insereaza in coada */
		if(IC(coada) == NULL)
			InsQ_vida(coada, (void *)serial);
		else
			InsQ_nevida(coada, (void *)serial);
		TLG s, ant;
		for(s = *l, ant = NULL; s != NULL; ant = s, s = s->urm)
		{
			TSerial* q = (TSerial*)(s->info);
			if(strcmp(q->nume, elem) == 0)
			{
				/* elimina din lista */
				TLG aux = s;
				if(ant == NULL)
					*l = s->urm;
				else
					ant->urm = s->urm;
			}
		}
	}
	return 1;
}

/* functie care adauga seriale in top10 in functie de pozitie */
int Ins_sort(TLG *l, void *p, int pozitie)
{
	TLG a, ant;
	ant = *l;
	int lungime = LungimeLG(l);
	int contor = 2;

	if (pozitie == 1) //inserez la inceput de lista
	{
		InsLG(&(*l), p);
		return 1;
	}
	if(pozitie > lungime) //inserez la sfarsit
	{
		InsSF((*l), p);
		return 1;
	}
	for (a = ant->urm; a != NULL; a = a->urm, ant = ant->urm) //ant este prima celula, a este a doua
	{
		if (contor == pozitie)
		{

			TLG aux = (TLG)malloc(sizeof(TCelulaG));
			if (!aux)
				return 0;
			aux->info = p;
			aux->urm = ant->urm;
			ant->urm = aux;
			return 1;
		}
		contor++;
	}
}

int main(int arg, char* argv[])
{
	FILE* in;
	FILE* out;
	in = fopen(argv[1], "r");
	if(in == NULL) return 0;
	out = fopen(argv[2], "w");
	if(out == NULL) return 0;

	char *comanda = malloc(30);
	char *nume = malloc(33);
	int ID, nrSez, nrEp, durata, pozitia;
	float rating;
	int Indice = 1;

	/* LISTE GENERICE */
	TLG Tendinte = NULL;
	TLG Documentare = NULL;
	TLG Tutoriale = NULL;
	TLG Top10 = NULL;

	TCoada *watch_later = InitQ(sizeof(TSerial));

	while(fscanf(in, "%s", comanda) == 1) //atata timp cat citeste linii cu comenzi
	{
		char s1[] = "add", s2[] = "show", s3[] = "later";
		if(strcmp(comanda, s1) == 0) //add
		{
			
			fscanf(in, "%d %s %f %d", &ID, nume, &rating, &nrSez);
			TSerial* p = (TSerial*)malloc(sizeof(TSerial));
			if(!p) return 0; //nu s-a reusit alocarea serialului
			p->ID = ID;
			p->nume = malloc(33);
			strcpy(p->nume, nume);
			p->rating = rating;
			p->nr_sezoane = nrSez;
			p->coada_sezoane = InitQ(sizeof(TSezon)); //initializare coada de seriale
			int i, j;
			for(i = 1; i <= p->nr_sezoane; i++) //atata timp cat sunt sezoane
			{
				fscanf(in, "%d", &nrEp); //citesc cate episoade are fiecare sezon
				TSezon* q = (TSezon*) malloc(sizeof(TSezon));
				if(!q) return 0; //nu s-a reusit alocarea sezonului

				q->nr_episoade = nrEp;
				q->coada_episoade = InitQ(sizeof(int)); //initializare coada de episoade

				for(j = 1; j <= q->nr_episoade; j++) //atata timp cat sunt episoade
				{
					fscanf(in, "%d", &durata); //citesc cate minute are fiecare episod

					/* INSERARE IN COADA DE EPISOADE */
					if(IC(q->coada_episoade) == NULL) //inserez in coada vida de episoade
						InsQ_vida(q->coada_episoade, (void *)&durata);
					else
						InsQ_nevida(q->coada_episoade, (void *)&durata);
				}
		
				/*INSERARE IN COADA DE SEZOANE */
				if(IC(p->coada_sezoane) == NULL) //inserez in coada vida de sezoane
					InsQ_vida(p->coada_sezoane, (void *)q);
				else //insere in coada nevida
					InsQ_nevida(p->coada_sezoane, (void *)q);
			}

			/* INSERARE IN LISTA DE SERIALE */
			if(ID == 1) //inserez in lista Tendinte
			{
				InsLG(&Tendinte, (void *)p);
				fprintf(out, "Serialul %s a fost adaugat la pozitia ", p->nume);
				char *aux = malloc(33);
				strcpy(aux, p->nume);
				SortLG(&Tendinte);
				fprintf(out, "%d.\n", indice(Tendinte, (void *)aux));
			}
			if(ID == 2) //inserez in lista Documentare
			{
				InsLG(&Documentare, (void *)p);
				fprintf(out, "Serialul %s a fost adaugat la pozitia ", p->nume);
				char *aux = malloc(33);
				strcpy(aux, p->nume);
				SortLG(&Documentare);
				fprintf(out, "%d.\n", indice(Documentare, (void *)aux));
			}
			if(ID == 3) //inserez in lista Tutoriale
			{
				InsLG(&Tutoriale, (void *)p);
				fprintf(out,"Serialul %s a fost adaugat la pozitia ", p->nume);
				char *aux = malloc(33);
				strcpy(aux, p->nume);
				SortLG(&Tutoriale);
				fprintf(out, "%d.\n", indice(Tutoriale, (void *)aux));
			}
		}
	 
		if(strcmp(comanda, s3) == 0) //later
		{
			fscanf(in, "%s", nume);

			int l1 = Cauta_si_elimina(&Tendinte, (void *)nume, watch_later);
			int l2 = Cauta_si_elimina(&Documentare, (void *)nume, watch_later);
			int l3 = Cauta_si_elimina(&Tutoriale, (void *)nume, watch_later);
			int l4 = Cauta_si_elimina(&Top10, (void *)nume, watch_later);

			if(l1 != 0 || l2 != 0 || l3 != 0 || l4 != 0) //daca am gasit serialul in vreuna dintre liste
			{
				fprintf(out, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n", nume, Indice);
				Indice++;
			}
		} 

		if(strcmp(comanda, s2) == 0) //show
		{
			char *id = malloc(20);
			fscanf(in, "%s", id);
			if(strcmp(id, "1") == 0)
			{
				fprintf(out, "Categoria %s: ", id);
				Afisare(&Tendinte, AfisElem, out);
			}
			if(strcmp(id, "2") == 0)
			{	
				fprintf(out, "Categoria %s: ", id);
				Afisare(&Documentare, AfisElem, out);
			}
			if(strcmp(id, "3") == 0)
			{
				fprintf(out, "Categoria %s: ", id);
				Afisare(&Tutoriale, AfisElem, out);
			}
			if(strcmp(id, "top10") == 0)
			{
				fprintf(out, "Categoria %s: ", id);
				Afisare(&Top10, AfisElem, out);
			}
			if(strcmp(id, "later") == 0)
			{
				fprintf(out, "Categoria %s: ", id);
				Afisare_coada(watch_later, out, AfisElem);
			}
		} 

		if(strcmp(comanda, "add_top") == 0) //add_top
		{
			fscanf(in, "%d %s %f %d", &pozitia, nume, &rating, &nrSez);
			TSerial* p = (TSerial*)malloc(sizeof(TSerial));
			if(!p) return 0; //nu s-a reusit alocarea serialului
			p->ID = pozitia;
			p->nume = malloc(33);
			strcpy(p->nume, nume);
			p->rating = rating;
			p->nr_sezoane = nrSez;
			p->coada_sezoane = InitQ(sizeof(TSezon)); //initializare coada de seriale
			int i, j;
			for(i = 1; i <= p->nr_sezoane; i++) //atata timp cat sunt sezoane
			{
				fscanf(in, "%d", &nrEp); //citesc cate episoade are fiecare sezon
				TSezon* q = (TSezon*) malloc(sizeof(TSezon));
				if(!q) return 0; //nu s-a reusit alocarea sezonului

				q->nr_episoade = nrEp;
				q->coada_episoade = InitQ(sizeof(int)); //initializare coada de episoade

				for(j = 1; j <= q->nr_episoade; j++) //atata timp cat sunt episoade
				{
					fscanf(in, "%d", &durata); //citesc cate minute are fiecare episod

					/* INSERARE IN COADA DE EPISOADE */
					if(IC(q->coada_episoade) == NULL) //inserez in coada vida de episoade
						InsQ_vida(q->coada_episoade, (void *)&durata);
					else
						InsQ_nevida(q->coada_episoade, (void *)&durata);
				}
		
				/*INSERARE IN COADA DE SEZOANE */
				if(IC(p->coada_sezoane) == NULL) //inserez in coada vida de sezoane
					InsQ_vida(p->coada_sezoane, (void *)q);
				else //insere in coada nevida
					InsQ_nevida(p->coada_sezoane, (void *)q);
			}

			/* INSERARE IN LISTA top10 */

			Ins_sort(&Top10, (void *)p, pozitia);
			
			if(LungimeLG(&Top10) > 10)
				EliminaLG(Top10);

			fprintf(out, "Categoria top10: ");
			Afisare(&Top10, AfisElem, out);
		} 
	
	}
	return 0;
}

