#include "frame.h"

#include "operations.h"

FrameStack::FrameStack(Method_info method_info, std::vector<CP_info> cp_info) {
  frame* aux = (frame*)malloc(sizeof(frame));

  aux->method_info = method_info;
  aux->cp_info = cp_info;
  aux->varStack = new VariableStack(aux->method_info.attributes->info.code_info.maxStack);
  aux->localVars = new LocalVariables(aux->method_info.attributes->info.code_info.maxLocals);
  startPC(aux);
  Operations::setFrame(aux);
  Operations::setFrames(&frames);
  Operations::setFrameStack(this);

  MethodArea::setFrameStack(this);
  frames.push(aux);
}

void FrameStack::startPC(frame* frame) {
  frame->pc = frame->method_info.attributes->info.code_info.code;
}

void FrameStack::execute() {
  while (nextInstruction()) {
    Operations::run(opcode);
  }
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
    // TODO: que?
    // frames.pop();
  }
  if (frames.empty()) {
    Operations::setFrame(nullptr);
    Operations::setFrames(nullptr);
    exit(0);
  }
  Operations::setFrame(frames.top());
  Operations::setFrames(&frames);
}
