#include "p0_lista.h"

void createEmptyList(tLista* lista){
    (*lista)[0] = NULL;
}

bool createNode(tItemL* item, char* str){ //funcion auxiliar para realizar el malloc de un elemento a introducir
    *item = malloc(sizeof(strlen(str)));
    if(*item == NULL) //Comprobamos que se pudo realizar la reserva de memoria
    {
        return false;
    }
    (*item)->cadena = str;//Copiamos el argumento str en el campo cadena
    return true;
}

bool insertComand(tLista* lista, char* cmd, int n){
    tItemL item = NULL; //Nuevo item
    int i = 0; //Iniciamos contador
    if(n<MAX_LEN_LIST){//Comprobamos no excedernos de la lista
        if(createNode(&item, str)){ //Si se consigue reservar memoria
                (*lista)[i] = item; //Guardamos el objeto en el ultimo
                (*lista)->last++; //Aumentamos el
                return true; //Exito devolvemos true
            else free(item);
        }
    }
    return false;  //En caso de fallo devolvemos false
}

bool insertFile(tLista* lista, char* str, int fd){
    tItemL item = NULL; //Nuevo item
    if(fd<MAX_LEN_LIST){ //Comprobamos que el fd no exceda el maximo de la lista
        if(createNode(&item, str)){ //Si se consigue reservar memoria
            (*lista)[fd] = item; //Guardamos el objeto en el lugar correspondiente
            if(fd>(*lista)->last) (*lista)->last = fd; //Si el file descriptor excede el limite de la lista, este se vuelve el nuevo limite
            return true; //Exito devolvemos true
        }
    }
    return false;  //En caso de fallo devolvemos false
}

char * getCommand(tLista lista, int n){
    tItemL r = lista[n]; //Acedemos a la posicion n de la lista
    if(r == NULL) return NULL; // Si esta vacia devolvemos null
    return r->cadena; // En otro caso devolvemos la cadena almacenada
}

void deleteFile(tLista* lista, int fd){
    free((*lista)[fd]); //Liberamos el contenido de lista[n]
    (*lista)[fd] = NULL; //Ponemos lista[n] a NULL
    if(fd==(*lista)->last) (*lista)->last--; //Si borramos el ultimo fichero, decrementamos el ultimo
}

void deleteList(tLista* lista){
    int i = 0; // Iniciamos un contador
    while(i<(*lista)->last){ //Recoremos el array entero
        free((*lista)[i]); //Liberamos memoria
        (*lista)[i] = NULL; //Asignamos NULL
        i++; //Incrementamos el indice
    }
}

char * getFile(tLista lista, int fd){
    int mod = fcntl(fd,F_GETFL);
    printf("descriptor: %d -> %s, %d\n",fd, lista[fd]->cadena, mod);
}