#include <iostream>

// Tipos de representação de dados da classe
typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

struct CLASS_INFO {
  u2 name_index;
};

struct FIELD_REF_INFO {
  u2 class_index;
  u2 nameAndType_index;
};

struct METHOD_REF_INFO {
  u2 class_index;
  u2 nameAndType_index;
};

struct INTERFACE_METHOD_REF_INFO {
  u2 class_index;
  u2 nameAndType_index;
};

struct STRING_INFO {
  u2 string_index;
};

struct INTEGER_INFO {
  u4 bytes;
};

struct FLOAT_INFO {
  u4 bytes;
};

struct LONG_INFO {
  u4 highBytes;
  u4 lowBytes;
};

struct DOUBLE_INFO {
  u4 highBytes;
  u4 lowBytes;
};

struct NAME_AND_TYPE_INFO {
  u2 name_index;
  u2 descriptor_index;
};

struct UTF8_INFO {
  u2 length;
  u1 *bytes;
};

struct METHOD_HANDLE_INFO {
  u1 referenceKind;
  u2 reference_index;
};

struct METHOD_TYPE_INFO {
  u2 descriptor_index;
};

struct INVOKE_DYNAMIC_INFO {
  u2 bootstrapMethodAttribute_index;
  u2 nameAndType_index;
};

struct ConstantValue_attribute {
  u2 constantValue_index;
};

struct ExceptionTable {
  u2 startPc;
  u2 endPc;
  u2 handlerPc;
  u2 catchType;
};

struct Deprecated_attribute {};

struct Attribute_info;

struct Code_attribute {
  u2 maxStack;
  u2 maxLocals;
  u4 codeLength;
  u1 *code;
  u2 exceptionTableLength;
  ExceptionTable *exceptionTable;
  u2 attributesCount;
  Attribute_info *attributes;
};

struct Exceptions_attribute {
  u2 numberOfExceptions;
  u2 *exceptionIndexTable;
};

struct Class {
  u2 innerClassInfo_index;
  u2 outerClassInfo_index;
  u2 innerName_index;
  u2 innerClassAccessFlags;
};

struct InnerClasses_attribute {
  u2 numberOfClasses;
  Class *classes;
};

struct Synthetic_attribute {};

struct SourceFile_attribute {
  u2 sourceFile_index;
};

struct LineNumberTable {
  u2 startPc;
  u2 lineNumber;
};

struct LineNumberTable_attribute {
  u2 lineNumberTableLength;
  LineNumberTable *lineNumberTable;
};

struct LocalVariableTable {
  u2 startPc;
  u2 length;
  u2 name_index;
  u2 descriptor_index;
  u2 index;
};

struct LocalVariableTable_attribute {
  u2 localVariableTableLength;
  LocalVariableTable *localVariableTable;
};

struct Attribute_info {
  u2 attributeName_index;
  u4 attributeLength;
  union {
    ConstantValue_attribute constantValue_info;
    Code_attribute code_info;
    Exceptions_attribute exceptions_info;
    InnerClasses_attribute innerClasses_info;
    Synthetic_attribute synthetic_info;
    SourceFile_attribute sourceFile_info;
    LineNumberTable_attribute lineNumberTable_info;
    LocalVariableTable_attribute localVariableTable_info;
    Deprecated_attribute deprecated_info;
  } info;
};

struct Field_info {
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributesCount;
  Attribute_info *attributes;
};

struct Method_info {
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributesCount;
  Attribute_info *attributes;
};

struct CP_info {
  u1 tag;
  union {
    CLASS_INFO class_info;
    FIELD_REF_INFO fieldref_info;
    METHOD_REF_INFO methodref_info;
    INTERFACE_METHOD_REF_INFO interfaceMethodref_info;
    STRING_INFO string_info;
    INTEGER_INFO integer_info;
    FLOAT_INFO float_info;
    LONG_INFO long_info;
    DOUBLE_INFO double_info;
    NAME_AND_TYPE_INFO nameAndType_info;
    UTF8_INFO utf8_info;
    METHOD_HANDLE_INFO methodHandle_info;
    METHOD_TYPE_INFO methodType_info;
    INVOKE_DYNAMIC_INFO invokeDynamic_info;
  } info;
};
