#include "p1_lib.h"
void create(char *args){ //Crear archivos o directorios
    int fd;
    if(args == NULL) changeDir(args); //Sin argumentos imprimimos directorio actual
    else {
        if(strcmp(args,"-f") == 0){ //Comprobamos si imprimimos un archivo o directorio
            args = strtok(NULL," \n\t");
            if((fd = creat(args,0777))==-1) perror("\nError en create: "); //Tratamos de crear el archivo
            else close(fd);  //Si logramos crear el archivo borramos su file descriptors
        }else if(mkdir(args,0777)==-1) perror("\nError en create: "); //Tratamos de crear el directorio
    }
} 