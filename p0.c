#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#Define IN_LEN 100

int tro
void inputHandler(){

}
int main(){
    char input[IN_LEN];
    char *args;
    bool terminado = false;
    while(!terminado){
        printf("-->");
        fgets(input, IN_LEN, stdin);
        puts(input);
        inputHandler();
    }
    return 0;
}