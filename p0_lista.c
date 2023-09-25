//Codigo de la lista
#include "p0_lista.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

void createEmptyList(SList *L){
    *L = NULL;
}

void deleteElement(SPosL* p, SList L){
    free(*p);
}

void deleteList(SList *L){//recorre la lista y va eliminando sus elementos
    SPosL q = *L;
    while(*L != NULL){
        q = q->next;
        deleteElement(&q, *L);
        q = (*L);
    }
    (*L) = NULL;
}  

bool createNode(char*  command, SPosL * pos){
    *pos = malloc(sizeof(SPosL));
    if(pos!=NULL){
        memcpy((*pos)->comando, command, strlen(command));
        (*pos)->next = NULL;
        return true;
    }
    else return false;
}

//Insertar nuevo comando al principio de la lista
bool insertItem(SList *L, char* command){
    SPosL pos;
    if(createNode(command,&pos)){
        pos->next = (*L);
        (*L)->next = pos;
        return true;
    }
    else return false;
}

void imprimirListado(SList L){//imprime por pantalla los elementos de la lista
    int i = 1;
    SPosL q = L;
    while(q != NULL){
        printf("%d->%s", i, q->comando);
        q = q->next;
        i++;
    }
}

bool getElement(SList L, int pos, char* dest){
    int i = 1;
    if(pos < 1){
        return false;
    } else {
        SPosL q = L;
        while((q != NULL)&&(i < pos)){
            q = q->next;
            i++;
        }
        if(i == pos){
            strcpy(dest, q->comando);
            return true;
        }
    }
    return false;
}