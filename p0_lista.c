#include "p0_lista.h"

void createEmptyList(tList* lista){
    (*lista) = NULL;
}

bool isEmptyList(tList lista){
    return lista == NULL;
}
tPos next(tList lista, tPos p){
    return p->next;
}

tPos first(tList lista){
    return lista;
}

void* getData(tList lista, tPos p){
    return p->data;
}

bool insertCMD(tList* lista, cmd comand){
    bool r = false;
    tPos i;
    tPos p = malloc(sizeof(struct node));
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

bool createFileNode(tPos* p, char* str, int fd){ //Funcion auxiliar que reserva memoria para añadir un fichero a una lista
    bool r = false;
    tFile* file = malloc(sizeof(tFile));
    if(file != NULL){
        file->path = str;
        file->fd = fd;
        (*p)->data = file;
        (*p)->next = NULL;
        r = true;
    }
    return r;
}

bool insertFCH(tList* lista, char* str, int fd){ //NO FUNCIONA
    tPos i;
    tPos p = malloc(sizeof(struct node));
    tFile* file;
    if(p != NULL && createFileNode(&p, str, fd)){
        if(isEmptyList(*lista))
        {
            (*lista) = p;
        }
        else{
            file = (*lista)->data;
            if(fd < file->fd){
                p->next = (*lista);
                (*lista)->next = p;
                p->next = NULL;
                puts("hasta aqui :D");
            }
            else if((*lista)->next != NULL){
                i = (*lista);
                file = (i->next->data);
                while(i->next->next != NULL && file->fd < fd){
                    i = i->next;
                    if(i->next->data != NULL) file = (i->next->data);
                }
                if(i->next !=NULL){
                    p->next = i->next;
                    i->next = p;
                }
                else
                i->next = p;
                p->next = NULL;
            }
            else{
                (*lista)->next = p;
                p->next = NULL;
            }
        }
    }
    return false;
}

tFile* getFHC(tList lista, int fd){
    tPos i;
    tFile* file;
    if(!isEmptyList(lista)){
        i = lista;
        file = i->data;
        while(i != NULL && file->fd < fd){
            i = i->next;
            file = i->data;
        }
        if(i!=NULL && file->fd == fd) return file;
    }
    return NULL;
}

bool deleteFCH(tList* lista, int fd){
    tPos i;
    tPos delete;
    tFile* file;
    if(!isEmptyList(*lista)){
        i = *lista;
        file = i->data;
        if(file->fd == fd){
            (*lista)=(*lista)->next;
            free(file);
            free(i);
            return true;
        }
        else if (i->next != NULL){
            file = i->next->data;
            while(i->next != NULL && file->fd < fd){
                i = i->next;
                file = i->next->data;
            }
            if(file->fd == fd){
                if(i->next->next == NULL)
                {
                    delete = i->next;
                    i->next = NULL;
                }
                else{
                    delete = i->next;
                    i->next = i->next->next;
                }
                file = delete->data;  
                free(file);
                free(delete);
                return true;
            }
        }
    }
    return false;
}