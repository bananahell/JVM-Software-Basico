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
  } else {
    cout << "Using default.class...." << endl;
  }

  FILE *fp = fopen(nome_classe, "rb");
  if (fp == NULL) {
    cout << "There was a problem opening your file " << nome_classe << "...." << endl;
    return 0;
  }

  ClassFile *classe = new ClassFile(fp);
  cout << "--------------------------------" << endl;
  cout << "| Magic #        |  " << classe->getMagicNumber() << endl;
  cout << "| Minor v.       |  " << classe->getMinorVersion() << endl;
  cout << "| Major v.       |  " << classe->getMajorVersion() << endl;
  cout << "| Interfaces #   |  " << classe->getInterfacesCount() << endl;
  cout << "| Fields #       |  " << classe->getFieldsCount() << endl;
  cout << "| Methods #      |  " << classe->getMethodsCount() << endl;
  cout << "--------------------------------" << endl;
  fclose(fp);
  return 0;
}
