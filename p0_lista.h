//Cabecera de la lista (Usaremos la misma implementación para los comandos y los ficheros, por lo que habra funciones para cada tipo, y habŕa que controlar el no mezclarlos)
#include "p0_lib.h"
#define MAX_LEN_LIST 4096 //elementos maximos en una lista

//Definicion de tipos
struct item { //Struct con 2 campos para guardar comandos o ficheros
    char* cadena; //Cadena para guardar un comando / un directorio
    int mod; //Modo de apertura (solo fichero)
};
typedef struct item* tItemL;//Tipo de dato a guardar en la lista (puntero a struct item)
typedef tItemL tLista[MAX_LEN_LIST]; //Definicion de la lista (Array de punteros)

//Funciones de la lista
void createEmptyList(tLista* lista); //Inicializa una lista a vacia
bool insertComand(tLista* lista, char* cmd); //Inserta un comando a la lista
char * getCommand(tLista lista, int n); //Devuelve el comando numero n de una lista
bool insertFile(tLista* lista, char* path, int mode); //Inserta la información de un fichero
void printFile(tLista* lista, int fd); //Imprime los datos del fichero con cierto fd de la lista dada

//Borrar una lista entera. Se enfoca en borrar listas de comandos, ya que no se da el caso para los ficheros
//n es el numero de comandos(usado para agilizar la tarea, si se pasa un numero negativo se revisara toda la lista)
void deleteList(tLista* lista, int n);

//Borra el fichero n de una lista (Los elementos no se desplazaran de su indice) 
//deleteFile no existe ya que no se da el caso de que se borre un unico comando de la lista
//Aunque esta función serviria para ese proposito, no esta contemplado, y daría lugar a errores
void deleteFile(tLista* lista, int n);
