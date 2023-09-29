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
typedef struct node* tPos; 
struct node{
    void* data;
    tPos next;
};
typedef tPos tList;

//funciones generales
void createEmptyList(tList* lista); // Inicializa una lista vacia
bool isEmptyList(tList lista); //Devuelve true si la lista esta vacia, false en otro caso
tPos next(tList lista, tPos p); //Devuelve la posición siguiente a una dada, o nulo si es la ultima
tPos first(tList lista); //Devuelve la primera posición de una lista
void* getData(tList lista, tPos p);//Devuelve un puntero void que apunta a un dato de la lista dada su posición
//Funciones especificas de un tipo de dato
int countCMD(tList lista); //Devuelve el numero de comandos de una lista 
bool insertCMD(tList* lista, cmd comdando); //Inserta un comando en la lista(Unicamente se añaden al final de la lista)
char* getCMD(tList lista, int n); //Devuelve el puntero del dato del item numero n como un puntero a cadena
bool insertFCH(tList* lista, char* str, int fd); //Inserta un fichero 
tFile* getFHC(tList lista, int fd); //Devuelve un puntero a un fichero con cierto fd de una lista, o NULL si no se ha encontrado
bool deleteFCH(tList* lista, int fd);// Borra un fichero con cierto fd de la lista
void deleteCMDList(tList* lista); //Devuelve una lista vacia(suponemos que no lo estaba previamente), habiendo liberado la memoria de forma correcta