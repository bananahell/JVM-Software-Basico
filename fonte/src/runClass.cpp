#include "runClass.h"

map<string, ClassFile *> MethodArea::classFiles;

void runClass(ClassFile *classFile) {
  int main_index = findMain(classFile);
  if (main_index == -1) {
    cout << "Parcero deu ruim" << endl;
    return;
  }
  addClass(classFile);
  FrameStack::addFrame(classFile->getMethods().at(main_index), classFile->getConstantPool());
}

int findMain(ClassFile *classFile) {
  int main_index = -1;
  vector<Method_info> allMethods = classFile->getMethods();
  for (int i = 0; i < classFile->getMethodsCount(); i++) {
    int flags = allMethods.at(i).access_flags;
    int name_index = allMethods.at(i).name_index;
    string name = ReadClassByteCode::getUTF8(classFile->getConstantPool().at(name_index - 1));
    int descriptor_index = allMethods.at(i).descriptor_index;
    string descriptor = ReadClassByteCode::getUTF8(classFile->getConstantPool().at(descriptor_index - 1));
    if (name == "main") {
      if (descriptor == "([Ljava/lang/String;)V") {
        if ((flags & 0x09) == 0x09) {
          main_index = i;
          break;
        }
      }
    }
  }
  return main_index;
}

void addClass(ClassFile *classFile) {
  int thisNameIndex = classFile->getConstantPool().at(classFile->getThisClass() - 1).info.class_info.name_index;
  CP_info thisCPInfo = classFile->getConstantPool().at(thisNameIndex - 1);
  string thisClassName = ReadClassByteCode::getUTF8(thisCPInfo);
  MethodArea::classFiles.insert(pair<string, ClassFile *>(thisClassName, classFile));
}

void MethodArea::setFrameStack(FrameStack *newFrameStack) {
  frameStack = newFrameStack;
}
