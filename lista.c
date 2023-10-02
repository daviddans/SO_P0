#include "lista.h"
#define MAX_CMD 1000 //Tamaño maximo de un comando a guardar
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
        p->data = malloc(sizeof(char)*strlen(comand)+1);//añadir control de errores
        strcpy(p->data, comand);
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

int countCMD(tList lista){ // Sin uso 
    int i = 0;
    while(lista != NULL){
        lista = lista->next;
        i++;
    }
    return i;
}

void printCMD(tList lista, int n){
    int i = 1;
    tPos p = lista;
    char* cmd = NULL;
    if(n < 0){
        while(p != NULL){
        cmd = p->data;
        printf("    %d ---> %s",i,cmd);
        p = p->next;
        i++;
        }
    }
    else{
        while(i < n && p != NULL){
        cmd = p->data;
        printf("    %d ---> %s",i,cmd);
        p = p->next;
        i++;
        }
    }
}

void deleteList(tList* lista){
    tPos i = NULL;
    while((*lista) !=NULL){
        i = (*lista);
        (*lista) = (*lista)->next;
        free(i->data);
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

bool insertFile(tList* lista, char* str, int fd){
    tPos i;
    tPos p = malloc(sizeof(struct node));
    tFile* file;
    if(p != NULL && createFileNode(&p, str, fd)){ //Crear nodo y comprobar si se pudo reservar memoria
        if(isEmptyList(*lista)){ //Insertar en lista vacia
            (*lista) = p;
        }
        else{ // Insertar en lista no vacia
            i = (*lista);
            file = i->data;
            if(i->next == NULL){ //Unico elemento
                if(file->fd > fd){ //Insertar delante
                    p->next = i;
                    (*lista) = p;
                }
                else{ //Insertar al final
                    p->next = NULL;
                    i->next = p;
                }
            }
            else{ //Multiples elementos
                file = i->next->data;
                while(i->next != NULL && file->fd < fd){
                    i = i->next;
                    if(i->next != NULL) file = i->next->data;
                }
                if(i->next !=NULL){ //Insercion en el medio
                    p->next = i->next;
                    i->next = p;
                }
                else{ // Insercion en el final
                    p->next = NULL;
                    i->next = p;
                }
            }
        }
        return true;
    }
    return false;
}

tFile* getFile(tList lista, int fd){
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

bool deleteFile(tList* lista, int fd){
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

void printfFile(tFile file){
    //do something
}