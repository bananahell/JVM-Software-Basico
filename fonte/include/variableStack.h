#ifndef VARIABLESTACK
#define VARIABLESTACK

#include <stack>

#include "globalStructures.h"

class VariableStack {
 private:
  std::stack<u4> elements;
  std::stack<u1> types;
  std::stack<u1> realTypes;

  bool typePushed;
  const int realMax;

 public:
  const int max;
  VariableStack(int);
};

#endif  // VARIABLESTACK
