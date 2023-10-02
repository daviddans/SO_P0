//Author1: David Dans Villares Login: david.dans.villares@udc.es
//Author2: Pablo Teijeiro Torrón Login: pablo.teijeirot@udc.es


#include "p1_lib.h" //Cabecera con las dependencias del codigo

#define MAX_IN 1000 //Entrada maxima
#define MAX_REC 10 //Numero maximo de recursiones


//Funcion para gestionar los comandos y parametros introducidos
void inputHandler(char * input, bool * onRunTime, tList* listaComandos, tList* listaFicheros, int* control)
{
	int i; //variable para command N
	tPos pos; //variable para command N
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
	else if(strcmp(input,"command")==0){//Command hace una llamada recursiva a la función para repetir la ejecución de un comando del historico
		(*control)++;
		printf("%d",*control);
		if(*control<MAX_REC){
			printf("%d",*control);
			pos = first(*listaComandos);
			puts("uno");
			i = 0;
			while(pos != NULL && i<atoi(args)){
				pos = next(*listaComandos, pos);
				i++;
			}
			if(pos == NULL) printf("No se encontro el comando: %s", args);
			else{
				free(args);
				puts("1");
				args = getData(*listaComandos, pos);
				puts("2");
				strcpy(input, args);
				puts("3");
				inputHandler(input, onRunTime, listaComandos, listaFicheros, control);
				puts("4");
			}
		}
		else puts("Demasiada recursion!!!\n");
	} 
	else if(strcmp(input,"\n")!=0) printf("Comando no reconocido. Usa help para obtener una lista de comandos\n");//Si hay un comando no reconocido se imprime un error

}



//Funcion Main 
int main(){
	tList listaComandos; //Lista para el historial de comandos
	tList listaFicheros; //Lista para los ficheros abiertos
	int control; //variable para controlar la recursion
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
			control = 0;
			insertCMD(&listaComandos, input);//Añadimos comando al historico
			inputHandler(input, &onRunTime, &listaComandos, &listaFicheros, &control);//Procesar entrada
		}
	}
	//Borrado de las listas
	deleteList(&listaComandos);
	deleteList(&listaFicheros);
	return 0;
}