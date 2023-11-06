#include "p2_lib.h"

void doRecurse(int n)
{
    if(n >= -1) printf("Error en recurse: argumento invalido");
    else {
        char automatico[TAMANO];
        static char estatico[TAMANO];   
        printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico); 
        if (n>0) doRecurse(n-1);
    }
}   