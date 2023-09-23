//Author1: David Dans Villares Login: david.dans.villares@udc.es
//Author2: Pablo Teijeiro ... Login: ...@udc.es
#include "p0_lib.h"
#define MAX_IN 1000

void inputHandler(char * input, bool * onRunTime)
{
	char * args = strtok(input," \n\t");
	args = strtok(NULL," \n\t");
	if (input!=NULL){
		if(strcmp(input,"bye")==0) exitShell(onRunTime);
		else if(strcmp(input,"quit")==0) exitShell(onRunTime);
		else if(strcmp(input,"exit")==0) exitShell(onRunTime);
		else if(strcmp(input,"help")==0) help(args);
		else printf("Comando no reconocido. Usa help para obtener una lista de comandos\n");
	}
}

int main(){
	bool onRunTime = true;
	char input[MAX_IN];
	printf("Iniciando Shell ^^ Usa help para obtener una lista de comandos\n");
	while(onRunTime){
		printf("--> ");
		fgets(input,MAX_IN,stdin);
		inputHandler(input, &onRunTime);
	}
	return 0;
}