#include "runClass.h"

map<string, ClassFile *> MethodArea::classFiles;
FrameStack *MethodArea::frameStack = nullptr;

void runClass(ClassFile *classFile) {
  int main_index = FrameStack::findMain(classFile);
  if (main_index == -1) {
    cout << "Parcero deu ruim" << endl;
    return;
  }
  addClass(classFile);
  cout << "main_index = " << main_index << endl;
  cout << "classFile->getMethods().at(main_index).attributes[0].info.code_info.maxStack = "
       << classFile->getMethods().at(main_index).attributes[0].info.code_info.maxStack << endl;
  FrameStack frameStack(classFile);
  cout << "Passei do construtor de FrameStack o/" << endl;
}

void addClass(ClassFile *classFile) {
  int thisNameIndex = classFile->getConstantPool().at(classFile->getThisClass() - 1).info.class_info.name_index;
  CP_info thisCPInfo = classFile->getConstantPool().at(thisNameIndex - 1);
  string thisClassName = ReadClassByteCode::getUTF8(thisCPInfo);
  MethodArea::classFiles.insert(pair<string, ClassFile *>(thisClassName, classFile));
}

void MethodArea::setFrameStack(FrameStack *newFrameStack) {
  MethodArea::frameStack = newFrameStack;
}
