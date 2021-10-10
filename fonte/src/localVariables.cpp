#include "localVariables.h"

#include <cstdlib>

LocalVariables::LocalVariables(u2 maxSize) : max(maxSize), realMax(2 * maxSize), isTwoSlots(false) {
  elements = (u4 *)calloc(max * 2, sizeof(u4));
  types = (u1 *)calloc(max * 2, sizeof(u1));
}
