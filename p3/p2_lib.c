#include "p2_lib.h"
#define MAX_FILE_LEN 1000

void memTypeToStr(Type tipo, char buff[8]){ //Funcion auxiliar para convertir enumType en str

    switch (tipo)
    {
        case mal: strcpy(buff,"malloc");
        break;
        case shm: strcpy(buff,"shared");
        break;
        case map: strcpy(buff,"mmap");
        break;
        default: strcpy(buff,"NULL");
            break;
    }
}

void printfMemBlk(tMemBlock memBlock){ //Funcion auxiliar para imprimir los datos de un bloque de memoria
    struct tm* calendar;
    char timeStr[30];
    Type t = memBlock.tipo; //Guardamos tipo
    char tipo[8];
    memTypeToStr(t,tipo); //Guardamos nombre del tipo en string
    calendar = localtime(&memBlock.allocTime); //Creamos struc tm con la hora de reserva
    strftime(timeStr,30,"%d/%m/%Y %X",calendar); //Creamos un string con el formato deseado
    if(t == mal) printf("%6p%12lu %s %s\n",memBlock.addres,memBlock.size,timeStr,tipo); //Imprimir malloc
    else if(t == shm) printf("%-6p%20lu %s %s (key %d)\n",memBlock.addres,memBlock.size,timeStr,tipo,memBlock.key); //Imprimir shared
    else if(t == map) printf("%-6p%20lu %s %s (descriptor %d)\n",memBlock.addres,memBlock.size,timeStr,getNombre(memBlock.filename), memBlock.fd); //Imprimir malloc
    else printf("Error: printing memory list Type not found\n");
}

void printMemBlocks(tList lista){ //Imprime lista de memoria
    tMemBlock* memBlock;
    tPos i = lista;
    while ( i != NULL)
    {
        memBlock = i->data;
        printfMemBlk(*memBlock);
        i = i->next;   
    }
}

void printMemBlocksType(tList lista, Type tipo){ //Imprime lista de memoria (filtrado)
    tMemBlock* memBlock;
    tPos i = lista;
    while ( i != NULL)
    {
        memBlock = i->data;
        if(memBlock->tipo == tipo) printfMemBlk(*memBlock);
        i = i->next;   
    }
}

void doRecurse(int n)
{
    if(n == -1) printf("Error en recurse: argumento invalido\n");
    else {
        char automatico[TAMANO];
        static char estatico[TAMANO];   
        printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico); 
        if (n>0) doRecurse(n-1);
    }
}   

void doMalloc(char* args, char** args_ptr, tList* memory){ //Reserva bloques de memoria
    int pid = getpid();
    size_t tam = 0;
    void* memPtr = NULL;
    tPos memPos = NULL;
    tMemBlock* memBlock = NULL;
    time_t allocTime;
    if(args == NULL){
        printf("******Lista de bloques asignados malloc para el proceso %d\n",pid);
        printMemBlocksType(*memory, mal); //Sin argumentos imprimimos reservas de malloc hechas
    }
    else if(strcmp(args,"-free") == 0){
        args = strtok_r(NULL," \n\t", args_ptr);
        if(args !=NULL) tam = (size_t)strtoul(args,NULL,10);
        if(tam > 0)memPos = searchBySiceAndType(*memory,tam,mal); //Buscamos Coincidendicas
        if(memPos == NULL) printf("Error: en malloc -free, no se encuentran bloques de %lu bytes\n", tam); //Control errores
        else{ 
            memBlock = (tMemBlock*)getData(*memory,memPos);
            free(memBlock->addres); //Liberamos memoria
            printf("freed addres : %p\n", memBlock->addres);
            deleteMemBlockIn(memory, memPos); //Borramos de la lista
        }
    }
    else{
        tam = (size_t)strtoul(args,NULL,10);
        if(tam == 0) printf("No se pueden reservar bloque de 0 bytes\n");
        else{
            memPtr = malloc(tam); //Reservamos memoria
            if(memPtr == NULL) perror("Error: en malloc\n"); //Control errores
            else{
                time(&allocTime);
                insertMemBlock(memory,newMemBlock(memPtr,tam,allocTime,mal,0,NULL,0));
                printf("Asignados %lu bytes en %p\n",tam,memPtr);
            }
        }
    }
}
void * ObtenerMemoriaShmget (key_t clave, size_t tam)
{
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;

    if (tam!=0)     /*tam distito de 0 indica crear */
        flags=flags | IPC_CREAT | IPC_EXCL;
    if (clave==IPC_PRIVATE)  /*no nos vale*/
        {errno=EINVAL; return NULL;}
    if ((id=shmget(clave, tam, flags))==-1)
        return (NULL);
    if ((p=shmat(id,NULL,0))==(void*) -1){
        aux=errno;
        if (tam)
             shmctl(id,IPC_RMID,NULL);
        errno=aux;
        return (NULL);
    }
    shmctl (id,IPC_STAT,&s);
    return (p);
}

void doShared(char* args, char** args_ptr, tList* memory){ //reserva o libera un bloque shared de memoria
    int pid = getpid();
    size_t tam = 0;
    key_t key  = 0; 
    void* memPtr = NULL;
    time_t allocTime;
    int id;
    struct shmid_ds s;
    tPos p;
    if(args == NULL){
        printf("******Lista de bloques asignados shared para el proceso %d\n",pid);
        printMemBlocksType(*memory, shm); //Sin argumentos imprimimos reservas de shared hechas
    }
    else if(strcmp(args,"-free") == 0){
        args = strtok_r(NULL," \n\t", args_ptr);
        if (args==NULL || (key=(key_t)strtoul(args,NULL,10))==IPC_PRIVATE) printf ("Error en shared: necesita clave_valida\n");
        else if ((id=shmget(key,0,0666))==-1) perror ("shmget: imposible obtener memoria compartida");
        else if (shmctl(id,IPC_RMID,NULL)==-1) perror ("shmctl: imposible eliminar id de memoria compartida\n");
        else if ((p = searchByKey(*memory,key)) == NULL) printf("Error en shared: no se encontro cl en la lista\n");
        else deleteMemBlockIn(memory,p);
    }
    else if(strcmp(args,"-delkey") == 0){
        args = strtok_r(NULL," \n\t", args_ptr);
        if (args==NULL || (key=(key_t)strtoul(args,NULL,10))==IPC_PRIVATE) printf ("Error en shared: necesita clave_valida\n");
        else if ((id=shmget(key,0,0666))==-1) perror ("shmget: imposible obtener memoria compartida");
        else if (shmctl(id,IPC_RMID,NULL)==-1) perror ("shmctl: imposible eliminar id de memoria compartida\n");
    }
    else if(strcmp(args,"-create") == 0){
        args = strtok_r(NULL," \n\t", args_ptr);
        key=(key_t)  strtoul(args,NULL,10);
        args = strtok_r(NULL," \n\t", args_ptr);
        tam=(size_t) strtoul(args,NULL,10);
        if (tam==0) {
	        printf ("No se asignan bloques de 0 bytes\n");
        }
        else if ((memPtr=ObtenerMemoriaShmget(key,tam))!=NULL){
            time(&allocTime);
            insertMemBlock(memory,newMemBlock(memPtr,tam,allocTime,shm,key,NULL,0));
	        printf ("Asignados %lu bytes en %p\n",(unsigned long) tam, memPtr);

        }
        else{
	        printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) key,strerror(errno));
        }
    }
    else{
        key = (key_t)strtoul(args,NULL,10);
        if(key == 0) printf("Error en shared: invalid argument\n");
        else{
            if ((id=shmget(key,0,0666))==-1) perror("Error en shared: ");
            else{ 
                if((memPtr = shmat(id,NULL,0)) == NULL) perror("Error en shared: \n");
                else {
                    shmctl (id,IPC_STAT,&s);
                    tam = s.shm_segsz;
                    allocTime = s.shm_ctime;
                    insertMemBlock(memory,newMemBlock(memPtr,tam,allocTime,shm,key,NULL,0));
                    printf("Memoria compartida de clave %d  en %p\n",key,memPtr);
                }
            }
        }
    }
}

void doMmap(char* args, char** args_ptr, tList* memory){ //mapea o desmapea un fichero en memoria
    int pid = getpid();
    size_t tam = 0;
    void* memPtr = NULL;
    tPos memPos = NULL;
    tMemBlock* memBlock = NULL;
    time_t allocTime;
    struct stat s;
    int fd, protection=0, map=MAP_PRIVATE,modo=O_RDONLY;
    char fichero[Max_len_dir];
    if(args == NULL){
        printf("******Lista de bloques asignados mmap para el proceso %d\n",pid);
        printMemBlocksType(*memory, map); //Sin argumentos imprimimos reservas de mmap hechas
    }
    else if(strcmp(args,"-free") == 0){
        args = strtok_r(NULL," \n\t", args_ptr);
        strcpy(fichero,args);
        memPos = searchByFile(*memory, fichero); //Buscamos Coincidendicas
        if(memPos == NULL) printf("Error: en mmap -free, Fichero %s no mapeado\n", fichero); //Control errores
        else{ 
            memBlock = (tMemBlock*)getData(*memory,memPos);
            close(memBlock->fd); //Cerramos fichero
            printf("freed addres : %p\n", memBlock->addres);
            deleteMemBlockIn(memory, memPos); //Borramos de la lista
        }
    }
    else{
        strcpy(fichero, args);
        args = strtok_r(NULL," \n\t", args_ptr);
        if(args != NULL){
            for (int i = 0; i < 3; i++)
            {
                if (strchr(args,'r')!=NULL) protection|=PROT_READ;
                else if (strchr(args,'w')!=NULL) protection|=PROT_WRITE;
                else if (strchr(args,'x')!=NULL) protection|=PROT_EXEC;
            }   
        }
        if (protection&PROT_WRITE) modo=O_RDWR;
        else if (stat(fichero,&s)==-1 || (fd=open(fichero, modo))==-1) perror("Error en mmap:");
        else if ((memPtr=mmap(NULL,s.st_size, protection,map,fd,0))==MAP_FAILED) perror("Error en mmap:");
        else{
            allocTime = s.st_atime;
            tam = s.st_size;
            insertMemBlock(memory,newMemBlock(memPtr,tam,allocTime,map,0,fichero,fd));
            printf("Fichero: %s mapeado en %p\n",fichero,memPtr);
        }
    }
}

ssize_t LeerFichero (char *f, void *p, size_t cont)
{
   struct stat s;
   ssize_t  n;  
   int df,aux;
   if (stat (f,&s)==-1 || (df=open(f,O_RDONLY))==-1)
	return -1;     
   if (cont==-1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
	cont=s.st_size;
   if ((n=read(df,p,cont))==-1){
	aux=errno;
	close(df);
	errno=aux;
	return -1;
   }
   close (df);
   return n;
}

void doRead(char* args, char** args_ptr){ //lee un fichero en memoria
    void* addr;
    size_t nBytes;
    char fichero[Max_len_dir];
    if (args == NULL) printf("Error en read: faltan parametros\n");
    else{
        strcpy(fichero,args);
        args = strtok_r(NULL," \n\t", args_ptr);
        addr = (void*)strtoul(args,NULL,16);
        args = strtok_r(NULL," \n\t", args_ptr);
        nBytes = strtol(args,NULL,10);
        LeerFichero(fichero,addr,nBytes);
    }
}

ssize_t EscribirFichero (char *f, void *p, size_t cont, bool overwrite){
   ssize_t  n;
   int df,aux, flags=O_CREAT | O_EXCL | O_WRONLY;

   if (overwrite)
	flags=O_CREAT | O_WRONLY | O_TRUNC;

   if ((df=open(f,flags,0777))==-1)
	return -1;

   if ((n=write(df,p,cont))==-1){
	aux=errno;
	close(df);
	errno=aux;
	return -1;
   }
   close (df);
   return n;
}

void doWrite(char* args, char** args_ptr){//escribe en un fichero los contenidos de una dirección de memoria
    void* addr;
    size_t nBytes;
    char fichero[Max_len_dir];
    bool ow = false;
    if (args == NULL) printf("Error en write: faltan parametros\n");
    else{
        if (strcmp(args,"-o")==0)
        {
            ow = true;
            args = strtok_r(NULL," \n\t", args_ptr);
        }
        strcpy(fichero,args);
        args = strtok_r(NULL," \n\t", args_ptr);
        addr = (void*)strtoul(args,NULL,16);
        args = strtok_r(NULL," \n\t", args_ptr);
        nBytes = strtol(args,NULL,10);
        if(EscribirFichero(fichero,addr,nBytes,ow)==-1)perror("Error en write:");
    }
}

void LlenarMemoria (void *p, size_t cont, unsigned char byte)
{
  unsigned char *arr=(unsigned char *) p;
  size_t i;

  for (i=0; i<cont;i++)
		arr[i]=byte;
}

void doMemfill(char* args, char** args_ptr){
    void* addr;
    size_t nBytes;
    unsigned char byte;
    if(args != NULL){
        addr = (void*)strtoul(args,NULL,16);
        args = strtok_r(NULL," \n\t",args_ptr);
        nBytes = strToInt(args);
        args = strtok_r(NULL," \n\t",args_ptr);
        byte = strToInt(args);
        printf("Llenando %lu bytes de memoria con el byte (%.2X) a partir de la direccion %p\n",nBytes,byte,addr);
        LlenarMemoria(addr, nBytes, byte);
    }
}

void doMemdump(char* args, char** args_ptr){
    unsigned char* addr;
    size_t nBytes;
    if(args != NULL){
        addr = (unsigned char*)strtol(args,NULL,16);
        args = strtok_r(NULL," \n\t",args_ptr);
        nBytes = (size_t)strtoul(args,NULL,10);
        args = strtok_r(NULL," \n\t",args_ptr);
        printf("Volcando %lu bytes de memoria desde la direccion %p\n",nBytes,addr);
        for (size_t i = 0; i<nBytes; i++){
            printf(" %c ", addr[i]);
        }
        printf("\n");
        for (size_t i = 0; i<nBytes; i++){
            printf(" %.2X ", addr[i]);
        }
        printf("\n");
    }
}

void Do_MemPmap (void) /*sin argumentos*/
 { pid_t pid;       /*hace el pmap (o equivalente) del proceso actual*/
   char elpid[32];
   char *argv[4]={"pmap",elpid,NULL};
   
   sprintf (elpid,"%d", (int) getpid());
   if ((pid=fork())==-1){
      perror ("Imposible crear proceso");
      return;
      }
   if (pid==0){ /*proceso hijo*/
      if (execvp(argv[0],argv)==-1)
         perror("cannot execute pmap (linux, solaris)");
      
      argv[0]="vmmap"; argv[1]="-interleave"; argv[2]=elpid;argv[3]=NULL;
      if (execvp(argv[0],argv)==-1) /*probamos vmmap Mac-OS*/
         perror("cannot execute vmmap (Mac-OS)");          
      
      argv[0]="procstat"; argv[1]="vm"; argv[2]=elpid; argv[3]=NULL;   
      if (execvp(argv[0],argv)==-1)/*No hay pmap, probamos procstat FreeBSD */
         perror("cannot execute procstat (FreeBSD)");
         
      argv[0]="procmap",argv[1]=elpid;argv[2]=NULL;    
            if (execvp(argv[0],argv)==-1)  /*probamos procmap OpenBSD*/
         perror("cannot execute procmap (OpenBSD)");
         
      exit(1);
  }
  waitpid (pid,NULL,0);
}

int globA = 98723542;
int globB = 40670303;
int globC = 74742121;
int globD;
int globE;
int globF;

void doMem(char* args, char** args_ptr, tList* memory){//muestra información de la memoria de los procesos
    int pid = getpid();
    if(args == NULL || strcmp(args,"-all")==0){
        doMem("-vars",NULL,memory);
        doMem("-funcs",NULL,memory);
        doMem("-blocks",NULL,memory);
    }
    else if(strcmp(args,"-blocks")==0){
        printf("******Lista de bloques asignados para el proceso %d\n",pid);
        printMemBlocks(*memory); //Sin argumentos imprimimos reservas de memoria
    }
    else if(strcmp(args,"-pmap")==0) Do_MemPmap();
    else if(strcmp(args,"-funcs")==0){
        printf("Funciones programa:\t%p,\t%p,\t%p\n",authors,create,doMalloc);
        printf("Funciones libreria:\t%p,\t%p,\t%p\n",printf,scanf,strcpy);
    }
    else if(strcmp(args,"-vars")==0){
        int a = 12351523;
        int b = 46572356;
        int c = 17452164;
        static int sa = 124346534;
        static int sb = 124346534;
        static int sc = 124346534;
        static int sd;
        static int se;
        static int sf;
        printf("Variables Locales:\t%p,\t%p,\t%p\n",&a,&b,&c);
        printf("Variables Globales:\t%p,\t%p,\t%p\n",&globA,&globB,&globC);
        printf("Var(N.I.) Globales:\t%p,\t%p,\t%p\n",&globD,&globE,&globF);
        printf("Variables Estaticas:\t%p,\t%p,\t%p\n",&sa,&sb,&sc);
        printf("Var(N.I.) Estaticas:\t%p,\t%p,\t%p\n",&sd,&se,&sf);
    }
}