#include <iostream>
#include <string>
#include "Classfile.h"
/*#include "leitor.h"*/


using namespace std;

int main(int argc, char *argv[]) {
  Classfile *classfile;
  char *Arquivo;

if(argc > 1) {
    Arquivo = (char *) malloc(strlen(argv[1]) * sizeof(char));
    strcpy(Arquivo, argv[1]);
  } else {
    printf("O arquivo .class nao foi incluido.\nEncerrando o programa.......\n");
    exit(0);
  }

  class_file = (Classfile *) malloc(sizeof(Classfile));

  class_file = lerArquivo(class_file, nomeArquivo);

  imprimirClassFile(class_file);
  
  return 0;
}
