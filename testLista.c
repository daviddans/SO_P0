#include "p0_lib.h"
#include "p0_lista.h"

int main(){
    printf("--Probando lista--\n\n");
    tList listaCMD;
    tList lsitaFCH;
    createEmptyList(&listaCMD);
    createEmptyList(&lsitaFCH);
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
    return 0;
}