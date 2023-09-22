//Author1: David Dans Villares Login: david.dans.villares@udc.es
//Author2: Pablo Teijeiro ... Login: ...@udc.es
#import "p0_lib.h"

int main(){
  bool onRunTime = true;
  char * input;
  while(onRunTime){
    printf("Iniciando Shell ^^");
    input = readline("-->");
    inputHandler(input, onRunTime);
  }
  return 0;
}
