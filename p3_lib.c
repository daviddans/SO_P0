#include "p3_lib.h"

void printfBGproc(tBGProc proc){ //Funcion auxiliar para imprimir los datos de un bloque de memoria
    struct tm* calendar;
    char timeStr[30];
    calendar = localtime(&proc.launchTime); //Creamos struc tm con la hora de reserva
    strftime(timeStr,30,"%d/%m/%Y %X",calendar); //Creamos un string con el formato deseado
    printf("%d \t user prior %s Status (statusReturn), %s",proc.pid,timeStr,proc.command); //Imprimir datos
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
  if(aux != NULL) 
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

void doCommand(char* args){
    if (false){
        //dosomethin
    }
    else{
    }
    printf("%s",args);
}