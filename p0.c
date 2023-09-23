//Author1: David Dans Villares Login: david.dans.villares@udc.es
//Author2: Pablo Teijeiro ... Login: ...@udc.es

#include "p0_lib.h"//Fichero con todas las dependencias del codigo
#define MAX_IN 1000

//Funcion para gestionar los comandos y parametros introducidos
void inputHandler(char * input, bool * onRunTime)
{
	char * args = strtok(input," \n\t"); //Troceamos la entrada y la guardamos en una variable para poder gestionar los argumentos  
	args = strtok(NULL," \n\t"); //Descartamos el primer trozo (comando) para quedarnos unicamente los argumentos
	//Cadena de condicionales para llamar a la función correspondiente al comando, para ver el codigo de cada función consultar p0_lib.c
	if (input!=NULL){
		if(strcmp(input,"bye")==0) exitShell(onRunTime);
		else if(strcmp(input,"quit")==0) exitShell(onRunTime);
		else if(strcmp(input,"exit")==0) exitShell(onRunTime);
		else if(strcmp(input,"help")==0) help(args);
		else if(strcmp(input,"authors")==0) authors(args);
		else if(strcmp(input,"\n")!=0) printf("Comando no reconocido. Usa help para obtener una lista de comandos\n");
	}
}
//Funcion Main
int main(){
	bool onRunTime = true; //Bool para controlar la ejecución del bucle
	char input[MAX_IN]; //String para guardar la entrada del usuario
	printf("Iniciando Shell ^^ Usa help para obtener una lista de comandos\n");//Mensaje de inicio
	//Bucle de la shell
	while(onRunTime){
		printf("--> ");//Imprimir prompt
		fgets(input,MAX_IN,stdin);//Leer entrada estandar
		inputHandler(input, &onRunTime);//Procesar entrada
	}
	return 0;
}