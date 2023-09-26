#include "p0_lib.h"
#include "p0_lista.h"

int main(){
    tLista listaComandos;
    tLista listaFicheros;
    createEmptyList(listaComandos);
    createEmptyList(listaFicheros);
    instertComand(listaComandos,"hello world");
    return 0;
}