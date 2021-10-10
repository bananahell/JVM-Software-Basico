#ifndef LOCALVARIABLES
#define LOCALVARIABLES

#include "globalStructures.h"

class LocalVariables {
 private:
  u4* elements;
  u1* types;

  const u2 max;
  const u2 realMax;
  const bool isTwoSlots;

 public:
  LocalVariables(u2);
};

#endif  // LOCALVARIABLES
