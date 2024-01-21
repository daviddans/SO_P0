#include "p3_lib.h"

/*las siguientes funciones nos permiten obtener el nombre de una senal a partir
del número y viceversa */

static struct SEN sigstrnum[]={   
	{"HUP", SIGHUP},
	{"INT", SIGINT},
	{"QUIT", SIGQUIT},
	{"ILL", SIGILL}, 
	{"TRAP", SIGTRAP},
	{"ABRT", SIGABRT},
	{"IOT", SIGIOT},
	{"BUS", SIGBUS},
	{"FPE", SIGFPE},
	{"KILL", SIGKILL},
	{"USR1", SIGUSR1},
	{"SEGV", SIGSEGV},
	{"USR2", SIGUSR2}, 
	{"PIPE", SIGPIPE},
	{"ALRM", SIGALRM},
	{"TERM", SIGTERM},
	{"CHLD", SIGCHLD},
	{"CONT", SIGCONT},
	{"STOP", SIGSTOP},
	{"TSTP", SIGTSTP}, 
	{"TTIN", SIGTTIN},
	{"TTOU", SIGTTOU},
	{"URG", SIGURG},
	{"XCPU", SIGXCPU},
	{"XFSZ", SIGXFSZ},
	{"VTALRM", SIGVTALRM},
	{"PROF", SIGPROF},
	{"WINCH", SIGWINCH}, 
	{"IO", SIGIO},
	{"SYS", SIGSYS},
/*senales que no hay en todas partes*/
#ifdef SIGPOLL
	{"POLL", SIGPOLL},
#endif
#ifdef SIGPWR
	{"PWR", SIGPWR},
#endif
#ifdef SIGEMT
	{"EMT", SIGEMT},
#endif
#ifdef SIGINFO
	{"INFO", SIGINFO},
#endif
#ifdef SIGSTKFLT
	{"STKFLT", SIGSTKFLT},
#endif
#ifdef SIGCLD
	{"CLD", SIGCLD},
#endif
#ifdef SIGLOST
	{"LOST", SIGLOST},
#endif
#ifdef SIGCANCEL
	{"CANCEL", SIGCANCEL},
#endif
#ifdef SIGTHAW
	{"THAW", SIGTHAW},
#endif
#ifdef SIGFREEZE
	{"FREEZE", SIGFREEZE},
#endif
#ifdef SIGLWP
	{"LWP", SIGLWP},
#endif
#ifdef SIGWAITING
	{"WAITING", SIGWAITING},
#endif
 	{NULL,-1},
	};    /*fin array sigstrnum */


int ValorSenal(char * sen)  /*devuelve el numero de senial a partir del nombre*/ 
{ 
  int i;
  for (i=0; sigstrnum[i].nombre!=NULL; i++)
  	if (!strcmp(sen, sigstrnum[i].nombre))
		return sigstrnum[i].senal;
  return -1;
}


char *NombreSenal(int sen)  /*devuelve el nombre senal a partir de la senal*/ 
{			/* para sitios donde no hay sig2str*/
 int i;
  for (i=0; sigstrnum[i].nombre!=NULL; i++)
  	if (sen==sigstrnum[i].senal)
		return sigstrnum[i].nombre;
 return ("SIGUNKNOWN");
}


int BuscarVariable (char * var, char *e[])  /*busca una variable en el entorno que se le pasa como parámetro*/
{
  int pos=0;
  char aux[MAXVAR];
  
  strcpy (aux,var);
  strcat (aux,"=");
  
  while (e[pos]!=NULL)
    if (!strncmp(e[pos],aux,strlen(aux)))
      return (pos);
    else 
      pos++;
  errno=ENOENT;   /*no hay tal variable*/
  return(-1);
}

void doShowVar(char *args, char**env){
    int pos;
    if (args == NULL){
        pos = 0;
        while(env[pos] != NULL){
            printf("%p -> main arg3[%d]=(%p) %s\n",&env[pos],pos,env[pos],env[pos]);
            pos++;
        }
    }
    else 
    {
        pos = BuscarVariable(args, env);
        if(pos != -1) printf("Con arg3 main %s(%p) @(%p)\n", env[pos],env[pos],&env);
        else perror("Con arg3");
        pos = BuscarVariable(args, __environ);
        if (pos!= -1) printf("  Con __environ %s(%p) @(%p)\n", __environ[pos], __environ[pos], &__environ);
        else perror("  Con __environ");
        printf("    Con getenv %s (%p) \n", getenv(args), getenv(args));
    }
}

uid_t getUserUid(char *username){
    struct passwd* pas = getpwnam(username);
    if(pas != NULL) return pas->pw_uid;
    else return -1;
}

void doUid(char *args, char**args_ptr){
    uid_t ruser;
    uid_t euser;
    if (args == NULL || strcmp(args,"-get") == 0){
        ruser = getuid();
        euser = geteuid();
        printf ("Credencial real: %d (%s)\n",ruser, getUser(ruser));
        printf ("Credencial efectiva: %d (%s)\n",euser, getUser(euser));
    }
    else if (strcmp(args,"-set")==0){
        args = strtok_r(NULL," \n\t", args_ptr);
        if(args == NULL) printf("Error en uid: faltan argumentos\n");
        else if(strcmp(args,"-l")==0){
            args = strtok_r(NULL," \n\t", args_ptr);
            if(args != NULL) euser = getUserUid(args);
            else euser = -1;
            if (euser == -1) printf("Error en uid: argumento: %s no valido \n", args);
            else{
                if(seteuid(euser) == -1) perror("Error en uid: ");
            }
        }
        else{
            euser = strToInt(args);
            if (euser == -1) printf("Error en uid: argumento: %s no valido \n", args);
            else{
                if(seteuid(euser) == -1) perror("Error en uid: ");
            }
        }
    }
}

int CambiarVariable(char * var1, char *var2, char * valor, char *e[], bool subs) /*cambia una variable en el entorno que se le pasa como parámetro*/
{                                                        /*lo hace directamente, no usa putenv. subs indica si se usa o no var2*/
  int pos;
  char *aux;
   
  if ((pos=BuscarVariable(var1,e))==-1) return(-1);
  if(subs){
    if((aux=(char *)malloc(strlen(var2)+strlen(valor)+2))==NULL) return -1;
    strcpy(aux,var2);
  }
  else{
    if((aux=(char *)malloc(strlen(var1)+strlen(valor)+2))==NULL) return -1;
    strcpy(aux,var1);
  }
  strcat(aux,"=");
  strcat(aux,valor);
  e[pos]=aux;
  return (pos); 
}
void doChangeVar(char *args, char**args_ptr, char **env){ //cambia variable de entorno
    char* aux;
    char* var;
    char* value;
    if (args == NULL) printf("Uso: changevar < -a|-e|-p > var valor\n");
    else if(strcmp(args, "-a") == 0){ //Usando main arg[3]
        var = strtok_r(NULL," \n\t", args_ptr);
        value = strtok_r(NULL," \n\t", args_ptr);
        if(var != NULL && value != NULL) if(CambiarVariable(var,NULL,value,env, false) == -1) perror("Error en changevar:"); //Llamada a cambiarvariable + control de errores
    }
    else if(strcmp(args, "-e") == 0){ //Usando __environ
        var = strtok_r(NULL," \n\t", args_ptr);
        value = strtok_r(NULL," \n\t", args_ptr);
        if(var != NULL && value != NULL) if(CambiarVariable(var,NULL,value,__environ, false) == -1) perror("Error en changevar:"); //Llamada a cambiarvariable + control de errores  
    }
    else if(strcmp(args, "-p") == 0){ //Usando putenv()
        var = strtok_r(NULL," \n\t", args_ptr);
        value = strtok_r(NULL," \n\t", args_ptr);
        if(var != NULL && value != NULL){
            aux = malloc(sizeof(char)*(strlen(var)+strlen(value)+2)); //Guadamos memoria para "clave=valor"
            if (aux == NULL) printf("Error en changevar: falta de memoria \n");
            else{
                //Construimos el string con formato "VAR=value"
                strcpy(aux,var); 
                strcat(aux,"=");
                strcat(aux,value);
                if(putenv(aux) == -1) perror("Error en changevar: "); //Llamada a putenv + control de errores
            }
        }
    }
    else printf("Uso: changevar < -a|-e|-p > var valor\n");
}

void doSubsVar(char *args, char**args_ptr, char **env){ //cambia var1 por "var2=value"
    char* var1;
    char* var2;
    char* value;
    if (args == NULL) printf("Uso: subsvar < -a|-e > var1 var2 valor");
    else if(strcmp(args, "-a") == 0){ //Usando main arg[3]
        var1 = strtok_r(NULL," \n\t", args_ptr);
        var2 = strtok_r(NULL," \n\t", args_ptr);
        value = strtok_r(NULL," \n\t", args_ptr);
        if(CambiarVariable(var1,var2,value,env,true) == -1) perror("Error en subsvar:"); //Llamada a cambiarvariable + control de errores
    }
    else if(strcmp(args, "-e") == 0){ //Usando __environ
        var1 = strtok_r(NULL," \n\t", args_ptr);
        var2 = strtok_r(NULL," \n\t", args_ptr);
        value = strtok_r(NULL," \n\t", args_ptr);
        if(CambiarVariable(var1,var2,value,__environ,true) == -1) perror("Error en subsvar:"); //Llamada a cambiarvariable + control de errores
    }
    else printf("Uso: subsvar < -a|-e > var1 var2 valor\n");
}

void doShowEnv(char *args, char** env){
        int pos;
    if (args == NULL){
        pos = 0;
        while(env[pos] != NULL){
            printf("%p -> main arg3[%d]=(%p) %s\n",&env[pos],pos,env[pos],env[pos]);
            pos++;
        }
    }
    else if(strcmp(args,"-environ")==0)
    {
        pos = 0;
        while(env[pos] != NULL){
            printf("%p ->__environ[%d]=(%p) %s\n",&__environ[pos],pos,__environ[pos],__environ[pos]);
            pos++;
        }
    }
    else if(strcmp(args,"-addr")==0) printf("__environ: %p (almacenado en %p)\nmain arg[3]: %p (almacenado en %p)\n",__environ, &__environ, env, &env);
    else printf("Uso: showenv [-environ | -addr]\n");
}

void doFork(tList* lista)
{
	pid_t pid;
	
	if ((pid=fork())==0){
        freeAllBGList(lista);
		printf ("ejecutando proceso %d\n", getpid());
	}
	else if (pid!=-1)
		waitpid (pid,NULL,0);
}


void doExec(char *args, char**args_ptr){
    char* command;
    char* argv[MAXARGV];
    int i;
    if(args != NULL){
        command = args;
        for(int j = 0; j<MAXARGV;j++) {
            argv[j] = NULL;
        }
        i = 0;
        while (args != NULL && i < MAXARGV)
        {
            argv[i] = args;
            printf("argv[%d] = %s ",i,argv[i]);
            i++;
            args = strtok_r(NULL," \n\t", args_ptr);
        }
        if(execvp(command, argv) == -1) perror("Error en exec: ");
    }
    else printf("Uso: exec prog [args...]\n");
}


void doCommand(char* cmd,char* args,char** args_ptr, tList* list){
    int pid;
    int i;
    char* argv[MAXARGV];
    bool bg = false;
    if(cmd != NULL){
        argv[0] = cmd;
        for(i = 1; i < MAXARGV; i++){
            argv[i] = args;
            args = strtok_r(NULL," \n\t", args_ptr);
        }
        for(i = 1; i < MAXARGV; i++){
            if(argv[i] == NULL){
                if(strcmp(argv[i-1],"&") == 0) {
                    bg = true;
                    argv[i-1] = NULL;
                }
                break;
            }
        }
        if((pid = fork()) == 0){
            execvp(argv[0],argv);
            perror("Error:");
	    exit(0);
        }
        else if(pid == -1) perror("Error:");
        else if(bg) insertBGProc(list,newBGproc(pid,argv[0],"ACTIVO",0));
        else waitpid(pid,NULL,0);
    }
}

void printfBGproc(tBGProc proc){ //Funcion auxiliar para imprimir los datos de un bloque de memoria
    struct tm* calendar;
    char timeStr[30];
    int prior;
    errno = 0; //Limpiamos errno para verificar la validez de getpriority
    prior = getpriority(PRIO_PROCESS,proc.pid);
    if(prior == -1 && errno != 0) perror("prior = -1:");
    calendar = localtime(&proc.launchTime); //Creamos struc tm con la hora de reserva
    strftime(timeStr,30,"%d/%m/%Y %X",calendar); //Creamos un string con el formato deseado
    printf("%d \t %s p=(%d) %s %s (%03d) %s\n",proc.pid,getUser(getuid()),prior,timeStr,proc.wstatus,proc.signal,proc.command); //Imprimir datos
}
char* getNewStatus(int wstatus,int* signal){
    if(WIFEXITED(wstatus)){
        *signal = WEXITSTATUS(wstatus);
        return "TERMINADO";
    }
    else if(WIFSIGNALED(wstatus)){
        *signal = WTERMSIG(wstatus);
        return "SEÑALADO";
    }
    else if(WIFSTOPPED(wstatus)){
        *signal = WSTOPSIG(wstatus);
        return "PARADO";
    }
    else if(WIFCONTINUED(wstatus)){
        *signal = 0;
        return "ACTIVO";
    }
    else {
        return "DESCONOCIDO";
    
    }
}

void doJobs(tList* list){
    tBGProc* proces;
    tPos p;
    pid_t pid;
    int wstatus;
    int signal;
    p = *list;
    while (p != NULL)
    {
        proces = (tBGProc*)getData(*list,p);
        if((pid = waitpid(proces->pid,&wstatus,WNOHANG|WUNTRACED|WCONTINUED)) == 0);//Actualizamos estado
        else if(proces->pid == pid){
            strcpy(proces->wstatus, getNewStatus(wstatus,&signal));
            proces->signal = signal;
        }
        printfBGproc(*proces);
        p->data = (void*)proces;
        p = next(*list,p);
    }
}

void doDelJobs(char *args, char**args_ptr, tList* list){
    bool term = false, sig = false;
    tBGProc* proces;
    tPos p;
    tPos r;
    pid_t pid;
    int wstatus;
    int signal;
    if(args == NULL) doJobs(list); //Comprobamos argumentos
    else{
        term = (strcmp(args,"-term")==0);
        sig = (strcmp(args,"-sig")==0);
        if((args = strtok_r(NULL," \n\t", args_ptr))!=NULL){
            term = (strcmp(args,"-term")==0);
            sig = (strcmp(args,"-sig")==0);
        }
        p = *list;
        while (p != NULL)
        {
            proces = (tBGProc*)getData(*list,p);
            if((pid = waitpid(proces->pid,&wstatus,WNOHANG|WUNTRACED))==0);//Actualizamos estado si hace falta
            else if(proces->pid == pid){
                strcpy(proces->wstatus, getNewStatus(wstatus,&signal));
                proces->signal = signal;
            }
            p->data = (void*)proces;
            if(strcmp(proces->wstatus,"TERMINADO")==0 && term){ //Comprobamos si hay que borrar terminado
                r = p;
                p = next(*list,p);
                deleteBGProcIn(list,r);
            }
            else if(strcmp(proces->wstatus,"SEÑALADO")==0 && sig){ //Comprobamos si hay que borrar señalado
                r = p;
                p = next(*list,p);
                deleteBGProcIn(list,r);
            }
            else p = next(*list,p);
        }
    }
}
