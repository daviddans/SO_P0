#include "p0_Lista_H"
#include <stdlib.h>
//en principio solo hacen falta el createnode, createlist, insertitem y removeitem
void createEmptyList(SList *L){
    *L = NULL;
}

bool createNode(SPosL *p){
    *p = malloc(sizeof(SNode));
    return *p != NULL;
}

bool insertElement(char comando[], SPosL p, SList *L){
    SPosL q;
    if(q->next < MAX_DATA){

    }
} 

void deleteElement(SPosL p, SList* L){

}
