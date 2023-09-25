 #ifndef p0_Lista_H
 #define p0_Lista_H   
 #include <stdbool>
 #include <stdio.h>
 #include <string.h>
 #include <malloc.h>
 #define LENGTH 100
 #define LNULL NULL;
 typedef struct SNode * SPosL; 
 struct SNode{
          char comando[LENGTH];
          SPosL next;
 }
 typedef SPosL SList;

void createEmptyList(SList *L);   
void deleteList(SList *L);    
SPosL createItem(char command);
int insertItem(SList *L, char *command);                                             
void deleteElement(SPosL p, SList *L);  
void ImprimirListado(SList L);
char Buscar(SList L, int pos);   

