#include "p0_Lista_H"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
void createEmptyList(SList *L){
    *L = NULL;
}

void deleteElement(SPosL *p){
    free(*p);
}
void deleteList(SList *L){//recorre la lista y va eliminando sus elementos
    SPosL q = *L;
    while(*L != NULL){
        q = q->next;
        deleteElement(&q);
        q = (*L);
    }
    (*L) = NULL;
}  
SPosL createItem(char command){
    SPosL q = NULL;
    q = malloc(sizeof(SPosL));
    q->next = NULL;
    strcpy(q->comando, command);
    return q;
}

int insertItem(SList *L, char *command){
    if (*L == NULL){
        *L = malloc(sizeof(SPosL));
        strcpy((*L)->comando, command);
        (*L)->next = NULL;
        return 0;
    } else {
        SPosL q = *L;
        SPosL comando;
        while(q->next != NULL){
            q = q->next;
        }
        comando = createItem(command);
        q->next = comando;
        return 0;
    }
}

void ImprimirListado(SList L){//imprime por pantalla los elementos de la lista
    int i = i;
    SPosL q = L;
    while(q != NULL){
        printf("%d->%s", i, q->comando);
        q = q->next;
        i++;
    }
}

char Buscar(SList L, int pos){
    int i = 1;
    if(pos < 1){
        printf("Posicion no valida\n");
        return; //no se que poner
    } else {
        SPosL q = L;
        while((q != NULL)&&(i < pos)){
            q = q->next;
            i++;
        }
        if(i == pos){
            return q->comando;
        } else printf("Posicion no valida\n");
        return;//no se que poner
    }
}