#ifndef VARIABLESTACK
#define VARIABLESTACK

#include <stack>

#include "globalStructures.h"

#define INVALID 99
#define TYPE_NOT_SET 0
#define TYPE_INT 1
#define TYPE_FLOAT 2
#define TYPE_LONG 3
#define TYPE_DOUBLE 4
#define TYPE_BOOL 5
#define TYPE_REFERENCE 6

#define REALTYPE_BYTE 1
#define REALTYPE_BOOL 2
#define REALTYPE_CHAR 3
#define REALTYPE_SHORT 4
#define REALTYPE_INT 5
#define REALTYPE_FLOAT 6
#define REALTYPE_DOUBLE 7
#define REALTYPE_REFERENCE 8
#define REALTYPE_LONG 9

class VariableStack {
 private:
  std::stack<u4> elements;
  std::stack<u1> types;
  std::stack<u1> realTypes;

  bool typePushed;
  const int realMax;

 public:
  const int max;
  void push(int);
  VariableStack(int);
};

#endif  // VARIABLESTACK
