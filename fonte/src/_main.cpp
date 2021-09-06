#include <iostream>
#include <string>
#include <vector>

#include "classFile.h"
using namespace std;

int main(int argc, char *argv[]) {
  const char *nome_classe = "default.class";

  // Quando igual a 1 nao foi passado nenhum parametro
  if (argc > 1) {
    nome_classe = argv[1];
  }

  FILE *fp = fopen(nome_classe, "rb");
  if (fp == NULL) {
    cout << "Erro no arquivo : " << nome_classe << endl;
    return 0;
  }

  ClassFile *classe = new ClassFile(fp);
  cout << "Magic number = " << classe->getMagicNumber() << endl;
  cout << "Minor version = " << classe->getMinorVersion() << endl;
  cout << "Major version = " << classe->getMajorVersion() << endl;
  cout << "Interfaces count = " << classe->getInterfacesCount() << endl;
  cout << "Fields count = " << classe->getFieldsCount() << endl;
  cout << "Methods count = " << classe->getMethodsCount() << endl;
  fclose(fp);
  return 0;
}
