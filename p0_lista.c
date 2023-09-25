#include "p0_lista.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>  
void createEmptyList(SList *L){
    *L = NULL;
}

void removeItem(SPosL p, SList *L) {
    SPosL q;

    if(p == *L) {
        *L = (*L)->next;

    } else if(p->next == NULL) {
        for(q = *L; q->next->next != NULL; q = q->next);
        q->next = NULL;

    } else { // Eliminado de un elemento que no se encuentra en los extremos
        q = p->next;
        p->comando = q->comando;
        p->next = q->next;
        p = q;
    }

    free(p);
}

void deleteList(SList *L){//recorre la lista y va eliminando sus elementos
    SPosL q;
    while(*L != NULL){
        q = *L;
        *L = (*L)->next;
        free(q);
    }
}  

bool createNode(char *command, SPosL *pos){
    *pos = malloc(sizeof(SPosL));
    if(*pos!=NULL){
        memcpy((*pos)->comando, command, strlen(command));
        (*pos)->next = NULL;
        return true;
    } else return false;
}

bool insertItem(char command, SPosL p, SList *L){
    SPosL q, r;

    if(!createNode(&q)) {
        return false;
    }
    else {
        q->comando = d;
        q->next = NULL;

        /* Si la lista está vacía, se añadirá el elemento a la primera posición y el puntero
         * L, apuntará a este primer nodo */
        if (isEmptyList(*L)) {
            *L = q;
        }

        //Si la posición recibida por la función es NULL, se añadirá como último elemento de la lista
        else if(p == NULL) {
            for(r = *L; r->next != LNULL; r = r->next); // Nos desplazamos al último elemento de la lista
            r->next = q;
        }

        /* Si la posición recibida es idéntica al valor al que apunta *L, es porque hay que añadir este elemento
         en la primera posición de la lista */
        else if(p == *L) {
            q->next = p;
            *L = q;
        }

        // Si no se cumple ninguna de las otras condiciones, es que se debe insertar en una posición intermedia
        else {
            q->comando = p->comando;
            p->comando = command;
            q->next = p->next;
            p->next = q;
        }
        return true;
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

bool getElement(SList L, int pos, char *dest){
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
            strcpy(dest, (*pos)->comando);
            return true;
        }
    }
    return false;
}