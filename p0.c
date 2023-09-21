#include "p0_lib.h"
#include <stdio.h>
#include <stdbool.h>
#define IN_LEN 100

int main(){
    char input[IN_LEN];
    bool terminado = false;
    while(!terminado){
        printf("-->");
        fgets(input, IN_LEN, stdin);
        puts(input);
        inputHandler();
    }
    return 0;
}