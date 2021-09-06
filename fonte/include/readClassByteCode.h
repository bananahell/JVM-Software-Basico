#include <vector>

#include "globalStructures.h"

using namespace std;

class ReadClassByteCode {
 public:
  ReadClassByteCode();
  u1 read1byte(FILE *);
  u2 read2bytes(FILE *);
  u4 read4bytes(FILE *);
  UTF8_INFO getUTF8Info(FILE *);
  INTEGER_INFO getIntegerInfo(FILE *);
  FLOAT_INFO getFloatInfo(FILE *);
  LONG_INFO getLongInfo(FILE *);
  DOUBLE_INFO getDoubleInfo(FILE *);
  CLASS_INFO getClassInfo(FILE *);
  STRING_INFO getStringInfo(FILE *);
  FIELD_REF_INFO getFieldRefInfo(FILE *);
  METHOD_REF_INFO getMethodRefInfo(FILE *);
  INTERFACE_METHOD_REF_INFO getInterfaceMethodRefInfo(FILE *);
  NAME_AND_TYPE_INFO getNameAndTypeInfo(FILE *);
  METHOD_HANDLE_INFO getMethodHandleInfo(FILE *);
  METHOD_TYPE_INFO getMethodTypeInfo(FILE *);
  INVOKE_DYNAMIC_INFO getInvokeDynamic_info(FILE *);
  string getUTF8(CP_info);
  ExceptionTable getExceptionTable(FILE *);
  Attribute_info getAttributeInfo(FILE *, vector<CP_info>);
  Code_attribute getCodeAttribute(FILE *, const vector<CP_info> &);
  LineNumberTable getLineNumberTable(FILE *);
  LineNumberTable_attribute getLineNumberTableAttribute(FILE *);
  LocalVariableTable getLocalVariableTable(FILE *);
  LocalVariableTable_attribute getLocalVariableAttribute(FILE *);
  Exceptions_attribute getExceptionsAttribute(FILE *);
  SourceFile_attribute getSourceFileAttribute(FILE *);
  Deprecated_attribute getDeprecatedAttribute();
  Class getClass(FILE *);
  InnerClasses_attribute getInnerClassesAttribute(FILE *);
  Synthetic_attribute getSyntheticAttribute();
  ConstantValue_attribute getConstantValueAttribute(FILE *);
};
