#include "p2_lib.h" //Inclusion de librerías de las practicas antetriores

#define MAXVAR 32000
#define MAXARGS 16 //Numero de argumentos maximos para pasar a un proceso nuevo

void doUid(char *args, char**args_ptr); //muestra o cambia credenciales
void doShowVar(char *args, char** env); //muestra variable de entorno
void doChangeVar(); //cambia variable de entorno
void doSubsVar(); //intercambia variables de entorno
void doShowEnv(); //muestra entorno
void doFork(); //crea proceso hijo
void doExec(); //ejecuta un un programa sin crear un proceso hijo
void doJobs(); //lista procesos en segundo plano
void doCommand(char* args);