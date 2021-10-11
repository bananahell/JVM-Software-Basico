#ifndef FRAME
#define FRAME

#include <stack>
#include <vector>

#include "classFile.h"
#include "localVariables.h"
#include "variableStack.h"

typedef struct frame {
  unsigned char *pc;
  std::vector<CP_info> cp_info;
  VariableStack *varStack;
  LocalVariables *localVars;
  Method_info method_info;
};

class FrameStack {
 private:
  int opcode;
  void startPC(frame *);
  bool nextInstruction();
  std::stack<frame *> frames;

 public:
  FrameStack(ClassFile *);
  static int findMain(ClassFile *);
  void execute();
  void pop();
};

#endif  // FRAME
