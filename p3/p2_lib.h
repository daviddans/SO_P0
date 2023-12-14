//Cabecera con las funciones de la practica anterior

#include "p1_lib.h" //Inclusion de librerías de las practicas antetriores

#define TAMANO 2048

void doMalloc(char* args, char** args_ptr, tList* memory); //reserva o libera un bloque malloc de memoria
void doShared(char* args, char** args_ptr, tList* memory); //reserva o libera un bloque shared de memoria
void doMmap(char* args, char** args_ptr, tList* memory); //mapea o desmapea un fichero en memoria
void doRead(char* args, char** args_ptr); //lee un fichero en memoria
void doWrite(char* args, char** args_ptr); //escribe en un fichero los contenidos de una dirección de memoria
void doMemdump(char* args, char** args_ptr); //vuelca los contenidos de una dirección de memoria en la pantalla
void doMemfill(char* args, char** args_ptr); //llena la memoria con el mismo byte
void doMem(char* args, char** args_ptr, tList* memory); //muestra información de la memoria de los procesos
void doRecurse(int n); //ejecuta una funcion recursiva

void printMemBlocks(tList lista); //Mostrar bloques de memoria de una lista
void printMemBlocksType(tList lista, Type tipo); //Mostrar bloques de memoria de una lista (Filtrando por tipo)