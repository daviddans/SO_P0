#include "p0_lib.h"
#include "p0_lista.h"

int main(){
    SList lista;
    createEmptyList(&lista);
    char * cadena1 = "Hola";
    char * cadena2 = "Buenas tardes";
    insertItem(&lista,cadena1);
    imprimirListado(lista);
    insertItem(&lista,cadena2);
    imprimirListado(lista);
    if(getElement(lista,2,cadena1)) puts(cadena1);
    else puts("Error1");
    return 0;
}