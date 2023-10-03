//Codigo para probara la funcionalidad de las listas
#include "p1_lib.h"
#define MAX_IN 500

int main(){
    printf("--Probando lista CMD--\n\n");
    char input[MAX_IN];
    char cmd[MAX_IN];
    tList listaCMD;
    tList listaFCH;
    createEmptyList(&listaCMD);
    createEmptyList(&listaFCH);
    if(isEmptyList(listaCMD)) puts("ta vasio\n");
    
    for(int i = 0; i< 5;i++){
	printf("--> ");//Imprimir prompt
	fgets(input,MAX_IN,stdin);//Leer entrada estandar
	printf("%s", input);
    strcpy(cmd,input);
    insertCMD(&listaCMD, cmd);
    }
    printCMD(listaCMD, -1);


    printf("--Probando lista FCH--\n\n");

    for(int i = 0; i< 5;i++){
	printf("--> ");//Imprimir prompt
	fgets(input,MAX_IN,stdin);//Leer entrada estandar
	printf("%s", input);
    strcpy(cmd,input);
    insertFile(&listaFCH, cmd, i);
    }

    printFiles(listaFCH);   
}