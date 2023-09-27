#include "p0_lib.h"//Fichero con las dependencias del codigo
#define Max_len_dir 500

//Funciones vinculadas a comandos de la shell
//Salir de la Shell
void exitShell(bool *b){
    printf("\nSaliendo de la shell ^^\n"); //mensaje de salida
    *b = false; //variable de entrada a falso
    return;
}
//Imprimir mensajes de ayuda de los comandos. Solo se tiene en cuenta el primer parametro de args
void help(char *args){ 
    // Si no recibe argumentos, imprimir una lista de los comandos disponibles
    if(args==NULL)puts("quit exit bye help [cmd] authors [-n|-l] date time pid [-p] chdir [dir]\n");
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
        if(getcwd(dir,Max_len_dir)==0) printf("Directorio actual: %s\n",dir); //Guardamos el directorio actual y lo imprimimos
        else perror("La longidud del directorio actual excede la esperada\n");
    }
    //Si hay argumentos 
    else if(chdir(args)!=0) printf("Error: Directorio: %s no encontrado.\n",args); //Se intenta cambiar al directorio introducido, si no se logra, imprimir un error
}