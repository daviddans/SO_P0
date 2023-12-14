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
    if(args==NULL) puts("quit :: exit :: bye :: help [cmd] :: authors [-n|-l] :: date :: time :: pid [-p] :: chdir [dir] :: hist [-c|-N] :: command [N] :: open [file][mode] :: close [fd] :: dup [fd] :: listopen :: infosys\ncreate [-f] name :: stat [-long][-link][-acc] name1 name2... :: list [-reca][-recb][-hid][-long][-accl] name1,... :: delete name1, name2 ... :: deltree name1, name2 ...\n");
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
    else if(strcmp(args,"open")== 0) puts("open [file] [mode] sirve para abrir un archivo\n   [file] especifica la ruta\n   [mode] especifica los parametros de apertura(cr,ex,ro,wo,rw,ap,tr)\n   Si no hay argumentos se listaran los archivos ya abiertos\n");
    //Ayuda sobre el comando close
    else if(strcmp(args,"close")== 0) puts("close [fd] sirve para eliminar la entrada del fichero correspondiente al fd\nSi no hay argumentos se listaran los archivos ya abiertos\n");
    //Ayuda sobre el comando dup
    else if(strcmp(args,"dup")== 0) puts("dup [fd] sirve para duplicar la entrada del fichero correspondiente al fd\nSi no hay argumentos se listaran los archivos ya abiertos\n");
    //Ayuda sobre el comando listopen
    else if(strcmp(args,"listopen")== 0) puts("listopen sirve para mostrar la lista de archivos abiertos\n");
    //Ayuda sobre el comando infosys
    else if(strcmp(args,"infosys")== 0) puts("infosys sirve para mostrar las caracteristicas de la maquina actual\n");
    //Ayuda sobre el comando create
    else if(strcmp(args,"create")== 0) puts("create crea un nuevo archivo o directorio\n   [-f] especifica crear un fichero (por defecto sera directorio)\n   [name] sera el nombre el fichero/directorio creado\n");
    //Ayuda sobre el comando stat
    else if(strcmp(args,"stat")== 0) puts("stats muestra propiedades de ficheros\n   [-long] muestra un listado largo\n   [-acc] muestra el accestime(solo para -long)\n   name1, name2... seran los nombres de archivos a imprimir su estatus\n");
    //Ayuda sobre el comando list
    else if(strcmp(args,"list")== 0) puts("list muestra el estado de los ficheros de un directorio\n   [-reca | -recb] para listar directorios recursivamente(despues/antes)\n  [-hid] listar ficheros ocultos\n   [-long][-acc][-link] ver help stat");
    //Ayuda sobre el comando delete
    else if(strcmp(args,"delete")== 0) puts("delete borra los archivos o carpetas vacias especificados\n \n");
    //Ayuda sobre el comando deltree
    else if(strcmp(args,"deltree")== 0) puts("delrtee borra recursivamente todo archivo y directoro contenido en las rutas dadas y sus subrutas\n   Usar con discrección la informacion borrada accidentalmente podria no ser recuperada");
    //Ayuda sobre malloc
    else if(strcmp(args,"malloc")== 0) puts("PlaceHolder(WIP)\n");
    //Ayuda sobre shared
    else if(strcmp(args,"shared")== 0) puts("PlaceHolder(WIP)\n");
    //Ayuda sobre mmap
    else if(strcmp(args,"mmap")== 0) puts("PlaceHolder(WIP)\n");
    //Ayuda sobre read
    else if(strcmp(args,"read")== 0) puts("PlaceHolder(WIP)\n");
    //Ayuda sobre write
    else if(strcmp(args,"write")== 0) puts("PlaceHolder(WIP)\n");
    //Ayuda sobre memdump
    else if(strcmp(args,"memdump")== 0) puts("PlaceHolder(WIP)\n");
    //Ayuda sobre memfill
    else if(strcmp(args,"memfill")== 0) puts("PlaceHolder(WIP)\n");
    //Ayuda sobre mem
    else if(strcmp(args,"mem")== 0) puts("PlaceHolder(WIP)\n");
    //Ayuda sobre el comando recurse
    else if(strcmp(args,"recurse")== 0) puts("recurse n Invoca a la funcion recursiva n veces\n");
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
void hist(char* args, char**args_ptr, tList* lista){
    int n = 0;
    if(isEmptyList(*lista)) puts("Error en el historial de comandos\n");
    else {
        args = strtok_r(args,"-",args_ptr);
        if(args == NULL){ //Si no hay argumentos validos
            printCMD(*lista, -1); // Imprimir todos los comandos
        }
        else if(strcmp(args,"c")== 0){ //Argumento -c (borrar la lista)
            deleteListCMD(lista);
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
        mode = file->mode; //Recuperamos el modo de apertura guardado en la lista
        mode |= fcntl(file->fd, F_GETFL); //Añadimos los que tenga el sistema guardado
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

void openfile(char* args, char** args_ptr, tList* lista){ //Abrir un fichero
    int mode = 0; //int para guardar el mode
    int fd = -1; //int para guardar el fd
    char* path = NULL; //int para guardar la ruta del archivo
    if(args == NULL) printFiles(*lista); //Si no hay argumentos : Imprimir archivos abiertos
    else{
        path = malloc(sizeof(char)*strlen(args)+1); //Reservamos memoria para guardar la direccion.
        strcpy(path, args); //Copiamos la direccion
        args = strtok_r(NULL," \n\t", args_ptr); //Siguiente argumento
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
            args = strtok_r(NULL," \n\t",args_ptr);//Siguiente argumento
        }
        fd = open(path, mode,0777); //Llamada al sistema y guardamos el fd resultante
        if(fd > 0) {
             //Si obtenemos un fd valido imprimimos una confirmación
            if(insertFile(lista, path, fd, mode)) printf("Añadida entrada nº %d (%s) a la lista de ficheros abiertos\n",fd, path); //Añadimos el fichero abierto a la lista
            else puts("Error al intentar añadir elemento a la lista\n");
        }
        else perror("Error:"); //Si hay un error imprimimos el mensaje de error estandard del so
    }
     free(path); //Liberamos la memoria guardada
}

int strToInt(char* str){ // Funcion auxiliar para convertir strings en enteros positivos con un control de errores añadido
    int r;
    bool isNum = true;
    if(str != NULL){
        for (int i = 0; str[i] != '\0'; i++){ //comprobamos si el string dado es convertible
            if(str[i]<48 || str[i] > 57){
                isNum = false; 
                break;
            }
        }
    }
    else isNum = false;
    if(isNum) r = atoi(str); //Si es convertible usamos la funcion atoi para convertirlo en entero
    else r = -1; //En otro caso devolvemos -1 para controlar los posibles errores
    return r;
}

void dupfile(char* args, tList* lista){ //Clonar el fd de un fichero abierto
    int fd; //int para guardar el fd
    int fd2 = -1; //int para guardar el fd de la copia
    tFile* file = NULL; //puntero para guardar el fichero a duplicar
    char* path = NULL; //String para guardar el nombre / ruta del fichero duplicado
    if(args == NULL) printFiles(*lista); //Si no hay argumentos : Imprimir archivos abiertos
    else{
        fd = strToInt(args);
        if((fd2=dup(fd)) == -1) perror("Error:"); //Llamada al sistema y guardamos el fd resultante. Si hay un error imprimimos el mensaje de error estandard del so
        else{ //Duplicamos la entrada en la lista de ficheros
            file = searchFile(*lista, fd)->data; //Buscamos el fichero duplicado
            path = malloc(sizeof(char)*strlen(file->path)+15); //Reservamos memoria para construir el nombre del fichero
            path[0] = '\0';
            strcat(path, "dup ");
            strcat(path, args);
            strcat(path, " ");
            strcat(path, file->path);
            if(insertFile(lista, path, fd2, fcntl(file->fd, F_GETFL))) printf("Duplicada entrada nº %d a la lista de ficheros abiertos\n",fd); 
            else puts("Error al insertar en la lista\n"); //Error si no se duplica la entrada en la lista
            free(path); //Liberamos la memoria guardada
        }
    }
}

void closefile(char* args, tList* lista){ //Cerrar un fichero abierto
    int fd; //int para guardar el fd
    if(args == NULL) printFiles(*lista); //Si no hay argumentos : Imprimir archivos abiertos
    else{
        fd = strToInt(args);
        if(close(fd) == -1) perror("Error al cerrar un archivo:"); //Llamada al sistema y guardamos el fd resultante. Si hay un error imprimimos el mensaje de error estandard del so
        else{ //Duplicamos la entrada en la lista de ficheros
            if(deleteFile(lista, fd)) printf("Borrada entrada nº %d en la lista de ficheros abiertos\n",fd); 
            else puts("Error al borrar en la lista\n"); //Error si no se duplica la entrada en la lista
        }
    }
}

void listopen(char* args, tList* lista){
    if(args == NULL) printFiles(*lista); 
    else puts("Error: listopen no recibe mas argumentos");
}

void infosys(char* args){
    struct utsname datos;
    if(args == NULL){
        if(uname(&datos) == 0){ //Llamada al sistema
        printf("Machine name: %s\nOS:%s\n release: %s\n version: %s\n Architecture: %s\n",datos.nodename, datos.sysname, datos.release, datos.version, datos.machine);
        }
        else perror("Error:"); //Error en la llamada al sistema
    }
    else puts("Error: listopen no recive mas argumentos");
}