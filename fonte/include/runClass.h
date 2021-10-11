#include <map>
#include <vector>

#include "frame.h"
#include "writeClassAttributes.h"

using namespace std;

void runClass(ClassFile *);
void addClass(ClassFile *);
void addClass(string);

class MethodArea {
 private:
  static FrameStack *frameStack;

 public:
  static map<string, ClassFile *> classFiles;
  static void setFrameStack(FrameStack *);
};
