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
    size_t tam = 0;
    void* memPtr = NULL;
    tPos memPos = NULL;
    tMemBlock* memBlock = NULL;
    time_t allocTime;
    if(args == NULL){
        printf("******Lista de bloques asignados malloc para el proceso %d\n",pid);
        printMemBlocksType(*memory, mal); //Sin argumentos imprimimos reservas de malloc hechas
    }
    else if(strcmp(args,"-free") == 0){
        args = strtok_r(NULL," \n\t", args_ptr);
        if(args !=NULL) tam = atoi(args);
        if(tam > 0)memPos = searchBySiceAndType(*memory,tam,mal); //Buscamos Coincidendicas
        if(memPos == NULL) printf("Error: en malloc -free, no se encuentran bloques de %lu bytes\n", tam); //Control errores
        else{ 
            memBlock = (tMemBlock*)getData(*memory,memPos);
            free(memBlock->addres); //Liberamos memoria
            printf("freed addres : %p\n", memBlock->addres);
            deleteMemBlockIn(memory, memPos); //Borramos de la lista
        }
    }
    else{
        tam = atoi(args);
        if(tam == 0) printf("No se pueden reservar bloque de 0 bytes\n");
        else{
            memPtr = malloc(tam); //Reservamos memoria
            if(memPtr == NULL) perror("Error: en malloc\n"); //Control errores
            else{
                time(&allocTime);
                tMemBlock* myNewMemBlock = newMemBlock(memPtr,tam,allocTime,mal,0,NULL,0);
                insertMemBlock(memory,myNewMemBlock);
                printf("Asignados %lu bytes en %p\n",tam,memPtr);
            }
        }
    }
}

void LlenarMemoria (void *p, size_t cont, unsigned char byte)
{
  unsigned char *arr=(unsigned char *) p;
  size_t i;

  for (i=0; i<cont;i++)
		arr[i]=byte;
}

void doMemfill(char* args, char** args_ptr){
    void* addr;
    size_t nBytes;
    unsigned char byte;
    if(args != NULL){
        addr = (void*)strtol(args,NULL,16);
        args = strtok_r(NULL," \n\t",args_ptr);
        nBytes = strToInt(args);
        args = strtok_r(NULL," \n\t",args_ptr);
        byte = strToInt(args);
        printf("Llenando %lu bytes de memoria con el byte (%.2X) a partir de la direccion %p\n",nBytes,byte,addr);
        LlenarMemoria(addr, nBytes, byte);
    }
}

void doMemdump(char* args, char** args_ptr){
    unsigned char* addr;
    size_t nBytes;
    if(args != NULL){
        addr = (unsigned char*)strtol(args,NULL,16);
        args = strtok_r(NULL," \n\t",args_ptr);
        nBytes = strToInt(args);
        args = strtok_r(NULL," \n\t",args_ptr);
        printf("Volcando %lu bytes de memoria desde la direccion %p\n",nBytes,addr);
        for (size_t i = 0; i<nBytes; i++){
            printf(" %.2X ", addr[i]);
        }
        printf(":END:\n");
    }
}