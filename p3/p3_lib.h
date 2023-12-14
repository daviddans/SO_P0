#include "p2_lib.h" //Inclusion de librerías de las practicas antetriores

#define MAXVAR 1000 //Tamaño maximo considerado para una variable de entorno
#define MAXARGV 10 //Numero de argumentos maximos para pasar a un proceso nuevo
#define __USE_XOPEN_EXTENDED //Activar macro WCONTINUED
struct SEN
{
    char* nombre;
    int senal;
};


void doUid(char *args, char**args_ptr); //muestra o cambia credenciales
void doShowVar(char *args, char** env); //muestra variable de entorno
void doChangeVar(char *args, char**args_ptr, char **env); //cambia variable de entorno
void doSubsVar(char *args, char**args_ptr, char **env); //intercambia variables de entorno
void doShowEnv(char *args, char** env); //muestra entorno
void doFork(tList* list); //crea proceso hijo
void doExec(char *args, char**args_ptr); //ejecuta un un programa sin crear un proceso hijo
void doJobs(tList* list); //lista procesos en segundo plano
void doDelJobs(char *args, char**args_ptr, tList* list); //borra procesos en segundo plano
void doCommand(char *cmd, char* args, char** args_ptr, tList* list); //para cualquier comando no reconocido buscara en path
