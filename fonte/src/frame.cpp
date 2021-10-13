#include "frame.h"

#include <iomanip>

#include "operations.h"

FrameStack::FrameStack(ClassFile* classFile) {
  frame* aux = (frame*)malloc(sizeof(frame));
  int main_index = findMain(classFile);
  aux->method_info = (Method_info)classFile->getMethods().at(main_index);
  aux->cp_info = classFile->getConstantPool().data();

  int maxStack = aux->method_info.attributes[0].info.code_info.maxStack;
  aux->varStack = new VariableStack(maxStack);
  int maxLocals = aux->method_info.attributes[0].info.code_info.maxLocals;
  aux->localVars = new LocalVariables(maxLocals);
  startPC(aux);
  frames.push(aux);
  Operations::setFrame(frames.top());
  Operations::setFrames(&frames);
  Operations::setFrameStack(this);

  MethodArea::setFrameStack(this);
  opcode = 0;
}

void FrameStack::startPC(frame* frame) {
  frame->pc = frame->method_info.attributes->info.code_info.code;
}

void FrameStack::execute() {
  while (nextInstruction()) {
    cout << "opcode: " << setw(3) << opcode << " -> ";
    Operations::run(opcode);
  }
}

int FrameStack::findMain(ClassFile* classFile) {
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

bool FrameStack::nextInstruction() {
  if (frames.empty()) {
    return false;
  }
  int currentPC = frames.top()->pc - frames.top()->method_info.attributes->info.code_info.code;
  int codeLength = frames.top()->method_info.attributes->info.code_info.codeLength;
  if (currentPC < codeLength) {
    opcode = *frames.top()->pc;
    frames.top()->pc++;
    return true;
  }
  this->pop();
  if (frames.empty()) {
    return false;
  }
  return true;
}

void FrameStack::pop() {
  if (!frames.empty()) {
    delete frames.top()->varStack;
    delete frames.top()->localVars;
    frames.pop();
  }
  if (frames.empty()) {
    Operations::setFrame(nullptr);
    Operations::setFrames(nullptr);
    exit(0);
  }
  Operations::setFrame(frames.top());
  Operations::setFrames(&frames);
}
