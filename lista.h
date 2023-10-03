//Se usa la misma implementación para la lista de ficheros y la de comandos, por lo que el dato es un puntero void* y habra funciones para cada tipo

//Includes (librerias para toda la practica)
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/utsname.h>
#include <sys/stat.h> 

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
tPos last(tList lista); //Devuelve la ultima posición de una lista
void* getData(tList lista, tPos p);//Devuelve un puntero void que apunta a un dato de la lista dada su posición
void deleteList(tList* lista); //Vacia una lista(suponemos que no lo estaba previamente), habiendo liberado la memoria de forma correcta
//Funciones especificas de un tipo de dato
bool insertCMD(tList* lista, cmd comdando); //Inserta un comando en la lista(Unicamente se añaden al final de la lista)
void printCMD(tList lista, int n);  // Imprime los primeros n comandos. Si n<0 se imprimiran todos los comandos
bool insertFile(tList* lista, char* str, int fd); //Inserta un fichero 
bool deleteFile(tList* lista, int fd);// Borra un fichero con cierto fd de la lista
