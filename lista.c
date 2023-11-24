//Codigo de la lista
#include "lista.h"

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
        p->data = malloc(sizeof(char)*strlen(comand)+1);
        if(p->data == NULL) printf("ERROR EN INSERTCMD");
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
        while(i <= n && p != NULL){
        cmd = p->data;
        printf("    %d ---> %s",i,cmd);
        p = p->next;
        i++;
        }
    }
}

void deleteListCMD(tList* lista){ //Borra una lista de comandos liberando memoria correctamente
    tPos i = NULL;
    while((*lista) !=NULL){
        i = (*lista);
        (*lista) = (*lista)->next;
        free(i->data);
        free(i);
    }
}

void deleteListFile(tList* lista){ //Borra una lista de ficheros liberando memoria correctamente
    tPos i = NULL;
    tFile* file;
    while((*lista) !=NULL){
        i = (*lista);
        (*lista) = (*lista)->next;
        file = i->data;
        free(file->path);
        free(file);
        free(i);
    }
}


bool createFileNode(tPos* p, char* str, int fd, int mode){ //Funcion auxiliar que reserva memoria para añadir un fichero a una lista
    bool r = false;
    tFile* file = malloc(sizeof(tFile));
    if(file != NULL){
        file->path = malloc(sizeof(char)*strlen(str)+1);
        strcpy(file->path, str);
        file->fd = fd;
        file->mode = mode;
        (*p)->data = file;
        (*p)->next = NULL;
        r = true;
    }
    return r;
}

bool insertFile(tList* lista, char* str, int fd, int mode){
    tPos i;
    tPos p = malloc(sizeof(struct node));
    tFile* file;
    if(p != NULL && createFileNode(&p, str, fd, mode)){ //Crear nodo y comprobar si se pudo reservar memoria
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

tPos searchFile(tList lista, int fd){ //Devuelve la posicion de un archivo buscado por fd
    tPos i = lista;
    tFile * file = NULL;
    if(!isEmptyList(lista)){ // comprobamos que la lista no este vacia
        file = i->data;
        while(i != NULL && file->fd < fd){ // recorremos la lista
            i = i->next;
            if(i !=NULL) file = i->data;
        }
        if(file->fd == fd){ // Si encontramos el elemento devolvemos su puntero
            return i; 
        }
    }
    return NULL; //Si no encontramos el elemento devolvemos NULL
}

bool deleteFile(tList* lista, int fd){ //Borra un archivo de la lista
    tPos i;
    tPos del;
    tFile* file;
    if(!isEmptyList(*lista)){ // comprobamos que la lista no este vacia
        i = *lista;
        file = i->data;
        if(file->fd == fd){ //Eliminar primer elemento
            *lista = (*lista)->next;
            free(file->path);
            free(file);
            free(i);
        }
        else if(i->next != NULL){
            file = i->next->data;
            while(i->next != NULL && file->fd < fd){  //Buscar el elemento a borrar
                i = i->next;
                if(i->next != NULL) file = i->next->data;
            }
            if(file->fd == fd){ //Si se encontro el elemento a borrar
                if(i->next->next != NULL){ //Borrado en el medio
                del = i->next;
                i->next = del->next;
                file = del->data;
                free(file->path);
                free(del->data);
                free(del);
                }
                else{ //Borrado al final
                del = i->next;
                i->next = NULL; 
                file = del->data;
                free(file->path);
                free(del->data);
                free(del);
                }
                return true;
            }
        }
    }
    return false;
}

tMemBlock* newMemBlock(void* addres, size_t size, time_t allocTime, Type tipo, __key_t key, char name[], int fd){//Crea un bloque de memoria 
    tMemBlock* p = malloc(sizeof(tMemBlock)); //Reservamos memoria
    if(p != NULL){
        p->addres = addres; //Guardamos direccion
        p->size = size; //Guardamos tamañ0
        time(&(p->allocTime)); //Guardamos hora
        p->tipo = tipo; //Guardamos tipo
        p->key = -1;
        p->filename = NULL;
        p->fd = -1;
        if(tipo == shm) p->key = key; //Guardamos clave de shm
        if(tipo == map) {
            p->filename = malloc(sizeof(char)*(strlen(name)+1));
            strcpy(p->filename, name);
            p->fd = fd;
        }
    }
    return p;
}


bool insertMemBlock(tList* lista, tMemBlock* memblock){ //Añade un bloque de memoria previamente creado a la lista
    bool r; //Bool para guardar el retorno
    tPos pos;
    if(memblock == NULL) printf("No se puede añadir bloques de memoria nulos");
    else{
        if((pos = malloc(sizeof(struct node)))==NULL) r = false; //Comprobamos que la reserva de memoria sea correcta
        else{
            pos->data = memblock; //Guardamos los datos
            pos->next = NULL;
            if(isEmptyList(*lista)) *lista = pos; //Si la lista es vacia insertamos como unico elemento
            else{//Si no insertamos al principio (mayor eficiencia)
                pos->next = *lista;
                *lista = pos;
            }
            r = true;
        }
    }
    return r;
}   
void freeMemblock(tMemBlock* memBlock){ //Funcion auxiliar para liberar memoria de un bloque de memoria
    if(memBlock->tipo == map) free(memBlock->filename);
    free(memBlock);
}

void deleteMemBlockIn(tList* lista, tPos p){ //Boramos el item de la posicion p
    tPos i;
    if(p == *lista){
        *lista = p->next; // Comprobamos si es el primer elemento
        freeMemblock(p->data);
        free(p);
    }
    else{
        while (i!= NULL && i->next != p) //Recorremos la lista
        {
            i = i->next;
        }
        if(i->next == p){ //Si encontramos el elemento
            i->next = p->next;
            freeMemblock(p->data);
            free(p);
        }
    }
}

tPos findKey(tList lista, __key_t key){ //Busca un elemento por el campo key
    tPos i = lista;
    tMemBlock * memBlock = NULL;
    if(!isEmptyList(lista)){ // comprobamos que la lista no este vacia
        memBlock = i->data;
        while(i != NULL && memBlock->key != key){ // recorremos la lista
            i = i->next;
            if(i !=NULL) memBlock = i->data;
        }
        if(memBlock->key == key){ // Si encontramos el elemento devolvemos su puntero
            return i; 
        }
    }
    return NULL; //Si no encontramos el elemento devolvemos NULL
}

void deleteMemList(tList* lista){ //Elimina lista de memblocks
    tPos i = NULL;
    tMemBlock* memBlock;
    while((*lista) !=NULL){
        i = (*lista);
        (*lista) = (*lista)->next;
        memBlock = i->data;
        freeMemblock(memBlock);
        free(i);
    }
}

void freeAllMemoryList(tList* lista){ //Funcion que vacia correctamente una lista de memoria antes de salir del programa
    tPos i = NULL;
    tMemBlock* memBlock;
    while((*lista) !=NULL){
        i = (*lista);
        (*lista) = (*lista)->next;
        memBlock = i->data;
        free(memBlock->addres);
        freeMemblock(memBlock);
        free(i);
    }
}

tPos searchBySiceAndType(tList lista, size_t tam, Type tipo){ //Devuelve la posicion de la primera coincidencia
    tPos i = lista;
    tMemBlock * memBlock = NULL;
    if(!isEmptyList(lista)){ // comprobamos que la lista no este vacia
        memBlock = i->data;
        while(i != NULL && !(memBlock->size == tam && memBlock->tipo == tipo)){ // recorremos la lista
            i = i->next;
            if(i!=NULL)memBlock = i->data;
        }
        if(memBlock->size == tam && memBlock->tipo == tipo){ // Si encontramos el elemento devolvemos su puntero
            return i; 
        }
    }
    return NULL; //Si no encontramos el elemento devolvemos NULL
}

tPos searchByKey(tList lista, key_t key){ //Devuelve la posicion de la primera coincidencia
    tPos i = lista;
    tMemBlock * memBlock = NULL;
    if(!isEmptyList(lista)){ // comprobamos que la lista no este vacia
        memBlock = i->data;
        while(i != NULL && !(memBlock->tipo == shm && memBlock->key == key)){ // recorremos la lista
            i = i->next;
            if(i!=NULL)memBlock = i->data;
        }
        if(memBlock->tipo == shm && memBlock->key == key){ // Si encontramos el elemento devolvemos su puntero
            return i; 
        }
    }
    return NULL; //Si no encontramos el elemento devolvemos NULL
}

tPos searchByFile(tList lista, char* file){ //Devuelve la posicion de la primera coincidencia
    tPos i = lista;
    tMemBlock * memBlock = NULL;
    if(!isEmptyList(lista)){ // comprobamos que la lista no este vacia
        memBlock = i->data;
        while(i != NULL && !(memBlock->tipo == map && strcmp(memBlock->filename,file)==0)){ // recorremos la lista
            i = i->next;
            if(i!=NULL)memBlock = i->data;
        }
        if((memBlock->tipo == map && strcmp(memBlock->filename,file)==0)){ // Si encontramos el elemento devolvemos su puntero
            return i; 
        }
    }
    return NULL; //Si no encontramos el elemento devolvemos NULL
}