#include "p0_lista.h"

void createEmptyList(tLista* lista){
    *lista[0] = NULL; //Colocar el primer indice a null
}

bool createNode(tItemL* item, char* str, int mode, bool type){ //funcion auxiliar para realizar el malloc de un elemento a introducir
    *item = malloc(sizeof(struct item));
    if(*item == NULL) //Comprobamos que se pudo realizar la reserva de memoria
    {
        return false;
    }
    (*item)->cadena = NULL;//inicializamos cadena
    if(type){ //Si type true, consideramos crear un comando
        (*item)->cadena = str;//Copiamos el argumento str en el campo cadena
        (*item)->mod = -1; //Consideramos -1 como un mode no valido, por tanto será un comando
    }
    else{ //Consideramos crear un fichero
        (*item)->cadena = str; //Copiamos el argumento str en el campo cadena
        (*item)->mod = mode; //Copiamos el mode
    }
    return true;
}
bool insertComand(tLista* lista, char* cmd){
    tItemL item = NULL; //Nuevo item
    int i = 0; //Iniciamos contador
    if(createNode(&item, cmd, -1, true)){ //Si se consigue reservar memoria
        while((*lista)[i] != NULL) //Recorremos la lista hasta encontrar el primer hueco
        {
            i++;
        }
        if(i<MAX_LEN_LIST -1){//Comprobamos que la lista no este llena
            (*lista)[i] = item; //Guardamos el objeto en el ultimo
            (*lista)[i+1] = NULL; //Fijamos la siguiente posición en null
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

bool insertFile(tLista* lista, char* path, int mode){
    tItemL item = NULL; //Nuevo item
    int i = 0; //Iniciamos contador
    if(createNode(&item, path, mode, false)){ //Si se consigue reservar memoria
        while((*lista)[i] != NULL) //Recorremos la lista hasta encontrar el primer hueco
        {
            i++;
        }
        if(i<MAX_LEN_LIST -1){//Comprobamos que la lista no este llena
            (*lista)[i] = item; //Guardamos el objeto en el ultimo
            (*lista)[i+1] = NULL; //Fijamos la siguiente posición en null
            return true; //Exito devolvemos true
        }
    }
    return false;  //En caso de fallo devolvemos false
}

void deleteFile(tLista* lista, int n){
    free((*lista)[n]); //Liberamos el contenido de lista[n]
    (*lista)[n] = NULL; //Ponemos lista[n] a NULL
}

void deleteList(tLista* lista, int n){
    int i = 0; // Iniciamos un contador
    if(n<0) n = MAX_LEN_LIST; //Si n negativo, comprobaremos todo el array
    while(i<n){ //Recoremos el array entero
        free((*lista)[i]); //Liberamos memoria
        (*lista)[i] = NULL; //Asignamos NULL
        i++; //Incrementamos el indice
    }
}