#include "classFile.h"

ClassFile::ClassFile() {}

// Construtor
ClassFile::ClassFile(FILE* fp) {
  this->magicNumber = ReadClassByteCode::read4bytes(fp);
  this->minorVersion = ReadClassByteCode::read2bytes(fp);
  this->majorVersion = ReadClassByteCode::read2bytes(fp);
  this->constantPoolSize = ReadClassByteCode::read2bytes(fp);
  this->setConstantPool(fp);
  this->accessFlags = ReadClassByteCode::read2bytes(fp);
  this->thisClass = ReadClassByteCode::read2bytes(fp);
  this->superClass = ReadClassByteCode::read2bytes(fp);
  this->interfacesCount = ReadClassByteCode::read2bytes(fp);
  this->setInterfaces(fp);
  this->fieldsCount = ReadClassByteCode::read2bytes(fp);
  this->setFields(fp);
  this->methodsCount = ReadClassByteCode::read2bytes(fp);
  this->setMethods(fp);
  this->attributesCount = ReadClassByteCode::read2bytes(fp);
  this->setAttributes(fp);
}

/* Seta a constantPool com estrutura CP_info usando o arquivo fp (.class)
 * Utiliza constantPoolSize para saber o número de entradas da
 * tabela e o método read1byte lê a tag e utiliza um método get
 * para a informacao apropriada
 */
void ClassFile::setConstantPool(FILE* fp) {
  int constantPoolSize = this->constantPoolSize - 1;

  for (int i = 0; i < constantPoolSize; i++) {
    u1 tag = ReadClassByteCode::read1byte(fp);
    CP_info cpInfo;
    cpInfo.tag = tag;
    switch (tag) {
      // Class
      case 7:
        cpInfo.info.class_info = ReadClassByteCode::getClassInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // Fieldref
      case 9:
        cpInfo.info.fieldref_info = ReadClassByteCode::getFieldRefInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // Methodref
      case 10:
        cpInfo.info.methodref_info = ReadClassByteCode::getMethodRefInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // InterfaceMethodref
      case 11:
        cpInfo.info.interfaceMethodref_info = ReadClassByteCode::getInterfaceMethodRefInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // String
      case 8:
        cpInfo.info.string_info = ReadClassByteCode::getStringInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // Integer
      case 3:
        cpInfo.info.integer_info = ReadClassByteCode::getIntegerInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // Float
      case 4:
        cpInfo.info.float_info = ReadClassByteCode::getFloatInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // Long
      case 5:
        cpInfo.info.long_info = ReadClassByteCode::getLongInfo(fp);
        this->constantPool.push_back(cpInfo);
        CP_info cpInfo1;
        cpInfo1.tag = 0;
        this->constantPool.push_back(cpInfo1);
        i++;
        break;

      // Double
      case 6:
        cpInfo.info.double_info = ReadClassByteCode::getDoubleInfo(fp);
        this->constantPool.push_back(cpInfo);
        CP_info cpInfo2;
        cpInfo2.tag = 0;
        this->constantPool.push_back(cpInfo2);
        i++;
        break;

      // NameAndType
      case 12:
        cpInfo.info.nameAndType_info = ReadClassByteCode::getNameAndTypeInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // UTF8
      case 1:
        cpInfo.info.utf8_info = ReadClassByteCode::getUTF8Info(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // MethodHandle
      case 15:
        cpInfo.info.methodHandle_info = ReadClassByteCode::getMethodHandleInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // MethodType
      case 16:
        cpInfo.info.methodType_info = ReadClassByteCode::getMethodTypeInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // InvokeDynamic
      case 18:
        cpInfo.info.invokeDynamic_info = ReadClassByteCode::getInvokeDynamic_info(fp);
        this->constantPool.push_back(cpInfo);
        break;
    }
  }
}

/* Define a tabela de Interfaces usando o arquivo fp (.class)
 * interfacesCount contem o numero de entradas da tabela (total de entradas)
 */
void ClassFile::setInterfaces(FILE* fp) {
  for (int i = 0; i < this->interfacesCount; i++) {
    u2 interface = ReadClassByteCode::read2bytes(fp);
    this->interfaces.push_back(interface);
  }
}

/*
 * Define a tabela Fields com estruturas fieldInfo usando o arquivo fp (.class).
 * fieldsCount para saber o número de entradas da tabela (total de entradas)
 * malloc aloca memoria para o tamanho adequado
 */
void ClassFile::setFields(FILE* fp) {
  for (int i = 0; i < this->fieldsCount; i++) {
    Field_info fieldInfo;
    fieldInfo.access_flags = ReadClassByteCode::read2bytes(fp);
    fieldInfo.name_index = ReadClassByteCode::read2bytes(fp);
    fieldInfo.descriptor_index = ReadClassByteCode::read2bytes(fp);
    fieldInfo.attributesCount = ReadClassByteCode::read2bytes(fp);
    int contador = fieldInfo.attributesCount;
    fieldInfo.attributes = static_cast<Attribute_info*>(malloc(contador * sizeof(Attribute_info)));
    for (int j = 0; j < contador; j++) {
      fieldInfo.attributes[j] = ReadClassByteCode::getAttributeInfo(fp, constantPool);
    }
    this->fields.push_back(fieldInfo);
  }
}

/* Define Methods com a estrutura methodInfo usando o arquivo fp (.class)
 * methodsCount define o numero de entradas da tabela (total de entradas)
 * malloc aloca memoria para o tamanho adequado
 */
void ClassFile::setMethods(FILE* fp) {
  for (int i = 0; i < this->methodsCount; i++) {
    Method_info methodInfo;
    methodInfo.access_flags = ReadClassByteCode::read2bytes(fp);
    methodInfo.name_index = ReadClassByteCode::read2bytes(fp);
    methodInfo.descriptor_index = ReadClassByteCode::read2bytes(fp);
    methodInfo.attributesCount = ReadClassByteCode::read2bytes(fp);
    int counter = methodInfo.attributesCount;
    methodInfo.attributes = static_cast<Attribute_info*>(malloc(counter * sizeof(Attribute_info)));
    for (int j = 0; j < counter; j++) {
      methodInfo.attributes[j] = ReadClassByteCode::getAttributeInfo(fp, constantPool);
    }
    this->methods.push_back(methodInfo);
  }
}

/*
 * Define Attribute_info usando o arquivo fp (.class)
 * attributesCount define o numero de entradas da tabela (total de entradas)
 */
void ClassFile::setAttributes(FILE* fp) {
  for (int i = 0; i < this->attributesCount; i++) {
    this->attributes.push_back(ReadClassByteCode::getAttributeInfo(fp, constantPool));
  }
}

u4 ClassFile::getMagicNumber() { return this->magicNumber; }
u2 ClassFile::getMinorVersion() { return this->minorVersion; }
u2 ClassFile::getMajorVersion() { return this->majorVersion; }
u2 ClassFile::getConstantPoolSize() { return this->constantPoolSize; }
vector<CP_info> ClassFile::getConstantPool() { return this->constantPool; }
u2 ClassFile::getAccessFlags() { return this->accessFlags; }
u2 ClassFile::getThisClass() { return this->thisClass; }
u2 ClassFile::getSuperClass() { return this->superClass; }
u2 ClassFile::getInterfacesCount() { return this->interfacesCount; }
vector<u2> ClassFile::getInterfaces() { return this->interfaces; }
u2 ClassFile::getFieldsCount() { return this->fieldsCount; }
vector<Field_info> ClassFile::getFields() { return this->fields; }
u2 ClassFile::getMethodsCount() { return this->methodsCount; }
vector<Method_info> ClassFile::getMethods() { return this->methods; }
u2 ClassFile::getAttributesCount() { return this->attributesCount; }
vector<Attribute_info> ClassFile::getAttributes() { return this->attributes; }
