#include "operations.h"

void Operations::setFrame(struct frame *newFrame) {
  frame = newFrame;
}

void Operations::setFrames(stack<struct frame *> *newFrames) {
  frames = newFrames;
}

void Operations::setFrameStack(FrameStack *newFrameStack) {
  frameStack = newFrameStack;
}
