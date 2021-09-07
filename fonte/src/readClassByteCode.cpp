#include "readClassByteCode.h"

#include <cstdio>
#include <cstdlib>

using namespace std;

ReadClassByteCode::ReadClassByteCode() {}

// Abre arquivo, le 1 byte do arquivo .class e retorna 1 byte
u1 ReadClassByteCode::read1byte(FILE *fp) {
  u1 byte = 0;
  fread(&byte, sizeof(u1), 1, fp);
  return byte;
}

// abre arquivo, le 2 bytes considerando littleendian, retorna 2 bytes
u2 ReadClassByteCode::read2bytes(FILE *fp) {
  u2 bytes = 0;
  for (int i = 0; i < 2; i++) {
    bytes += ReadClassByteCode::read1byte(fp) << (8 - 8 * i);
  }
  return bytes;
}

// abre arquivo, le 4 bytes considerando littleendian, retorna 4 bytes
u4 ReadClassByteCode::read4bytes(FILE *fp) {
  u4 bytes = 0;
  for (int i = 0; i < 4; i++) {
    bytes += ReadClassByteCode::read1byte(fp) << (24 - 8 * i);
  }
  return bytes;
}

/* define o lenght
 * malloc para alocar memória com o tamanho adequado
 * le byte a byte
 * retorna utf8_info
 */
UTF8_INFO ReadClassByteCode::getUTF8Info(FILE *fp) {
  UTF8_INFO utf8_info;
  utf8_info.length = ReadClassByteCode::read2bytes(fp);
  utf8_info.bytes = (u1 *)malloc(utf8_info.length * sizeof(u1));
  for (int i = 0; i < utf8_info.length; i++) {
    utf8_info.bytes[i] = ReadClassByteCode::read1byte(fp);
  }
  return utf8_info;
}

// define o campo bytes da struct tipo INTEGER_INFO.
INTEGER_INFO ReadClassByteCode::getIntegerInfo(FILE *fp) {
  INTEGER_INFO integer_info;
  integer_info.bytes = ReadClassByteCode::read4bytes(fp);
  return integer_info;
}

// define o campo bytes da struct float_info do tipo FLOAT_INFO
FLOAT_INFO ReadClassByteCode::getFloatInfo(FILE *fp) {
  FLOAT_INFO float_info;
  float_info.bytes = ReadClassByteCode::read4bytes(fp);
  return float_info;
}

/* le o arquivo fp (.class), define os campos highbytes e low bytes da struct
 * LONG_INFO
 */
LONG_INFO ReadClassByteCode::getLongInfo(FILE *fp) {
  LONG_INFO long_info;
  long_info.highBytes = ReadClassByteCode::read4bytes(fp);
  long_info.lowBytes = ReadClassByteCode::read4bytes(fp);
  return long_info;
}

// le o arquivo fp (.class), define os campos highbytes e low bytes da struct DOUBLE_INFO
DOUBLE_INFO ReadClassByteCode::getDoubleInfo(FILE *fp) {
  DOUBLE_INFO double_info;
  double_info.highBytes = ReadClassByteCode::read4bytes(fp);
  double_info.lowBytes = ReadClassByteCode::read4bytes(fp);
  return double_info;
}

// le o fp (.class), define name_index na struct do tipo CLASS_INFO
CLASS_INFO ReadClassByteCode::getClassInfo(FILE *fp) {
  CLASS_INFO class_info;
  class_info.name_index = ReadClassByteCode::read2bytes(fp);
  return class_info;
}

// le o fp (.class), define string_index na struct do tipo STRING_INFO
STRING_INFO ReadClassByteCode::getStringInfo(FILE *fp) {
  STRING_INFO string_info;
  string_info.string_index = ReadClassByteCode::read2bytes(fp);
  return string_info;
}

/* le o fp (.class), define class_index e nameAndType_index da
 * struct tipo FIELD_REF_INFO
 */
FIELD_REF_INFO ReadClassByteCode::getFieldRefInfo(FILE *fp) {
  FIELD_REF_INFO field_ref_info;
  field_ref_info.class_index = ReadClassByteCode::read2bytes(fp);
  field_ref_info.nameAndType_index = ReadClassByteCode::read2bytes(fp);
  return field_ref_info;
}

/* le o fp (.class), define class_index e nameAndType_index da
 * struct tipo METHOD_REF_INFO
 */
METHOD_REF_INFO ReadClassByteCode::getMethodRefInfo(FILE *fp) {
  METHOD_REF_INFO method_ref_info;
  method_ref_info.class_index = ReadClassByteCode::read2bytes(fp);
  method_ref_info.nameAndType_index = ReadClassByteCode::read2bytes(fp);
  return method_ref_info;
}

/* le o fp (.class), define class_index e nameAndType_index da struct tipo
 * INTERFACE_METHOD_REF_INFO
 */
INTERFACE_METHOD_REF_INFO ReadClassByteCode::getInterfaceMethodRefInfo(FILE *fp) {
  INTERFACE_METHOD_REF_INFO interface_method_ref_info;
  interface_method_ref_info.class_index = ReadClassByteCode::read2bytes(fp);
  interface_method_ref_info.nameAndType_index = ReadClassByteCode::read2bytes(fp);
  return interface_method_ref_info;
}

/* le o fp (.class), define name_index e descriptor_index da struct
 * tipo NAME_AND_TYPE_INFO
 */
NAME_AND_TYPE_INFO ReadClassByteCode::getNameAndTypeInfo(FILE *fp) {
  NAME_AND_TYPE_INFO name_and_type_info;
  name_and_type_info.name_index = ReadClassByteCode::read2bytes(fp);
  name_and_type_info.descriptor_index = ReadClassByteCode::read2bytes(fp);
  return name_and_type_info;
}

/* le o fp (.class), define reference_index e referenceKind da struct do tipo
 * METHOD_HANDLE_INFO
 */
METHOD_HANDLE_INFO ReadClassByteCode::getMethodHandleInfo(FILE *fp) {
  METHOD_HANDLE_INFO method_handle_info;
  method_handle_info.referenceKind = ReadClassByteCode::read1byte(fp);
  method_handle_info.reference_index = ReadClassByteCode::read2bytes(fp);
  return method_handle_info;
}

// le o fp (.class), define descriptor_index da struct tipo METHOD_TYPE_INFO
METHOD_TYPE_INFO ReadClassByteCode::getMethodTypeInfo(FILE *fp) {
  METHOD_TYPE_INFO method_type_info;
  method_type_info.descriptor_index = ReadClassByteCode::read2bytes(fp);
  return method_type_info;
}

/* le o fp (.class), define bootstrapMethodAttribute_index e
 * nameAndType_index da struct tipo INVOKE_DYNAMIC_INFO
 */
INVOKE_DYNAMIC_INFO ReadClassByteCode::getInvokeDynamic_info(FILE *fp) {
  INVOKE_DYNAMIC_INFO invoke_dynamic_info;
  invoke_dynamic_info.bootstrapMethodAttribute_index = ReadClassByteCode::read2bytes(fp);
  invoke_dynamic_info.nameAndType_index = ReadClassByteCode::read2bytes(fp);
  return invoke_dynamic_info;
}

/* verificar lenght de cpInfo, para cada byte realiza um "push_back" na
 * string do byte lido
 */
string ReadClassByteCode::getUTF8(CP_info cpInfo) {
  string utf8;
  for (int i = 0; i < cpInfo.info.utf8_info.length; i++) {
    utf8.push_back(cpInfo.info.utf8_info.bytes[i]);
  }
  return utf8;
}

/*
 * acessa fp (.class) e define os campos startPC, endPC, handlerPC e catchType da
 * struct EceptionTable
 */
ExceptionTable ReadClassByteCode::getExceptionTable(FILE *fp) {
  ExceptionTable exception_table;
  exception_table.startPc = ReadClassByteCode::read2bytes(fp);
  exception_table.endPc = ReadClassByteCode::read2bytes(fp);
  exception_table.handlerPc = ReadClassByteCode::read2bytes(fp);
  exception_table.catchType = ReadClassByteCode::read2bytes(fp);
  return exception_table;
}

/*
 * le o arquivo fp (.class) define o campo attributeName_index, attributeLength.
 * utiliza o método getUTF8 para pegar a string name para o constantPool com o
 * index name_index - 1.
 */
Attribute_info ReadClassByteCode::getAttributeInfo(FILE *fp, vector<CP_info> constantPool) {
  Attribute_info attribute_info;
  attribute_info.attributeName_index = ReadClassByteCode::read2bytes(fp);
  attribute_info.attributeLength = ReadClassByteCode::read4bytes(fp);
  string name = ReadClassByteCode::getUTF8(constantPool[attribute_info.attributeName_index - 1]);
  if (name == "Code") {
    attribute_info.info.code_info = ReadClassByteCode::getCodeAttribute(fp, constantPool);

  } else if (name == "LineNumberTable") {
    attribute_info.info.lineNumberTable_info = ReadClassByteCode::getLineNumberTableAttribute(fp);

  } else if (name == "LocalVariableTable") {
    attribute_info.info.localVariableTable_info = ReadClassByteCode::getLocalVariableAttribute(fp);

  } else if (name == "Exceptions") {
    attribute_info.info.exceptions_info = ReadClassByteCode::getExceptionsAttribute(fp);

  } else if (name == "SourceFile") {
    attribute_info.info.sourceFile_info = ReadClassByteCode::getSourceFileAttribute(fp);

  } else if (name == "Deprecated") {
    attribute_info.info.deprecated_info = ReadClassByteCode::getDeprecatedAttribute();

  } else if (name == "InnerClasses") {
    attribute_info.info.innerClasses_info = ReadClassByteCode::getInnerClassesAttribute(fp);

  } else if (name == "Synthetic") {
    attribute_info.info.synthetic_info = ReadClassByteCode::getSyntheticAttribute();

  } else if (name == "ConstantValue") {
    attribute_info.info.constantValue_info = ReadClassByteCode::getConstantValueAttribute(fp);

  } else {
    cout << "The code has an attribute not yet implemented." << endl;
  }
  return attribute_info;
}

/*
 * le o arquivo fp (.class) define os campos maxStack, maxLocals, codeLength.
 * utiliza o valor de codeLength para saber o número de bytes e aloca memória de acordo com esse
 * pega os valores de ExceptionTableLength e attributesCount, utiliza para ExceptionTable
 */
Code_attribute ReadClassByteCode::getCodeAttribute(FILE *fp, const vector<CP_info> &cp) {
  Code_attribute code_attribute;
  code_attribute.maxStack = ReadClassByteCode::read2bytes(fp);
  code_attribute.maxLocals = ReadClassByteCode::read2bytes(fp);

  code_attribute.codeLength = ReadClassByteCode::read4bytes(fp);
  code_attribute.code = (u1 *)malloc(code_attribute.codeLength * sizeof(u1));
  for (int i = 0; i < (int)code_attribute.codeLength; i++) {
    code_attribute.code[i] = ReadClassByteCode::read1byte(fp);
  }

  code_attribute.exceptionTableLength = ReadClassByteCode::read2bytes(fp);
  int exceptionTableLength = code_attribute.exceptionTableLength;
  code_attribute.exceptionTable = static_cast<ExceptionTable *>(malloc(exceptionTableLength * sizeof(ExceptionTable)));
  for (int i = 0; i < exceptionTableLength; i++) {
    code_attribute.exceptionTable[i] = ReadClassByteCode::getExceptionTable(fp);
  }

  code_attribute.attributesCount = ReadClassByteCode::read2bytes(fp);
  int attributesCount = code_attribute.attributesCount;
  code_attribute.attributes = static_cast<Attribute_info *>(malloc(attributesCount * sizeof(Attribute_info)));
  for (int i = 0; i < attributesCount; i++) {
    code_attribute.attributes[i] = ReadClassByteCode::getAttributeInfo(fp, cp);
  }

  return code_attribute;
}

// le fp (.class) e define os campos startPC e lineNumber da struct tipo LineNumberTable
LineNumberTable ReadClassByteCode::getLineNumberTable(FILE *fp) {
  LineNumberTable lineNumberTable;
  lineNumberTable.startPc = ReadClassByteCode::read2bytes(fp);
  lineNumberTable.lineNumber = ReadClassByteCode::read2bytes(fp);
  return lineNumberTable;
}

/* le o arquivo fp (.class) e define lineNumberTableLength, utiliza esse valor para saber o número de
 *lineNumberTable. usa malloc para alocar memoria adequadamente
 */
LineNumberTable_attribute ReadClassByteCode::getLineNumberTableAttribute(FILE *fp) {
  LineNumberTable_attribute line_number_table_attribute;
  line_number_table_attribute.lineNumberTableLength = ReadClassByteCode::read2bytes(fp);
  int lineNumberTableLength = line_number_table_attribute.lineNumberTableLength;
  line_number_table_attribute.lineNumberTable =
      static_cast<LineNumberTable *>(malloc(lineNumberTableLength * sizeof(LineNumberTable)));
  for (int i = 0; i < lineNumberTableLength; i++) {
    line_number_table_attribute.lineNumberTable[i] = ReadClassByteCode::getLineNumberTable(fp);
  }
  return line_number_table_attribute;
}

/*
 * Define os campos startPc, length, name_index e descriptor_index e index da struct tipo
 * LocalVariableTable
 */
LocalVariableTable ReadClassByteCode::getLocalVariableTable(FILE *fp) {
  LocalVariableTable localVariableTable;
  localVariableTable.startPc = ReadClassByteCode::read2bytes(fp);
  localVariableTable.length = ReadClassByteCode::read2bytes(fp);
  localVariableTable.name_index = ReadClassByteCode::read2bytes(fp);
  localVariableTable.descriptor_index = ReadClassByteCode::read2bytes(fp);
  localVariableTable.index = ReadClassByteCode::read2bytes(fp);
  return localVariableTable;
}

/*
 * Define localVariableTableLength
 * Usa o malloc para alocar memória adequadamente
 */
LocalVariableTable_attribute ReadClassByteCode::getLocalVariableAttribute(FILE *fp) {
  LocalVariableTable_attribute local_variable_table_attribute;
  local_variable_table_attribute.localVariableTableLength = ReadClassByteCode::read2bytes(fp);
  int localVarTableLength = local_variable_table_attribute.localVariableTableLength;
  local_variable_table_attribute.localVariableTable =
      static_cast<LocalVariableTable *>(malloc(localVarTableLength * sizeof(LocalVariableTable)));
  for (int i = 0; i < localVarTableLength; i++) {
    local_variable_table_attribute.localVariableTable[i] = ReadClassByteCode::getLocalVariableTable(fp);
  }
  return local_variable_table_attribute;
}

/*
 * Define  numberOfExceptions (número de entradas na
 * tabela). Utiliza o malloc para alocar memória adequadamente
 */
Exceptions_attribute ReadClassByteCode::getExceptionsAttribute(FILE *fp) {
  Exceptions_attribute exceptions_attribute;
  exceptions_attribute.numberOfExceptions = ReadClassByteCode::read2bytes(fp);
  exceptions_attribute.exceptionIndexTable = (u2 *)malloc(exceptions_attribute.numberOfExceptions * sizeof(u2));
  for (int i = 0; i < exceptions_attribute.numberOfExceptions; i++) {
    exceptions_attribute.exceptionIndexTable[i] = ReadClassByteCode::read2bytes(fp);
  }
  return exceptions_attribute;
}

/*
 * Define o campo sourceFile_index da struct tipo SourceFile_attribute.
 */
SourceFile_attribute ReadClassByteCode::getSourceFileAttribute(FILE *fp) {
  SourceFile_attribute source_file_attribute;
  source_file_attribute.sourceFile_index = ReadClassByteCode::read2bytes(fp);
  return source_file_attribute;
}

Deprecated_attribute ReadClassByteCode::getDeprecatedAttribute() {
  Deprecated_attribute deprecated_attribute;
  return deprecated_attribute;
}

/*
 *Define os campos innerClassInfo_index, outerClassInfo_index, innerName_index e
 *innerClassAccessFlags da struct tipo Class.
 */
Class ReadClassByteCode::getClass(FILE *fp) {
  Class class_object;
  class_object.innerClassInfo_index = ReadClassByteCode::read2bytes(fp);
  class_object.outerClassInfo_index = ReadClassByteCode::read2bytes(fp);
  class_object.innerName_index = ReadClassByteCode::read2bytes(fp);
  class_object.innerClassAccessFlags = ReadClassByteCode::read2bytes(fp);
  return class_object;
}

/*
 *Define nnumber_of_classes, utiliza esse valor para saber o número de class's(struct
 *class). para cada class na tabela utiliza o método getClass para pegar a class e define o campo
 */
InnerClasses_attribute ReadClassByteCode::getInnerClassesAttribute(FILE *fp) {
  InnerClasses_attribute inner_classes_attribute;
  inner_classes_attribute.numberOfClasses = ReadClassByteCode::read2bytes(fp);
  int numOfClasses = inner_classes_attribute.numberOfClasses;
  inner_classes_attribute.classes = static_cast<Class *>(malloc(numOfClasses * sizeof(Class)));
  for (int i = 0; i < numOfClasses; i++) {
    inner_classes_attribute.classes[i] = ReadClassByteCode::getClass(fp);
  }
  return inner_classes_attribute;
}

Synthetic_attribute ReadClassByteCode::getSyntheticAttribute() {
  Synthetic_attribute synthetic_attribute;
  return synthetic_attribute;
}

/*
 * Define o campo constantValue_index da struct tipo ConstantValue_attribute.
 */
ConstantValue_attribute ReadClassByteCode::getConstantValueAttribute(FILE *fp) {
  ConstantValue_attribute constant_value_attribute;
  constant_value_attribute.constantValue_index = ReadClassByteCode::read2bytes(fp);
  return constant_value_attribute;
}
