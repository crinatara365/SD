/* Tararache Crina-Andreea, grupa 314CB */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Trie.h"

/* functie care creeaza nod nou in arborele cu carti */
struct Trie_1* Nod_nou_1() 
{
    struct Trie_1* node = (struct Trie_1*)malloc(sizeof(struct Trie_1));
    node->leaf = (TCarte*)malloc(sizeof(TCarte));
    if(!node->leaf) return 0;
    node->leaf = NULL;
    int i;
    for(i = 0; i < CHAR_SIZE; i++)
    {
        node->character[i] = NULL;
    }
    return node;
}

/* functie care creeaza nod nou in arborele cu autori */
struct Trie_2* Nod_nou_2() 
{
    struct Trie_2* node = (struct Trie_2*)malloc(sizeof(struct Trie_2));
    node->leaf = (struct Trie_1*)malloc(sizeof(struct Trie_1));
    if(!node->leaf) return 0;
    node->leaf = NULL;
    int i;
    for(i = 0; i < CHAR_SIZE; i++)
    {
        node->character[i] = NULL;
    }
    return node;
}

/* functie care insereaza string in arborele de carti */
void Insert_1(struct Trie_1* head, char* str, TCarte *carte)
{
    struct Trie_1* current = head;
    while(*str)
    {
        if(current->character[*str-0] == NULL)
        {
            current->character[*str-0] = Nod_nou_1();
        }
        current = current->character[*str-0];
        str++;
    }
    /* ultimului nod i se atribuie pointerul catre structura ce contine informatiile cartii */
    current->leaf = carte; 
}

/* functie care insereaza string in arborele de autori */
void Insert_2(struct Trie_2* head, char* str, struct Trie_1 *p)
{
    struct Trie_2* current = head;
    while(*str)
    {
        if(current->character[*str-0] == NULL)
        {
            current->character[*str-0] = Nod_nou_2();
        }
        current = current->character[*str-0];
        str++;
    }
    /* ultimului nod i se atribuie pointerul catre arborele de carti corespunzator autorului */
    current->leaf = p; 
}

/* returneaza pointerul catre structura de carti (daca gaseste) sau NULL (daca nu gaseste) */
TCarte* search_1(struct Trie_1* head, char* str) 
{
    /*daca Trie este gol, returneaza 0*/
    if(head == NULL) 
    {   
        printf("trie e gol\n");
        return 0;
    }
    struct Trie_1* current = head;
    while(*str)
    {
        current = current->character[*str-0];
        if(current == NULL)
            return 0;
        str++; 
    }
    return current->leaf;
}

/* returneaza pointerul catre structura unui arbore cu cartile corespunzatoare(daca gaseste) sau NULL (altfel) */
struct Trie_1* search_2(struct Trie_2* head, char* str) 
{
     /*daca Trie este gol, returneaza 0*/
    if(head == NULL)
    {   
        printf("trie e gol\n");
        return 0;
    }
    struct Trie_2* current = head;
    while(*str)
    {
        current = current->character[*str-0];
        if(current == NULL)
            return 0;
        str++; 
    }
    return current->leaf;
}

/* afiseaza continutul unui arbore */
void display(struct Trie_1* head, char str[], int level, FILE *out)
{
    char alfabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
    int lungime = strlen(alfabet);
    if(head == NULL)  
        printf("trie e gol\n");


    if(head->leaf != NULL)
    {
        str[level] = '\0';
        /* sa nu afiseze o linie goala la inceput */
        if(strlen(str) > 0 && head->leaf->titlu != NULL) 
            fprintf(out, "%s\n", str);
    }

    int i;
    for(i = 0; i < lungime; i++)
        if(head->character[alfabet[i]-0] != NULL)
        {
            str[level] = alfabet[i]-0;
            display(head->character[alfabet[i]-0], str, level + 1, out);
        }
}

/* cauta numele cartii dupa prefix */
int display_by_prefix_book(struct Trie_1* head, char str[], int level, FILE *out, char prefix[], int* contor)
{
    char alfabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
    int lungime = strlen(alfabet);
    if(head == NULL)  
        printf("trie e gol\n");

    if(head->leaf != NULL)
    {
        str[level] = '\0';
        if(strlen(str) > 0 && head->leaf->titlu != NULL) 
            if(StartsWith(str, prefix) != 0 && (*contor)<3)
            {
                *contor = (*contor)+1;
                fprintf(out, "%s\n", str);
                if(*contor>=3)
                    return 0;
            }
    }

    int i;
    for(i = 0; i < lungime; i++)
        if(head->character[alfabet[i]-0] != NULL)
        {
            str[level] = alfabet[i]-0;
            display_by_prefix_book(head->character[alfabet[i]-0], str, level + 1, out, prefix, contor);
        }
}

/* verifica daca stringul a incepe cu stringul b */
int StartsWith(char a[], char b[])
{
    if(strncmp(a, b, strlen(b)) == 0)
        return 1;
    return 0;
}

/* cauta autorul dupa prefix */
int display_by_prefix_author(struct Trie_2* head, char str[], int level, FILE *out, char prefix[], int* contor)
{
    char alfabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
    int lungime = strlen(alfabet);
    if(head == NULL)  
        printf("trie e gol\n");

    if(head->leaf != NULL)
    {
        str[level] = '\0';
        /* sa nu afiseze o linie goala la inceput */
        if(strlen(str) > 0) 
            if(StartsWith(str, prefix) != 0 && (*contor)<3) 
            {
                *contor = (*contor)+1;
                fprintf(out, "%s\n", str); 
                if(*contor>=3)
                    return 0;
            }
    }

    int i;
    for(i = 0; i < lungime; i++)
        if(head->character[alfabet[i]-0] != NULL)
        {
            str[level] = alfabet[i]-0;
            display_by_prefix_author(head->character[alfabet[i]-0], str, level + 1, out, prefix, contor);
        }
} 
