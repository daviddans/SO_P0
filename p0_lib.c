//Codigo de la practica p0
#include "p0_lib.h"


//Salir de la Shell
void exitShell(bool *b){
    printf("\nSaliendo de la shell ^^\n"); //mensaje de salida
    *b = false; //variable de entrada a falso
    return;
}
//Imprimir mensajes de ayuda de los comandos. Solo se tiene en cuenta el primer parametro de args
void help(char *args){ 
    // Si no recibe argumentos, imprimir una lista de los comandos disponibles
    if(args==NULL)puts("quit :: exit :: bye :: help [cmd] :: authors [-n|-l] :: date :: time :: pid [-p] :: chdir [dir] :: hist [-c|-N] :: command [N] :: open [file][mode] ::\n");
    //Ayuda sobre el comando help
    else if(strcmp(args,"help") == 0) puts("help muestra una lista de los comandos disponibles\n  help [comando] muestra una ayuda detallada del comando\n");
    //Ayuda sobre los comandos exit, quit, y bye
    else if(strcmp(args,"quit")==0 || strcmp(args,"exit")==0 || strcmp(args,"bye")==0 ) printf("%s cierra el programa de shell actual\n",args);
    //Ayuda sobre authors
    else if(strcmp(args,"authors")== 0) puts("authors muestra por pantalla nombre y login de los autores\n  authors -l mostrara solo login\n  authors -n mostrara solo nombres\n");
    //Ayuda sobre el comando date
    else if(strcmp(args,"date")== 0) puts("date muestra la fecha del sistema\n");
    //Ayuda sobre el comando time
    else if(strcmp(args,"time")== 0) puts("time muestra la hora del sistema\n");
    //Ayuda sobre el comando pid
    else if(strcmp(args,"pid")== 0) puts("pid muestra el identificador de la shell actual\n pid -p muestra el identificador del proceso padre\n");
    //Ayuda sobre el comando time
    else if(strcmp(args,"chdir")== 0) puts("chdir muestra el directorio actual\n  chdir [dir] cambia el directorio actual al especificado\n");
    //Ayuda sobre el comando hist
    else if(strcmp(args,"hist")== 0) puts("hist muestra el historial de comandos\n  hist [-c] borra el historial\n  hist [-N] imprime los N primeros comandos\n");
    //Ayuda sobre el comando command
    else if(strcmp(args,"command")== 0) puts("command [N] ejecuta de nuevo el comando numero N del historico\n  command sin argumentos muestra el historico\n");
    //Ayuda sobre el comando open
    else if(strcmp(args,"open")== 0) puts("Open [file] [mode] sirve para abrir un archivo\n   [file] especifica la ruta\n   [mode] especifica los parametros de apertura(cr,ex,ro,wo,rw,ap,tr)\n   Si no hay argumentos se listaran los archivos ya abiertos\n");
    //Si se introduce un comando no reconocido se mostrara un mensaje de error
    else puts("Error: Comando no reconocido\n");
}
//Imprimir mensajes con los datos de los autores
void authors(char *args){
    char str[190];//String para guardar el mensaje a imprimir
    //Si no tiene argumentos se guardan todos los datos
    if(args == NULL) strcpy(str,"\nAutores:\nNombre del autor 1: David Dans Villares Login del autor 1: david.dans.villares@udc.es\nNombre del autor 2: Pablo Teijeiro Torrón Login del autor 2: pablo.teijeirot@udc.es");
    //El parametro -l guarda solo logins
    else if(strcmp(args,"-l") == 0) strcpy(str,"\nAutores:\nLogin del autor 1: david.dans.villares@udc.es\nLogin del autor 2: pablo.teijeirot@udc.es");
    //El parametro -n guarda solo nombres
    else if(strcmp(args,"-n") == 0) strcpy(str,"\nAutores:\nNombre del autor 1: David Dans Villares\nNombre del autor 2: Pablo Teijeiro Torrón");
    //Si se introduce un parametro no valido se guarda un mensaje de error
    else {
        strcpy(str,"Error: authors no reconoce el parametro: "); //Creamos un mensaje de error
        strcat(str,args); //Le añadimos el comando erroneo introducido
    }
    printf("%s\n",str);//Imprimir string guardada
}
//Imprimir fecha del sistema
void printDate(){
    char date_now[15]; //String para guardar la fecha
    time_t t; //Variable para guardar la hora
    struct tm *calendar; //Variable para guardar el calendario
    time(&t); //Tomamos la hora del sistema
    calendar = localtime(&t); //Creamos un calendario con la hora del sistema
    strftime(date_now,15,"%d/%m/%Y",calendar); //Creamos un string con el formato deseado
    printf("date : %s\n",date_now); //Mostramos la fecha por pantalla
}
//Imprimir fecha del sistema
void printTime(){
    char time_now[15]; //String para guardar la hora
    time_t t; //Variable para guardar la hora
    struct tm *calendar; //Variable para guardar el calendario
    time(&t); //Tomamos la hora del sistema
    calendar = localtime(&t); //Creamos un calendario con la hora del sistema
    strftime(time_now,15,"%X",calendar); //Creamos un string con el formato deseado
    printf("time : %s\n",time_now); //Mostramos la fecha por pantalla
}
//Imprimir el identificador de proceso
void pid(char *args){
    if(args == NULL) printf("pid: %d\n",getpid()); // Si no hay parametros se imprime el pid del proceso actual
    else if(strcmp(args,"-p")==0) printf("parent pid: %d\n",getppid()); // -p imprime el pid del proceso padre
    else printf("Error: el comando pid no reconoce el parametro: %s",args); // Ante un parametro no valido se imprime un mensaje de error
}
//Mostrar o cambiar directorio
void changeDir(char *args){
    char dir[Max_len_dir]; //Creamos una variable para guardar el directorio actual
    if(args == NULL){ // Si no hay argumentos
        getcwd(dir,Max_len_dir);
        if(dir != NULL) printf("Directorio actual: %s\n",dir); //Guardamos el directorio actual y lo imprimimos
        else perror("\n");
    }
    //Si hay argumentos 
    else if(chdir(args)!=0) perror("Error(chdir): "); //Se intenta cambiar al directorio introducido, si no se logra, imprimir un error
}
//Usar el historico de comandos
void hist(char* args, tList* lista){
    int n = 0;
    if(isEmptyList(*lista)) puts("Error en el historial de comandos\n");
    else {
        args = strtok(args,"-");
        if(args == NULL){ //Si no hay argumentos validos
            printCMD(*lista, -1); // Imprimir todos los comandos
        }
        else if(strcmp(args,"c")== 0){ //Argumento -c (borrar la lista)
            deleteList(lista);
        }
        else{ //Resto de argumentos
            n = atoi(args);
            if(n > 0) printCMD(*lista, n);
            else printf("El comando hist no reconoce el parametro: %s\n",args);
        }
    }
}

void printFiles(tList lista){ //Funcion auxiliar para imprimir la lista de archivos abiertos
    tPos i = first(lista); //Puntero al primero de la lista
    tFile* file = NULL; // Puntero a un fichero
    int mode = 0; // int para guardar el modo 
    char mode_s[100] = "\0"; //string para imprimir los modos
    while(i != NULL){ // Recorremos la lista hasta el final para imprimir cada elemento
        file = getData(lista, i); //Recuperamos el fichero
        mode = fcntl(file->fd, F_GETFL); //Recuperamos el modo de apertura
        //Añadimos a mode_s todos los modos a imprimir
        if((mode & O_CREAT) == O_CREAT) strcat(mode_s," O_CREAT");
        if((mode & O_EXCL) == O_EXCL) strcat(mode_s," O_EXCL");
        if((mode & O_RDWR) == O_RDWR) strcat(mode_s," O_RDWR");
        if((mode & O_RDONLY) == O_RDONLY && (mode & O_RDWR) != O_RDWR) strcat(mode_s," O_RDONLY");
        if((mode & O_WRONLY) == O_WRONLY && (mode & O_RDWR) != O_RDWR) strcat(mode_s," O_WRONLY");
        if((mode & O_APPEND) == O_APPEND) strcat(mode_s," O_APPEND");
        if((mode & O_TRUNC) == O_TRUNC) strcat(mode_s," O_TRUNC");
        printf("descriptor: %d ---> %s%s\n",file->fd, file->path, mode_s); //Imprimimos todos los datos del fichero
        i = next(lista, i); //Pasamos al siguiente
        mode_s[0] = '\0'; //Reseteamos mode_s
    }
}

void openfile(char* args, tList* lista){ //Abrir un fichero
    int mode = 0; //int para guardar el mode
    int fd = -1; //int para guardar el fd
    char* path = NULL; //int para guardar la ruta del archivo
    if(args == NULL) printFiles(*lista); //Si no hay argumentos : Imprimir archivos abiertos
    else{
        path = malloc(sizeof(char)*strlen(args)); //Reservamos memoria para guardar la direccion.
        strcpy(path, args); //Copiamos la direccion
        args = strtok(NULL," \n\t"); //Siguiente argumento
        while(args != NULL){ //Comprobar modos introducidos
            if (!strcmp(args,"cr")) mode|=O_CREAT;
            else if (!strcmp(args,"ex")) mode|=O_EXCL;
            else if (!strcmp(args,"ro")) mode|=O_RDONLY; 
            else if (!strcmp(args,"wo")) mode|=O_WRONLY;
            else if (!strcmp(args,"rw")) mode|=O_RDWR;
            else if (!strcmp(args,"ap")) mode|=O_APPEND;
            else if (!strcmp(args,"tr")) mode|=O_TRUNC; 
            else {
                printf("Error: Flag %s no valido\n", args);//Control de error de argumento no valido
            }
            args = strtok(NULL," \n\t");//Siguiente argumento
        }
        fd = open(path, mode); //Llamada al sistema y guardamos el fd resultante
        if(fd > 0) {
             //Si obtenemos un fd valido imprimimos una confirmación
            if(insertFile(lista, path, fd)) printf("Añadida entrada nº %d (%s) a la lista de ficheros abiertos\n",fd, path); //Añadimos el fichero abierto a la lista
            else puts("Error al intentar añadir elemento a la lista\n");
        }
        else perror("Error:"); //Si hay un error imprimimos el mensaje de error estandard del so
        free(path); //Liberamos la memoria guardada
    }
}
