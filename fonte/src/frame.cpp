#include "frame.h"

#include "operations.h"

void FrameStack::addFrame(Method_info method_info, std::vector<CP_info> cp_info) {
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

  // remove the top of stack if there isn't any instructions on current method
  this->pop();

  // checks if there is any elements left
  if (threads.empty()) {
    return false;
  }

  return true;
}
