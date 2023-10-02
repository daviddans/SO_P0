//Author1: David Dans Villares Login: david.dans.villares@udc.es
//Author2: Pablo Teijeiro Torrón Login: pablo.teijeirot@udc.es


#include "p1_lib.h" //Cabecera con las dependencias del codigo

#define MAX_IN 1000 //Entrada maxima

//Funcion para gestionar los comandos y parametros introducidos
void inputHandler(char * input, bool * onRunTime, tList* listaComandos, tList* listaFicheros)
{
	char * args = strtok(input," \n\t"); //Troceamos la entrada y la guardamos en una variable para poder gestionar los argumentos  
	//Cadena de condicionales para llamar a la función correspondiente al comando, para ver el codigo de cada función consultar p0_lib.c
	args = strtok(NULL," \n\t"); //Descartamos el primer trozo (comando) para quedarnos unicamente los argumentos
	if(strcmp(input,"bye")==0) exitShell(onRunTime);
	else if(strcmp(input,"quit")==0) exitShell(onRunTime);
	else if(strcmp(input,"exit")==0) exitShell(onRunTime);
	else if(strcmp(input,"help")==0) help(args);
	else if(strcmp(input,"authors")==0) authors(args);
	else if(strcmp(input,"date")==0) printDate();
	else if(strcmp(input,"time")==0) printTime();
	else if(strcmp(input,"pid")==0) pid(args);
	else if(strcmp(input,"chdir")==0) changeDir(args);
	else if(strcmp(input,"hist")==0) hist(args,listaComandos);
	else if(strcmp(input,"\n")!=0) printf("Comando no reconocido. Usa help para obtener una lista de comandos\n");//Si hay un comando no reconocido se imprime un error

}
//Funcion Main 
int main(){
	tList listaComandos; //Lista para el historial de comandos
	tList listaFicheros; //Lista para los ficheros abiertos
	createEmptyList(&listaComandos); //Inicialización lista
	createEmptyList(&listaFicheros); //Inicialización lista
	insertFile(&listaFicheros,"entrada estandar", 0);
	insertFile(&listaFicheros,"salida estandar", 1);
	insertFile(&listaFicheros,"error estandar", 2);
	bool onRunTime = true; //Bool para controlar la ejecución del bucle
	char input[MAX_IN]; //String para guardar la entrada del usuario
	printf("Iniciando Shell ^^ Usa help para obtener una lista de comandos\n");//Mensaje de inicio
	//Bucle de la shell
	while(onRunTime){
		printf("--> ");//Imprimir prompt
		fgets(input,MAX_IN,stdin);//Leer entrada estandar
		if(input != NULL){
			insertCMD(&listaComandos, input);//Añadimos comando al historico
			inputHandler(input, &onRunTime, &listaComandos, &listaFicheros);//Procesar entrada
		}
	}
	return 0;
}