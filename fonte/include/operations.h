#include "runClass.h"

class Operations {
 private:
  static struct frame *frame;
  static stack<struct frame *> *frames;
  static FrameStack *frameStack;

 public:
  Operations(struct frame *);

  static void setFrame(struct frame *);
  static void setFrames(stack<struct frame *> *);
  static void setFrameStack(FrameStack *);

  static void run(int);
};
