#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define LENGTH 100
#define LNULL NULL;
typedef struct SNode * SPosL; 
struct SNode{
    char comando[LENGTH];
    SPosL next;
};
typedef SPosL SList;

void createEmptyList(SList *L);   //Creamos una lista en L
void deleteList(SList *L);    //Borramos la lista L
bool insertItem(char command, SPosL p, SList *L);    //Instertamos un item con el parametro command al principio de la lista L                                         
void removeElement(SPosL p, SList *L);   //Borramos el elemento en la posición p de la lista L
void ImprimirListado(SList L); //Imprimimos la lista L
char Buscar(SList L, int pos); //Copiamos el contenido del elemento no. pos en dest
