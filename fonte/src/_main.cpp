#include <iostream>
#include <string>
#include <vector>

#include "runClass.h"

using namespace std;

int main(int argc, char *argv[]) {
  const char *className = "class/default.class";

  // Quando igual a 1 nao foi passado nenhum parametro
  if (argc > 1) {
    className = argv[1];
  } else {
    cout << "Using default.class...." << endl;
  }

  FILE *fp = fopen(className, "rb");
  if (fp == NULL) {
    cout << "There was a problem opening your file " << className << "...." << endl;
    return 0;
  }

  ClassFile *classFile = new ClassFile(fp);

  string outputFileName = "output.txt";
  bool writeSuccess = writeAllToFile(classFile, outputFileName);
  if (writeSuccess) {
    cout << "Success! Results in file " << outputFileName << endl;
  }

  runClass(classFile);

  fclose(fp);
  return 0;
}
