/* Tararache Crina-Andreea, grupa 314CB */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Trie.h"


int main(int arg, char* argv[])
{
    FILE* in;
	FILE* out;
	in = fopen(argv[1], "r");
	if(in == NULL) return 0;
	out = fopen(argv[2], "w");
	if(out == NULL) return 0;

    struct Trie_1* head_1 = Nod_nou_1(); /* trie ce contine cartile */
    struct Trie_2* head_2 = Nod_nou_2(); /* trie ce contine autorii */

    char *buffer;
    size_t bufsize = 32;
    buffer = (char*)malloc(bufsize * sizeof(char));
    if(!buffer) return 0;
    char *p;
    int rating, nr_pag;

    while(getline(&buffer, &bufsize, in) != -1)
    {
        p = strtok(buffer, "\n");
        p = strtok(p, " ");

        if(strcmp(p, "add_book") == 0)
        {
            char *s = malloc(100);
            if(!s) return 0;
            strcpy(s, p);

            TCarte *carte = (TCarte*)malloc(sizeof(TCarte));
            if(!carte) return 0;

            /* se completeaza campurile structurii unei carti */
            s = strtok(NULL, ":");
            carte->titlu = malloc(100);
            if(!carte->titlu) return 0;
		    strcpy(carte->titlu, s);
            s = strtok(NULL, ":");
            carte->autor = malloc(100);
            if(!carte->autor) return 0;
            strcpy(carte->autor, s);
            s = strtok(NULL, ":");
            rating = atoi(s);
            carte->rating = rating;
            s = strtok(NULL, ":");
            nr_pag = atoi(s);
            carte->nr_pag = nr_pag;

            Insert_1(head_1, carte->titlu, carte); /* se insereaza cartea in arborele de carti */
            if(search_2(head_2, carte->autor) == NULL) /* daca autorul nu se afla in arbore */
            {
                struct Trie_1* head_3 = Nod_nou_1(); /* trie ce contine cartile unui autor */
                Insert_1(head_3, carte->titlu, carte);
                Insert_2(head_2, carte->autor, head_3); /* se insereaza autorul in arborele de autori */
            }
            else /* daca autorul se afla in arbore */
            {
                struct Trie_1* aux = search_2(head_2, carte->autor);
                Insert_1(aux, carte->titlu, carte);
            } 
        }  

        if(strcmp(p, "search_book") == 0) //search_book <titlu> sau search_book <prefix_titlu>
        {
            char *s = malloc(200);
            if(!s) return 0;
            strcpy(s, p);
            s = strtok(NULL, "*"); 

            /* se elimina enterul de la finalul sirului de caractere */
            if(s[strlen(s) - 1] == '\n')
                s[strlen(s) - 1] = '\0';
            if(s[strlen(s) - 1] == '\r')
                s[strlen(s) - 1] = '\0';

            if(strchr(s, '~') != 0) //caut dupa prefix
            {
                char str[50];
                s = strtok(s, "~");
                char q[50];
                strcpy(q, s);
                int contor = 0;
                display_by_prefix_book(head_1, str, 0, out, q, &contor);
                if(contor == 0)
                    fprintf(out, "Nicio carte gasita.\n");
            }
            else //caut dupa nume
            {
                TCarte *aux;
                aux = search_1(head_1, s);
                if(aux == NULL) 
                    fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", s);
                else if(aux->titlu == NULL)
                    fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", s);
                else
                    fprintf(out, "Informatii recomandare: %s, %s, %d, %d\n", aux->titlu, aux->autor, aux->rating, aux->nr_pag);
            }
        }

        if(strcmp(p, "list_author") == 0) //list_author <autor> sau list_author <prefix_autor>
        {
            char *s = malloc(100);
            if(!s) return 0;
            strcpy(s, p);
            s = strtok(NULL, "*");

            /* se elimina enterul de la finalul sirului de caractere */
            if(s[strlen(s) - 1] == '\n')
                s[strlen(s) - 1] = '\0';
            if(s[strlen(s) - 1] == '\r')
                s[strlen(s) - 1] = '\0';

            if(strchr(s, '~') != 0) //caut dupa prefix
            {
                char str[50];
                s = strtok(s, "~");
                char q[50];
                strcpy(q, s);
                int contor = 0;
                display_by_prefix_author(head_2, str, 0, out, q, &contor);
                if(contor == 0)
                    fprintf(out, "Niciun autor gasit.\n");
            }
            else //caut dupa autor
            {
                struct Trie_1 *aux = search_2(head_2, s);
                char str[50];

                if(aux == NULL)
                    fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n", s);
                else
                    display(aux, str, 0, out);
            }
        }

        if(strcmp(p, "search_by_author") == 0)
        {
            
            char *s = malloc(100);
            if(!s) return 0;
            strcpy(s, p);
            s = strtok(NULL, "*");
            
            /* se elimina enterul de la finalul sirului de caractere */
            if(s[strlen(s) - 1] == '\n')
                s[strlen(s) - 1] = '\0';
            if(s[strlen(s) - 1] == '\r')
                s[strlen(s) - 1] = '\0';

            if(strchr(s, '~') != 0) 
            {
                if(strchr(s, ':') != 0)
                {
                    s = strtok(s, ":");
                    struct Trie_1 *aux = search_2(head_2, s); //daca exista autorul in T2
                    if(aux == NULL)
                        fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n", s);
                    else
                    {
                        s = strtok(NULL, "*");
                        s = strtok(s, "~");
                        char str[50];
                        char q[50];
                        strcpy(q, s);
                        int contor = 0;
                        display_by_prefix_book(aux, str, 0, out, q, &contor);
                        if(contor == 0)
                            fprintf(out, "Nicio carte gasita.\n");
                    }
                }
                else
                {
                    char str[50];
                    if(s[strlen(s) - 1] == '\n')
                        s[strlen(s) - 1] = '\0';
                    if(s[strlen(s) - 1] == '\r')
                        s[strlen(s) - 1] = '\0';
                    s = strtok(s, "~");
                    char q[50];
                    strcpy(q, s);
                    int contor = 0;
                    display_by_prefix_author(head_2, str, 0, out, q, &contor);
                    if(contor == 0)
                        fprintf(out, "Niciun autor gasit.\n");
                }
            }
            else
            {
                s = strtok(s, ":");
                struct Trie_1 *aux = search_2(head_2, s); //daca exista autorul in T2

                if(aux == NULL)
                    fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n", s);
                else
                {
                    s = strtok(NULL, "*");
                    if(s[strlen(s) - 1] == '\n')
                        s[strlen(s) - 1] = '\0';
                    if(s[strlen(s) - 1] == '\r')
                        s[strlen(s) - 1] = '\0';
                    TCarte *contor;
                    contor = search_1(aux, s);
            
                    if(contor == NULL) 
                        fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", s);
                    else if(contor->titlu == NULL)
                        fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", s);
                    else
                        fprintf(out, "Informatii recomandare: %s, %s, %d, %d\n", contor->titlu, contor->autor, contor->rating, contor->nr_pag);
 
                }
            }
        }

    }

    fclose(in);
    fclose(out);
    return 0;
}