#include "p0_lib.h"
#include "p0_lista.h"


int main(){
    printf("--Probando lista CMD--\n\n");
    tList listaCMD;
    tList listaFCH;
    createEmptyList(&listaCMD);
    createEmptyList(&listaFCH);
    if(isEmptyList(listaCMD)) puts("ta vasio\n");
    insertCMD(&listaCMD, "comando 1");
    insertCMD(&listaCMD, "get");
    insertCMD(&listaCMD, "Alferedo 123123");
    insertCMD(&listaCMD, "lorem ipsunm biblica dasdasdasdasd fucidasmdasmdasmdmasdmasdmasmdasmd LOLLLOLDASDASDASDASDASDASDASDASSSSSSSSSSSsaddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddsssssssssssaweq2223233");
    if(isEmptyList(listaCMD)) puts("Sigue vasio??\n");
    int i = 0;
    while(i<=countCMD(listaCMD)-1){
        printf("cmd%d : %s\n",i, getCMD(listaCMD, i));
        i++;;
    }
    if(!isEmptyList(listaCMD)) deleteCMDList(&listaCMD);
    if(isEmptyList(listaCMD)) puts("Lista Borrada!!\n");
    printf("--Probando lista FCH--\n\n");
    if(isEmptyList(listaFCH)) puts("ta vasio\n");
    insertFCH(&listaFCH, "biblia23",3);
    insertFCH(&listaFCH, "biblia24",4);
    insertFCH(&listaFCH, "biblia25",5);
    insertFCH(&listaFCH, "biblia28",8);
    insertFCH(&listaFCH, "biblia27",7);
    insertFCH(&listaFCH, "biblia26",6);
    
        tPos pos = first(listaFCH);
    tFile* file;
    i = 1;
    while(pos != NULL){
        file = getData(listaFCH,pos);
        printf("%d : %s\n",i, file->path);
        i++;
        pos = next(listaFCH, pos);
    }

    
    if(isEmptyList(listaFCH)) puts("Sigue vasio??\n");
    if(deleteFCH(&listaFCH,4)) puts("Borrado el 4\n");
    if(getFHC(listaFCH,0) == NULL) puts("No hay 0\n");
    if(getFHC(listaFCH,4) == NULL) puts("No hay 4\n");
    insertFCH(&listaFCH, "LA santa bliblia",4);

    return 0;
}