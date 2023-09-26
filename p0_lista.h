//Cabecera de la lista (Usaremos la misma implementación para los comandos y los ficheros, por lo que habra funciones para cada tipo, y habŕa que controlar el no mezclarlos)
#include "p0_lib.h"
#define MAX_LEN_LIST 4096 //elementos maximos en una lista

//Definicion de tipos
struct item { //Struct con 3 campos para guardar comandos o ficheros
    char* cadena; //Cadena para guardar un comando / un directorio
    int fileD; //File descriptor
    int mod; //Modo de apertura
};
typedef struct item* tItemL;//Tipo de dato a guardar en la lista (puntero a struct item)
typedef tItemL tLista[MAX_LEN_LIST]; //Definicion de la lista (Array de punteros)

//Funciones de la lista
void createEmptyList(tLista* lista); //Inicializa una lista a vacia
bool instertComand(tLista* lista, char* cmd); //Inserta un comando a la lista
bool insertFile(tLista* lista,char* path, int fd, int mod); //Inserta la información de un fichero
bool deleteList(tLista* lista); //Borrar una lista
bool returnComand(tLista lista, int n, char* dest); //Coloca en dest una cadena con el comando numero n
tItemL returnFile(tLista lista, int n); //Devuelve un struct tItemL con los datos del fichero numero n
bool deleteFile(tLista* list, int df); //Busca el fichero con el df correspondiente y lo borra
