#include "variableStack.h"

VariableStack::VariableStack(int maxSize) : realMax(maxSize), max(2 * maxSize) {
  typePushed = false;
}

void VariableStack::push(int number) {
  if (this->elements.size() == max) {
    throw std::out_of_range("Maximum stack limit reached!");
  }
  this->types.push(TYPE_INT);
  if (!typePushed) {
    this->realTypes.push(REALTYPE_INT);
  }
  this->elements.push(number);
  typePushed = false;
}
