#include "p0_lib.h"
#include "p0_lista.h"

int main(){
    printf("--Probando lista--\n\n");
    tLista listaCMD;
    tLista listaFCH;
    createEmptyList(&listaCMD);
    createEmptyList(&listaFCH);
    puts("listas inicializadas\n");
    insertComand(&listaCMD,"comando 1");
    insertComand(&listaCMD,"comando 2");
    insertComand(&listaCMD,"comando 3");
    int i =0;
    while(getCommand(listaCMD,i) != NULL)
    {
        printf("listaCMD%d : %s\n",i, getCommand(listaCMD,i));
        i++;
    }
    insertFile(&listaFCH,"fichero1.algo", 2);
    insertFile(&listaFCH,"fichero2.algo", 3);
    insertFile(&listaFCH,"fichero3.algo", 1);
    insertFile(&listaFCH,"fichero4.algo", 5);
    
    printFile(listaFCH, 0);
    printFile(listaFCH, 1);
    printFile(listaFCH, 2);
    printFile(listaFCH, 3);
    return 0;
}