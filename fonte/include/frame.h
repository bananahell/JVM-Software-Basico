#ifndef FRAME
#define FRAME

#include <stack>
#include <vector>

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
  FrameStack(Method_info, std::vector<CP_info>);
  void execute();
  void pop();
};

#endif  // FRAME
