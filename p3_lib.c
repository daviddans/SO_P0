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
        else perror("Error en showvar");
        pos = BuscarVariable(args, __environ);
        if (pos!= -1) printf("  Con __environ %s(%p) @(%p)\n", __environ[pos], __environ[pos], &__environ);
        else perror("Error en showvar");
        printf("    Con getenv %s (%p) \n", getenv(args), getenv(args));
    }
}

uid_t getUserUid(char *username){
    struct passwd* pas = getpwnam(username);
    return pas->pw_uid;
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
        if(strcmp(args,"-l")==0){
            args = strtok_r(NULL," \n\t", args_ptr);
            euser = getUserUid(args);
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



void doCommand(char* args){
    if (false){
        //dosomethin
    }
    else{
    }
    printf("%s",args);
}