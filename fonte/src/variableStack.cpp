#include "variableStack.h"

VariableStack::VariableStack(int maxSize) : realMax(maxSize), max(2 * maxSize) {
  typePushed = false;
}
