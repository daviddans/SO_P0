#include "p2_lib.h"


void memTypeToStr(Type tipo, char buff[8]){ //Funcion auxiliar para convertir enumType en str

    switch (tipo)
    {
        case mal: strcpy(buff,"malloc");
        break;
        case shm: strcpy(buff,"shared");
        break;
        case map: strcpy(buff,"mmap");
        break;
        default: strcpy(buff,"NULL");
            break;
    }
}

void printfMemBlk(tMemBlock memBlock){ //Funcion auxiliar para imprimir los datos de un bloque de memoria
    struct tm* calendar;
    char timeStr[30];
    Type t = memBlock.tipo; //Guardamos tipo
    char tipo[8];
    memTypeToStr(t,tipo); //Guardamos nombre del tipo en string
    calendar = localtime(&memBlock.allocTime); //Creamos struc tm con la hora de reserva
    strftime(timeStr,30,"%d/%m/%Y %X",calendar); //Creamos un string con el formato deseado
    if(t == mal) printf("%6p%12lu %s %s\n",memBlock.addres,memBlock.size,timeStr,tipo); //Imprimir malloc
    else if(t == shm) printf("%-6p%20lu %s %s (key %d)\n",memBlock.addres,memBlock.size,timeStr,tipo,memBlock.key); //Imprimir shared
    else if(t == map) printf("%-6p%20lu %s %s (descriptor %d)\n",memBlock.addres,memBlock.size,timeStr,getNombre(memBlock.filename), memBlock.fd); //Imprimir malloc
    else printf("Error: printing memory list Type not found\n");
}

void printMemBlocks(tList lista){ //Imprime lista de memoria
    tMemBlock* memBlock;
    tPos i = lista;
    while ( i != NULL)
    {
        memBlock = i->data;
        printfMemBlk(*memBlock);
        i = i->next;   
    }
}

void printMemBlocksType(tList lista, Type tipo){ //Imprime lista de memoria (filtrado)
    tMemBlock* memBlock;
    tPos i = lista;
    while ( i != NULL)
    {
        memBlock = i->data;
        if(memBlock->tipo == tipo) printfMemBlk(*memBlock);
        i = i->next;   
    }
}

void doRecurse(int n)
{
    if(n >= -1) printf("Error en recurse: argumento invalido");
    else {
        char automatico[TAMANO];
        static char estatico[TAMANO];   
        printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico); 
        if (n>0) doRecurse(n-1);
    }
}   

void doMalloc(char* args, char** args_ptr, tList* memory){ //Reserva bloques de memoria
    int pid = getpid();
    size_t tam;
    void* memPtr;
    tPos memPos;
    tMemBlock* memBlock;
    time_t allocTime;
    if(args == NULL){
        printf("******Lista de bloques asignados malloc para el proceso %d\n",pid);
        printMemBlocksType(*memory, mal); //Sin argumentos imprimimos reservas de malloc hechas
    }
    else if(strcmp(args,"-free") == 0){
        strtok_r(args," \n\t", args_ptr);
        tam = atoi(args);
        memPos = searchBySiceAndType(*memory,tam,mal); //Buscamos Coincidendicas
        if(memPos == NULL) printf("Error: en malloc -free\n"); //Control errores
        else{ 
            memBlock = getData(*memory,memPos);
            free(memBlock->addres); //Liberamos memoria
            deleteMemBlockIn(memory, memPos); //Borramos de la lista
        }
    }
    else{
        tam = atoi(args);
        memPtr = malloc(tam); //Reservamos memoria
        if(memPtr == NULL) perror("Error: en malloc\n"); //Control errores
        else{
            time(&allocTime);
            insertMemBlock(memory,newMemBlock(memPtr,tam,allocTime,mal,0,NULL,0)); //Añadimos entrada en la lista de memoria
            printf("Asignados %lu bytes en %p\n",tam,memPtr);
        }
    }
}