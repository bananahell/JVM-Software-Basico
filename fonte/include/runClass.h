#include <map>
#include <vector>

#include "frame.h"
#include "writeClassAttributes.h"

using namespace std;

void runClass(ClassFile *);
int findMain(ClassFile *);
void addClass(ClassFile *);
void addClass(string);

class MethodArea {
 public:
  static map<string, ClassFile *> classFiles;
  static FrameStack *frameStack;
  static void setFrameStack(FrameStack *);
};
