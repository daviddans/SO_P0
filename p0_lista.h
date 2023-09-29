//Se Reutiliza parte del codigo para la lista de ficheros y la de comandos, por lo que el dato es un puntero void* y habra funciones analogas para cada tipo
//Particularidades : 
//En la lista de comandos se insertan todos al final, y solo se borran las listas completas
//En la lista de ficheros se ordenaran por fd(file descriptor) y si se pueden hacer borrados por el medio

#include "p0_lib.h"
//Definicion de tipos
typedef char* cmd; //Definimos un tipo para los comandos
typedef struct file{ //Definimos un tipo para los ficheros
    char* path;
    int fd;
}tFile;
//Definicion de lista dinamica
typedef struct item* tPos; 
struct item{
    void* data;
    tPos next;
};
typedef tPos tList;

void createEmptyList(tList* lista); // Inicializa una lista vacia
bool isEmptyList(tList lista); //Devuelve true si la lista esta vacia, false en otro caso
int countCMD(tList lista); //Devuelve el numero de comandos de una lista 
bool insertCMD(tList* lista, cmd comdando); //Inserta un comando en la lista(Unicamente se añaden al final de la lista)
char* getCMD(tList lista, int n); //Devuelve el puntero del dato del item numero n como un puntero a cadena
bool insertFCH(tList* lsita, char* str, int fd); //Inserta un fichero 


void deleteCMDList(tList* lista); //Devuelve una lista vacia(suponemos que no lo estaba previamente), habiendo liberado la memoria de forma correcta