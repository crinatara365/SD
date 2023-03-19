/* Tararache Crina-Andreea, grupa 314CB */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CHAR_SIZE 130

typedef struct 
{
    char* titlu; /*titlul cartii*/
    char* autor; /*autorul cartii*/
    int rating; /*ratingul cartii*/
    int nr_pag; /*nr de pagini al cartii*/
}TCarte; /* structura unei carti */

struct Trie_1
{
    TCarte *leaf;
    struct Trie_1* character[CHAR_SIZE];
}; /* arborele cu carti */

struct Trie_2
{
    struct Trie_1 *leaf; /* ultimul nod primeste poiterul catre arborele de carti */
    struct Trie_2* character[CHAR_SIZE];
}; /* arborele cu autori */

void Insert_1(struct Trie_1*, char*, TCarte*); /*functie care insereaza string in arborele de carti*/
void Insert_2(struct Trie_2*, char*, struct Trie_1*); /*functie care insereaza string in arborele de autori*/
struct Trie_1* Nod_nou_1(); /*functie care creeaza nod nou in arborele cu carti*/
struct Trie_2* Nod_nou_2(); /*functie care creeaza nod nou in arborele cu autori*/
TCarte* search_1(struct Trie_1*, char*); /*functie care verifica daca string se afla in trie de carti*/
struct Trie_1* search_2(struct Trie_2*, char*); /*functie care verifica daca string se afla in trie de autori*/
void display(struct Trie_1*, char str[50], int, FILE*); /*functie care afiseaza continutul unui arbore de carti*/
int display_by_prefix_book(struct Trie_1*, char str[50], int, FILE *, char prefix[50], int* contor); /*returneaza primele 3 sugestii de carti ce contin prefixul dat */
int StartsWith(char a[50], char b[50]); /*functie care verifica daca un string incepe cu altul*/
int display_by_prefix_author(struct Trie_2* head, char str[], int level, FILE *out, char prefix[], int* contor); /*returneaza primele 3 sugestii de autori ce contin prefixul dat */