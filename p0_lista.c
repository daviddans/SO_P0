#include "p0_lista.h"

void createEmptyList(tList* lista){
    (*lista) = NULL;
}

bool isEmptyList(tList lista){
    return lista == NULL;
}

bool insertCMD(tList* lista, cmd comand){
    bool r = false;
    tPos i;
    tPos p = malloc(sizeof(struct item));
    if(p != NULL){
        p->data = comand;
        p->next = NULL;
        if((*lista) == NULL){
            (*lista) = p;
        }      
        else{
        i = (*lista);
        while(i->next != NULL){
            i = i->next;
        }
        i->next = p;
        }
        r = true;
    }
    return r;
}

int countCMD(tList lista){
    int i = 0;
    while(lista != NULL){
        lista = lista->next;
        i++;
    }
    return i;
}

char* getCMD(tList lista, int n){
    int i = 0;
    tPos p = lista;
    char* retorno = NULL;
    while(i < n && p != NULL){
        p = p->next;
        i++;
    }
    if(p !=NULL){
        retorno = p->data;
    }
    return retorno;
}

void deleteCMDList(tList* lista){
    tPos i = NULL;
    while((*lista) !=NULL){
        i = (*lista);
        (*lista) = (*lista)->next;
        free(i);
    }
}