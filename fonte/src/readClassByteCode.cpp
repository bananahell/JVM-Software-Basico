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
    bytes += read1byte(fp) << (8 - 8 * i);
  }
  return bytes;
}

// abre arquivo, le 4 bytes considerando littleendian, retorna 4 bytes
u4 ReadClassByteCode::read4bytes(FILE *fp) {
  u4 bytes = 0;
  for (int i = 0; i < 4; i++) {
    bytes += read1byte(fp) << (24 - 8 * i);
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
  utf8_info.length = read2bytes(fp);
  int contador = utf8_info.length;
  utf8_info.bytes = (u1 *)malloc(contador * sizeof(u1));
  for (int i = 0; i < contador; i++) {
    utf8_info.bytes[i] = read1byte(fp);
  }
  return utf8_info;
}

// define o campo bytes da struct tipo INTEGER_INFO.
INTEGER_INFO ReadClassByteCode::getIntegerInfo(FILE *fp) {
  INTEGER_INFO integer_info;
  integer_info.bytes = read4bytes(fp);
  return integer_info;
}

// define o campo bytes da struct float_info do tipo FLOAT_INFO
FLOAT_INFO ReadClassByteCode::getFloatInfo(FILE *fp) {
  FLOAT_INFO float_info;
  float_info.bytes = read4bytes(fp);
  return float_info;
}

/* le o arquivo fp (.class), define os campos highbytes e low bytes da struct
 * LONG_INFO
 */
LONG_INFO ReadClassByteCode::getLongInfo(FILE *fp) {
  LONG_INFO long_info;
  long_info.highBytes = read4bytes(fp);
  long_info.lowBytes = read4bytes(fp);
  return long_info;
}

// le o arquivo fp (.class), define os campos highbytes e low bytes da struct DOUBLE_INFO
DOUBLE_INFO ReadClassByteCode::getDoubleInfo(FILE *fp) {
  DOUBLE_INFO double_info;
  double_info.highBytes = read4bytes(fp);
  double_info.lowBytes = read4bytes(fp);
  return double_info;
}

// le o fp (.class), define name_index na struct do tipo CLASS_INFO
CLASS_INFO ReadClassByteCode::getClassInfo(FILE *fp) {
  CLASS_INFO class_info;
  class_info.name_index = read2bytes(fp);
  return class_info;
}

// le o fp (.class), define string_index na struct do tipo STRING_INFO
STRING_INFO ReadClassByteCode::getStringInfo(FILE *fp) {
  STRING_INFO string_info;
  string_info.string_index = read2bytes(fp);
  return string_info;
}

/* le o fp (.class), define class_index e nameAndType_index da
 * struct tipo FIELD_REF_INFO
 */
FIELD_REF_INFO ReadClassByteCode::getFieldRefInfo(FILE *fp) {
  FIELD_REF_INFO field_ref_info;
  field_ref_info.class_index = read2bytes(fp);
  field_ref_info.nameAndType_index = read2bytes(fp);
  return field_ref_info;
}

/* le o fp (.class), define class_index e nameAndType_index da
 * struct tipo METHOD_REF_INFO
 */
METHOD_REF_INFO ReadClassByteCode::getMethodRefInfo(FILE *fp) {
  METHOD_REF_INFO method_ref_info;
  method_ref_info.class_index = read2bytes(fp);
  method_ref_info.nameAndType_index = read2bytes(fp);
  return method_ref_info;
}

/* le o fp (.class), define class_index e nameAndType_index da struct tipo
 * INTERFACE_METHOD_REF_INFO
 */
INTERFACE_METHOD_REF_INFO ReadClassByteCode::getInterfaceMethodRefInfo(FILE *fp) {
  INTERFACE_METHOD_REF_INFO interface_method_ref_info;
  interface_method_ref_info.class_index = read2bytes(fp);
  interface_method_ref_info.nameAndType_index = read2bytes(fp);
  return interface_method_ref_info;
}

/* le o fp (.class), define name_index e descriptor_index da struct
 * tipo NAME_AND_TYPE_INFO
 */
NAME_AND_TYPE_INFO ReadClassByteCode::getNameAndTypeInfo(FILE *fp) {
  NAME_AND_TYPE_INFO name_and_type_info;
  name_and_type_info.name_index = read2bytes(fp);
  name_and_type_info.descriptor_index = read2bytes(fp);
  return name_and_type_info;
}

/* le o fp (.class), define reference_index e referenceKind da struct do tipo
 * METHOD_HANDLE_INFO
 */
METHOD_HANDLE_INFO ReadClassByteCode::getMethodHandleInfo(FILE *fp) {
  METHOD_HANDLE_INFO method_handle_info;
  method_handle_info.referenceKind = read1byte(fp);
  method_handle_info.reference_index = read2bytes(fp);
  return method_handle_info;
}

// le o fp (.class), define descriptor_index da struct tipo METHOD_TYPE_INFO
METHOD_TYPE_INFO ReadClassByteCode::getMethodTypeInfo(FILE *fp) {
  METHOD_TYPE_INFO method_type_info;
  method_type_info.descriptor_index = read2bytes(fp);
  return method_type_info;
}

/* le o fp (.class), define bootstrapMethodAttribute_index e
 * nameAndType_index da struct tipo INVOKE_DYNAMIC_INFO
 */
INVOKE_DYNAMIC_INFO ReadClassByteCode::getInvokeDynamic_info(FILE *fp) {
  INVOKE_DYNAMIC_INFO invoke_dynamic_info;
  invoke_dynamic_info.bootstrapMethodAttribute_index = read2bytes(fp);
  invoke_dynamic_info.nameAndType_index = read2bytes(fp);
  return invoke_dynamic_info;
}

/* verificar lenght de cpInfo, para cada byte realiza um "push_back" na
 * string do byte lido
 */
string ReadClassByteCode::getUTF8(CP_info cpInfo) {
  string utf8;
  int contador = cpInfo.info.utf8_info.length;
  for (int i = 0; i < contador; i++) {
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
  exception_table.startPc = read2bytes(fp);
  exception_table.endPc = read2bytes(fp);
  exception_table.handlerPc = read2bytes(fp);
  exception_table.catchType = read2bytes(fp);
  return exception_table;
}

/*
 * le o arquivo fp (.class) define o campo attributeName_index, attributeLength.
 * utiliza o método getUTF8 para pegar a string name para o constantPool com o
 * index name_index - 1.
 */
Attribute_info ReadClassByteCode::getAttributeInfo(FILE *fp, vector<CP_info> constantPool) {
  Attribute_info attribute_info;
  attribute_info.attributeName_index = ReadClassByteCode().read2bytes(fp);
  attribute_info.attributeLength = ReadClassByteCode().read4bytes(fp);
  string name = getUTF8(constantPool[attribute_info.attributeName_index - 1]);
  if (name == "Code") {
    attribute_info.info.code_info = ReadClassByteCode().getCodeAttribute(fp, constantPool);

  } else if (name == "LineNumberTable") {
    attribute_info.info.lineNumberTable_info = ReadClassByteCode().getLineNumberTableAttribute(fp);

  } else if (name == "LocalVariableTable") {
    attribute_info.info.localVariableTable_info = ReadClassByteCode().getLocalVariableAttribute(fp);

  } else if (name == "Exceptions") {
    attribute_info.info.exceptions_info = ReadClassByteCode().getExceptionsAttribute(fp);

  } else if (name == "SourceFile") {
    attribute_info.info.sourceFile_info = ReadClassByteCode().getSourceFileAttribute(fp);

  } else if (name == "Deprecated") {
    attribute_info.info.deprecated_info = ReadClassByteCode().getDeprecatedAttribute();

  } else if (name == "InnerClasses") {
    attribute_info.info.innerClasses_info = ReadClassByteCode().getInnerClassesAttribute(fp);

  } else if (name == "Synthetic") {
    attribute_info.info.synthetic_info = ReadClassByteCode().getSyntheticAttribute();

  } else if (name == "ConstantValue") {
    attribute_info.info.constantValue_info = ReadClassByteCode().getConstantValueAttribute(fp);

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
  code_attribute.maxStack = read2bytes(fp);
  code_attribute.maxLocals = read2bytes(fp);

  code_attribute.codeLength = read4bytes(fp);
  int contador = code_attribute.codeLength;
  code_attribute.code = (u1 *)malloc(contador * sizeof(u1));
  for (int i = 0; i < contador; i++) {
    code_attribute.code[i] = read1byte(fp);
  }

  code_attribute.exceptionTableLength = read2bytes(fp);
  contador = code_attribute.exceptionTableLength;
  code_attribute.exceptionTable = static_cast<ExceptionTable *>(malloc(contador * sizeof(ExceptionTable)));
  for (int i = 0; i < contador; i++) {
    code_attribute.exceptionTable[i] = getExceptionTable(fp);
  }

  code_attribute.attributesCount = read2bytes(fp);
  contador = code_attribute.attributesCount;
  code_attribute.attributes = static_cast<Attribute_info *>(malloc(contador * sizeof(Attribute_info)));
  for (int i = 0; i < contador; i++) {
    code_attribute.attributes[i] = getAttributeInfo(fp, cp);
  }

  return code_attribute;
}

// le fp (.class) e define os campos startPC e lineNumber da struct tipo LineNumberTable
LineNumberTable ReadClassByteCode::getLineNumberTable(FILE *fp) {
  LineNumberTable lineNumberTable;
  lineNumberTable.startPc = read2bytes(fp);
  lineNumberTable.lineNumber = read2bytes(fp);
  return lineNumberTable;
}

/**
Lê o arquivo .class com o método read2bytes para pegar e setar
lineNumberTableLength, utiliza esse valor para saber o número de
lineNumberTable. Utiliza o malloc para alocar memória com o tamanho adequado,
para cada lineNumberTable utiliza o método getLineNumberTable que retorna um
LineNumberTable e o seta no campo lineNumberTable.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct LineNumberTable_attribute.
*/
LineNumberTable_attribute ReadClassByteCode::getLineNumberTableAttribute(FILE *fp) {
  LineNumberTable_attribute line_number_table_attribute;
  line_number_table_attribute.lineNumberTableLength = read2bytes(fp);
  int contador = line_number_table_attribute.lineNumberTableLength;
  line_number_table_attribute.lineNumberTable =
      static_cast<LineNumberTable *>(malloc(contador * sizeof(LineNumberTable)));
  for (int i = 0; i < contador; i++) {
    line_number_table_attribute.lineNumberTable[i] = getLineNumberTable(fp);
  }
  return line_number_table_attribute;
}

/**
Lê o arquivo .class com o método read2bytes para pegar e setar os campos
startPc, length, name_index e descriptor_index e index da struct tipo
LocalVariableTable.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct LocalVariableTable.
*/
LocalVariableTable ReadClassByteCode::getLocalVariableTable(FILE *fp) {
  LocalVariableTable localVariableTable;
  localVariableTable.startPc = read2bytes(fp);
  localVariableTable.length = read2bytes(fp);
  localVariableTable.name_index = read2bytes(fp);
  localVariableTable.descriptor_index = read2bytes(fp);
  localVariableTable.index = read2bytes(fp);
  return localVariableTable;
}

/**
Lê o arquivo .class com o método read2bytes para pegar e setar
localVariableTableLength, utiliza esse valor para saber o número de
lineNumberTable. Utiliza o malloc para alocar memória com o tamanho adequado,
para cada localVariableTable utiliza o método getLocalVariableTable que
retorna um LocalVariableTable e o seta no campo localVariableTable.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct LocalVariableTable_attribute.
*/
LocalVariableTable_attribute ReadClassByteCode::getLocalVariableAttribute(FILE *fp) {
  LocalVariableTable_attribute local_variable_table_attribute;
  local_variable_table_attribute.localVariableTableLength = read2bytes(fp);
  int contador = local_variable_table_attribute.localVariableTableLength;
  local_variable_table_attribute.localVariableTable =
      static_cast<LocalVariableTable *>(malloc(contador * sizeof(LocalVariableTable)));
  for (int i = 0; i < contador; i++) {
    local_variable_table_attribute.localVariableTable[i] = getLocalVariableTable(fp);
  }
  return local_variable_table_attribute;
}

/**
Lê o arquivo .class com o método read2bytes para pegar e setar
numberOfExceptions, utiliza esse valor para saber o número de entradas na
tabela. Utiliza o malloc para alocar memória com o tamanho adequado, para cada
entrada na tabela utiliza o método read2bytes para ler o arquivo e seta o campo.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct Exceptions_attribute.
*/
Exceptions_attribute ReadClassByteCode::getExceptionsAttribute(FILE *fp) {
  Exceptions_attribute exceptions_attribute;
  exceptions_attribute.numberOfExceptions = read2bytes(fp);
  int contador = exceptions_attribute.numberOfExceptions;
  exceptions_attribute.exceptionIndexTable = (u2 *)malloc(contador * sizeof(u2));
  for (int i = 0; i < contador; i++) {
    exceptions_attribute.exceptionIndexTable[i] = read2bytes(fp);
  }
  return exceptions_attribute;
}

/**
Lê o arquivo .class com o método read2bytes para pegar e setar o campo
sourceFile_index da struct tipo SourceFile_attribute.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct SourceFile_attribute.
*/
SourceFile_attribute ReadClassByteCode::getSourceFileAttribute(FILE *fp) {
  SourceFile_attribute source_file_attribute;
  source_file_attribute.sourceFile_index = read2bytes(fp);
  return source_file_attribute;
}

/**
Cria uma struct do tipo Deprecated_attribute(vazia) e retorna ela, não foi
implementado.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct Deprecated_attribute.
*/
Deprecated_attribute ReadClassByteCode::getDeprecatedAttribute() {
  Deprecated_attribute deprecated_attribute;
  return deprecated_attribute;
}

/**
Lê o arquivo .class com o método read2bytes para pegar e setar os campos
innerClassInfo_index, outerClassInfo_index, innerName_index e
innerClassAccessFlags da struct tipo Class.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct Class.
*/
Class ReadClassByteCode::getClass(FILE *fp) {
  Class class_object;
  class_object.innerClassInfo_index = read2bytes(fp);
  class_object.outerClassInfo_index = read2bytes(fp);
  class_object.innerName_index = read2bytes(fp);
  class_object.innerClassAccessFlags = read2bytes(fp);
  return class_object;
}

/**
Lê o arquivo .class com o método read2bytes para pegar e setar
nnumber_of_classes, utiliza esse valor para saber o número de class's(struct
class). Utiliza o malloc para alocar memória com o tamanho adequado, para cada
class na tabela utiliza o método getClass para pegar a class e seta o campo.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct InnerClasses_attribute.
*/
InnerClasses_attribute ReadClassByteCode::getInnerClassesAttribute(FILE *fp) {
  InnerClasses_attribute inner_classes_attribute;
  inner_classes_attribute.numberOfClasses = read2bytes(fp);
  int contador = inner_classes_attribute.numberOfClasses;
  inner_classes_attribute.classes = static_cast<Class *>(malloc(contador * sizeof(Class)));
  for (int i = 0; i < contador; i++) {
    inner_classes_attribute.classes[i] = getClass(fp);
  }
  return inner_classes_attribute;
}

/**
Cria uma struct do tipo Synthetic_attribute(vazia) e retorna ela, não foi
implementado.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct Synthetic_attribute.
*/
Synthetic_attribute ReadClassByteCode::getSyntheticAttribute() {
  Synthetic_attribute synthetic_attribute;
  return synthetic_attribute;
}

/**
Lê o arquivo .class com o método read2bytes para pegar e setar o campo
constantValue_index da struct tipo ConstantValue_attribute.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct ConstantValue_attribute.
*/
ConstantValue_attribute ReadClassByteCode::getConstantValueAttribute(FILE *fp) {
  ConstantValue_attribute constant_value_attribute;
  constant_value_attribute.constantValue_index = read2bytes(fp);
  return constant_value_attribute;
}