#include "p1_lib.h"
void create(char *args, char** args_ptr){ //Crear archivos o directorios
    int fd;
    if(args == NULL) changeDir(args); //Sin argumentos imprimimos directorio actual
    else {
        if(strcmp(args,"-f") == 0){ //Comprobamos si imprimimos un archivo o directorio
            args = strtok_r(NULL," \n\t", args_ptr);
            if((fd = creat(args,0777))==-1) perror("\nError en create: "); //Tratamos de crear el archivo
            else close(fd);  //Si logramos crear el archivo borramos su file descriptors
        }else if(mkdir(args,0777)==-1) perror("\nError en create: "); //Tratamos de crear el directorio
    }
} 

char LetraTF (mode_t m) //Funcion auxiliar para sacar el tipo de fichero como caracter
{
     switch (m&__S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case __S_IFSOCK: return 's'; /*socket */
        case __S_IFLNK: return 'l'; /*symbolic link*/
        case __S_IFREG: return '-'; /* fichero normal*/
        case __S_IFBLK: return 'b'; /*block device*/
        case __S_IFDIR: return 'd'; /*directorio */ 
        case __S_IFCHR: return 'c'; /*char device*/
        case __S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
     }
}

char * ConvierteModo (mode_t m) //Funcion auxiliar para devolver los permisos en un string con formato rwx
{
    char *permisos;

    if ((permisos=(char *) malloc (12))==NULL)
        return NULL;
    strcpy (permisos,"---------- ");
    
    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r';    /*propietario*/
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r';    /*grupo*/
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r';    /*resto*/
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s';    /*setuid, setgid y stickybit*/
    if (m&S_ISGID) permisos[6]='s';
    if (m&__S_ISVTX) permisos[9]='t';
    
    return permisos;
}   

char* getUser(uid_t uid) //Funcion auxiliar para obtener el nombre de usuario a partir del uid
{
    struct passwd *pws;
    pws = getpwuid(uid);
        return pws->pw_name;
}

char* getGroup(gid_t gid){ //Funcion auxiliar para obtener el nombre de grupo a partir del gid
    struct group *grp;
    grp = getgrgid(gid);
    return grp->gr_name;
}

char* getNombre(char *path){ //Funcion auxiliar paara obtener el nombre de un archivo/directorio dada su ruta
    char *token = strtok(path,"/"); // Divide la ruta en partes usando '/'
    char *nombre = NULL;
    while (token != NULL) {
        nombre = token; // Guarda la parte actual como el nombre
        token = strtok(NULL, "/");
    }
    return nombre;
}

void showStat(char* args, char** args_ptr){
    struct stat status;
    time_t time;
    struct tm* calendar;
    char timeStr[30];
    char name[1000];
    char pathname[500];
    int pathnameLen;
    char* permisos;
    bool l = false;
    bool acc = false;
    bool link = false;
    if(args == NULL) changeDir(args); //Sin argumentos imprimimos directorio actual
    else{
        while (args != NULL)
        {
            if(args[0]=='-'){ //Comprobamos parametros
                if(strcmp(args,"-long") == 0) l = true;
                else if(strcmp(args,"-acc") == 0) acc = true;
                else if(strcmp(args,"-link") == 0) link = true;
                else printf("Error en stat: Argumento %s no reconocido\n",args);
            }
            else{  //Imprimimos Stat por cada fichero dado
                if(lstat(args,&status)==-1) perror("\nError en stat: "); //Llamada al sistema lstat y control de error
                else if(l){
                    if(acc) time = status.st_atime; //Usamos fecha de acceso
                    else time = status.st_mtime; //Usamos fecha de modificacion
                    calendar = localtime(&time); //Creamos un calendario con la hora del sistema
                    strftime(timeStr,30,"%d/%m/%Y-%X",calendar); //Creamos un string con el formato deseado
                    if(link && LetraTF(status.st_mode)=='l') { //Si se introduce el parametro -link y es enlace simbolico, construimos un string con el link y el path apuntado
                        strcpy(name,getNombre(args));
                        strcat(name, " -> ");
                        if((pathnameLen=readlink(args,pathname,500)) == -1) perror("Error en enlace simbolico:"); //Llamada al sistema para leer el enlace simbolico y control de errores
                        pathname[pathnameLen] = '\0';
                        strcat(name,pathname);
                    } else strcpy(name,getNombre(args)); //Mostramos unicamete el path introducido
                    permisos = ConvierteModo(status.st_mode);
                    printf("\t%s\t%ld (%ld)\t%s\t%s\t%s\t%ld\t%s\n",timeStr,status.st_nlink,status.st_ino,getUser(status.st_uid),getGroup(status.st_gid),permisos,status.st_size,name);//Mostramos la informacion en formato largo
                    free(permisos);//Liberamos memoria reservada
                }
                else{
                    printf("\t%ld\t%s\n",status.st_size,getNombre(args)); //Mostramos la informacion en formato corto
                }
            }
            args = strtok_r(NULL," \n\t",args_ptr); 
        }
    }
}

void list(char* args, char** args_ptr){ //Listar ficheros
    char mode[20]; //Copiamos parametros de stats
    char buff[1000]; //Buffer para crear argumentos
    char* buff_ptr; //Puntero para trocear buff
    char* rPath = NULL; //String para direccion absoluta
    DIR* directory = NULL; //Puntero para guardar las direcciones
    struct dirent* file; //Struct para cada fichero de las direcciones
    bool reca = false;
    bool recb = false;
    bool hid = false;
    mode[0] = '\0';
    if(args == NULL) changeDir(args); //Sin argumentos imprimimos directorio actual
    else{
        while (args != NULL)
        {
            if(args[0]=='-'){ //Comprobamos parametros
                if(strcmp(args,"-reca") == 0) reca = true;
                else if(strcmp(args,"-recb") == 0) recb = true;
                else if(strcmp(args,"-hid") == 0)  hid = true;
                else if(strcmp(args,"-long") == 0){
                strcat(mode,args); 
                strcat(mode," ");
                }
                else if(strcmp(args,"-acc") == 0){
                strcat(mode,args); 
                strcat(mode," ");
                }
                else if(strcmp(args,"-link") == 0){
                strcat(mode,args); 
                strcat(mode," ");
                }
                else printf("Error en list: argumento %s no reconocido\n",args);
            }
            else
            {
                if((directory = opendir(args)) == NULL) perror("Error en list:");
                else{

                    if(recb){ //Recursividad antes
                        while ((file = readdir(directory)) != NULL){
                            if(strcmp(file->d_name,".")== 0 || strcmp(file->d_name,"..")== 0) continue; //Ingoramos .(este directorio) y ..(directorio padre)
                            if(file->d_name[0] == '.' && !hid) continue; //Saltar elementos ocultos salvo -hid
                            if(file->d_type == 4){ //Mirar subcarpetas recursivamente antes
                                buff[0] = '\0'; //Obtencion de ruta absoluta
                                strcpy(buff,args);
                                strcat(buff,"/");
                                strcat(buff,file->d_name);
                                if((rPath = realpath(buff, NULL)) == NULL) perror("Error en list:"); //Comprobamos haber obtenido la ruta absoluta
                                else{
                                    buff[0] = '\0'; //Construccion de argumentos para list
                                    strcpy(buff,mode); //Añadimos argumentos de stat
                                    strcat(buff,"-recb "); //Añadimos -recb
                                    if(hid) strcat(buff,"-hid "); //Comprobamos si añadir -hid
                                    strcat(buff,rPath); //Añadimos ruta absoluta
                                    if(rPath != NULL) free(rPath);
                                    strcat(buff,"\0");//Añadimos final de string
                                    list(strtok_r(buff," \n\t", &buff_ptr), &buff_ptr); //Llamada recursiva a list
                                }
                            }
                        }
                    }
                    if(closedir(directory) == 0) directory = NULL;//Liberamos memorida reservada por opendir
                    directory = opendir(args);
                    printf("************ %s ************\n",args); //Imprimir nombre de la carpeta
                    while ((file = readdir(directory)) != NULL){
                        if(file->d_name[0] == '.' && !hid) continue; //Saltar elementos ocultos salvo -hid
                        buff[0] = '\0'; //Obtencion de ruta absoluta
                        strcpy(buff,args);
                        strcat(buff,"/");
                        strcat(buff,file->d_name);
                        if((rPath = realpath(buff, NULL)) == NULL) perror("Error en list:"); //Comprobamos haber obtenido la ruta absoluta
                        else{
                            buff[0] = '\0'; //Construccion de argumentos para stat
                            strcpy(buff,mode); //Añadimos argumentos de stat
                            strcat(buff,rPath); //Añadimos ruta absoluta
                            if(rPath != NULL) free(rPath);
                            strcat(buff,"\0");//Añadimos final de string
                            showStat(strtok_r(buff," \n\t", &buff_ptr),&buff_ptr); //Llamada al comando stat
                        }
                    }
                    if(closedir(directory) == 0) directory = NULL;//Liberamos memorida reservada por opendir
                    else perror("Error en list:");
                    directory = opendir(args);
                    if(reca && !recb){ //Recursividad despues
                        while ((file = readdir(directory)) != NULL){
                            if(strcmp(file->d_name,".")== 0 || strcmp(file->d_name,"..")== 0) continue; //Ingoramos .(este directorio) y ..(directorio padre)
                            if(file->d_name[0] == '.' && !hid) continue; //Saltar elementos ocultos salvo -hid
                            if(file->d_type == 4){ //Mirar subcarpetas recursivamente despues
                                buff[0] = '\0'; //Obtencion de ruta absoluta
                                strcpy(buff,args);
                                strcat(buff,"/");
                                strcat(buff,file->d_name);
                                if((rPath = realpath(buff, NULL)) == NULL) perror("Error en list:"); //Comprobamos haber obtenido la ruta absoluta
                                else{
                                buff[0] = '\0'; //Construccion de argumentos para list
                                strcpy(buff,mode); //Añadimos argumentos de stat
                                strcat(buff,"-reca "); //Añadimos -reca
                                if(hid) strcat(buff,"-hid "); //Comprobamos si añadir -hid
                                strcat(buff,rPath); //Añadimos ruta absoluta
                                if(rPath != NULL) free(rPath);
                                strcat(buff,"\0");//Añadimos final de string
                                list(strtok_r(buff," \n\t", &buff_ptr), &buff_ptr); //Llamada recursiva a list
                                }
                            }
                        }
                    }
                    if(closedir(directory) == 0) directory = NULL;//Liberamos memorida reservada por opendir
                }
            }   
            args = strtok_r(NULL," \n\t",args_ptr); 
        }
    }
}

void delete(char* args){ //Borrar ficheros o directorios vacios
    if(args == NULL) changeDir(args); //Sin argumentos imprimimos directorio actual
    else{
        if(remove(args) == -1) perror("Error en delete:"); //Llamada al sistema y control de errores
        else printf("\t-deleted: %s\n",args); //Mensaje de informacion 
    }
}

void deltree(char* args, char** args_ptr){ //Borrado recursivo de cualquier cosa (COMANDO PEGRILOSO USAR VM)
    char buff[1000]; //Buffer para construir ruta absoluta
    char* buff_ptr; //Puntero para trocear buff
    char* rPath = NULL; //String para direccion absoluta
    DIR* directory = NULL; //Puntero para guardar las direcciones
    struct dirent* file; //Struct para cada fichero de las direcciones
    if(args == NULL) changeDir(args); //Sin argumentos impri;mimos directorio actual
    else{
        while (args != NULL)
        {
            if((directory = opendir(args)) == NULL) perror("Error en deltree:");
            else{
                while ((file = readdir(directory)) != NULL){
                    if(strcmp(file->d_name,".")== 0 || strcmp(file->d_name,"..")== 0) continue; //Ingoramos .(este directorio) y ..(directorio padre)
                    if(file->d_type == 4){ //Mirar subcarpetas recursivamente antes
                        buff[0] = '\0'; //Obtencion de ruta absoluta
                        strcpy(buff,args);
                        strcat(buff,"/");
                        strcat(buff,file->d_name);
                        if((rPath = realpath(buff, NULL)) == NULL) perror("Error en list:"); //Comprobamos haber obtenido la ruta absoluta
                        else{
                            buff[0] = '\0'; //Construccion de argumentos para list
                            strcat(buff,rPath); //Añadimos ruta absoluta
                            if(rPath != NULL) free(rPath); //Liberamos memoria reservada por realpath
                            deltree(strtok_r(buff," \n\t", &buff_ptr), &buff_ptr); //Llamada recursiva a deltree
                        }
                    }
                }
                if(closedir(directory) == 0) directory = NULL;//Liberamos memorida reservada por opendir
                directory = opendir(args);
                printf("*BORRANDO: %s *\n",args); //Imprimir nombre de la carpeta
                while ((file = readdir(directory)) != NULL){
                    if(strcmp(file->d_name,".")== 0 || strcmp(file->d_name,"..")== 0) continue; //Ingoramos .(este directorio) y ..(directorio padre)
                    buff[0] = '\0'; //Obtencion de ruta absoluta
                    strcpy(buff,args);
                    strcat(buff,"/");
                    strcat(buff,file->d_name);
                    if((rPath = realpath(buff, NULL)) == NULL) perror("Error en list:"); //Comprobamos haber obtenido la ruta absoluta
                    else{
                        buff[0] = '\0'; //Construccion de argumentos para stat
                        strcat(buff,rPath); //Añadimos ruta absoluta
                        if(rPath != NULL) free(rPath); //Liberamos memoria reservada por realpath
                        delete(buff); //Llamada al comando delete
                    }
                }
                if(closedir(directory) == 0) directory = NULL;//Liberamos memorida reservada por opendir
                delete(args); //Borramos directorio vacio
            }
            args = strtok_r(NULL," \n\t",args_ptr); //Siguiente argumento
        }
    }
}