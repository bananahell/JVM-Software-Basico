#include <vector>

#include "globalStructures.h"

using namespace std;

class ReadClassByteCode {
 public:
  ReadClassByteCode();
  static u1 read1byte(FILE *);
  static u2 read2bytes(FILE *);
  static u4 read4bytes(FILE *);
  static UTF8_INFO getUTF8Info(FILE *);
  static INTEGER_INFO getIntegerInfo(FILE *);
  static FLOAT_INFO getFloatInfo(FILE *);
  static LONG_INFO getLongInfo(FILE *);
  static DOUBLE_INFO getDoubleInfo(FILE *);
  static CLASS_INFO getClassInfo(FILE *);
  static STRING_INFO getStringInfo(FILE *);
  static FIELD_REF_INFO getFieldRefInfo(FILE *);
  static METHOD_REF_INFO getMethodRefInfo(FILE *);
  static INTERFACE_METHOD_REF_INFO getInterfaceMethodRefInfo(FILE *);
  static NAME_AND_TYPE_INFO getNameAndTypeInfo(FILE *);
  static METHOD_HANDLE_INFO getMethodHandleInfo(FILE *);
  static METHOD_TYPE_INFO getMethodTypeInfo(FILE *);
  static INVOKE_DYNAMIC_INFO getInvokeDynamic_info(FILE *);
  static string getUTF8(CP_info);
  static ExceptionTable getExceptionTable(FILE *);
  static Attribute_info getAttributeInfo(FILE *, vector<CP_info>);
  static Code_attribute getCodeAttribute(FILE *, const vector<CP_info> &);
  static LineNumberTable getLineNumberTable(FILE *);
  static LineNumberTable_attribute getLineNumberTableAttribute(FILE *);
  static LocalVariableTable getLocalVariableTable(FILE *);
  static LocalVariableTable_attribute getLocalVariableAttribute(FILE *);
  static Exceptions_attribute getExceptionsAttribute(FILE *);
  static SourceFile_attribute getSourceFileAttribute(FILE *);
  static Deprecated_attribute getDeprecatedAttribute();
  static Class getClass(FILE *);
  static InnerClasses_attribute getInnerClassesAttribute(FILE *);
  static Synthetic_attribute getSyntheticAttribute();
  static ConstantValue_attribute getConstantValueAttribute(FILE *);
};
