#include "p0_lista.h"

void createEmptyList(tLista* lista){
    *(*lista)[0] = NULL; //Colocar el primer indice a null
}

bool createNode(tItemL* item, char* str, int fd, int mod){ //funcion auxiliar para realizar el malloc de un elemento a introducir
    *item = malloc(sizeof(tItemL));
    if(*item == NULL) //Comprobamos que se pudo realizar la reserva de memoria
    {
        return false;
    }
    if(fd<0){ //Si fd negativo, consideramos crear un comando
        memcpy((*item)->cadena,str,strlen(str)); //Copiamos el argumento str en el campo cadena
        (*item)->fileD = -1; //Consideramos -1 como un fd no valido, por tanto será un comando
        (*item)->mod = -1; //Consideramos -1 como un mode no valido, por tanto será un comando
    }
    else{ //Consideramos crear un fichero
        memcpy((*item)->cadena,str,strlen(str)); //Copiamos el argumento str en el campo cadena
        (*item)->fileD = fd; //Copiamos el file descriptor
        (*item)->mod = -1; //Copiamos el mode
    }
    return true;
}

bool instertComand(tLista* lista, char* cmd){
    tItemL item = NULL;
    int i = 0;
    if(createNode(&item, cmd, -1, -1)){
        while((*lista)[i] != NULL)
        {
            i++;
        }
        (*lista)[i] = item;
        (*lista)[i+1] = NULL;
        return true;
    }
    else return false;  
}