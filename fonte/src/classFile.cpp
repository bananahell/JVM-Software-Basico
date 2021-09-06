#include "classFile.h"

ClassFile::ClassFile() {}

// Construtor
ClassFile::ClassFile(FILE* fp) {
  this->setMagicNumber(fp);
  this->setMinorVersion(fp);
  this->setMajorVersion(fp);
  this->setConstantPoolSize(fp);
  this->setConstantPool(fp);
  this->setAccessFlags(fp);
  this->setThisClass(fp);
  this->setSuperClass(fp);
  this->setInterfacesCount(fp);
  this->setInterfaces(fp);
  this->setFieldsCount(fp);
  this->setFields(fp);
  this->setMethodsCount(fp);
  this->setMethods(fp);
  this->setAttributesCount(fp);
  this->setAttributes(fp);
}

// Inicia o valor de MagicNumber usando o arquivo fp (.class)
void ClassFile::setMagicNumber(FILE* fp) {
  ReadClassByteCode magicNumber;
  this->magicNumber = magicNumber.read4bytes(fp);
}

// Inicia o valor de MinorVersionno usando o arquivo fp (.class)
void ClassFile::setMinorVersion(FILE* fp) {
  ReadClassByteCode minorVersion;
  this->minorVersion = minorVersion.read2bytes(fp);
}

// Inicia o valor de MajorVersionno usando o arquivo fp (.class)
void ClassFile::setMajorVersion(FILE* fp) {
  ReadClassByteCode majorVersion;
  this->majorVersion = majorVersion.read2bytes(fp);
}

// Inicia o valor de constantPoolSize usando o arquivo fp (.class)
void ClassFile::setConstantPoolSize(FILE* fp) {
  ReadClassByteCode constantPoolSize;
  this->constantPoolSize = constantPoolSize.read2bytes(fp);
}

/* Seta a constantPool com estrutura CP_info usando o arquivo fp (.class)
 * Utiliza constantPoolSize para saber o número de entradas da
 * tabela e o método read1byte lê a tag e utiliza um método get
 * para a informacao apropriada
 */
void ClassFile::setConstantPool(FILE* fp) {
  int constantPoolSize = this->constantPoolSize - 1;

  for (int i = 0; i < constantPoolSize; i++) {
    uint8_t tag = ReadClassByteCode().read1byte(fp);
    CP_info cpInfo;
    cpInfo.tag = tag;
    switch (tag) {
      // Class
      case 7:
        cpInfo.info.class_info = ReadClassByteCode().getClassInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // Fieldref
      case 9:
        cpInfo.info.fieldref_info = ReadClassByteCode().getFieldRefInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // Methodref
      case 10:
        cpInfo.info.methodref_info = ReadClassByteCode().getMethodRefInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // InterfaceMethodref
      case 11:
        cpInfo.info.interfaceMethodref_info = ReadClassByteCode().getInterfaceMethodRefInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // String
      case 8:
        cpInfo.info.string_info = ReadClassByteCode().getStringInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // Integer
      case 3:
        cpInfo.info.integer_info = ReadClassByteCode().getIntegerInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // Float
      case 4:
        cpInfo.info.float_info = ReadClassByteCode().getFloatInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // Long
      case 5:
        cpInfo.info.long_info = ReadClassByteCode().getLongInfo(fp);
        this->constantPool.push_back(cpInfo);
        CP_info cpInfo1;
        cpInfo1.tag = 0;
        this->constantPool.push_back(cpInfo1);
        i++;
        break;

      // Double
      case 6:
        cpInfo.info.double_info = ReadClassByteCode().getDoubleInfo(fp);
        this->constantPool.push_back(cpInfo);
        CP_info cpInfo2;
        cpInfo2.tag = 0;
        this->constantPool.push_back(cpInfo2);
        i++;
        break;

      // NameAndType
      case 12:
        cpInfo.info.nameAndType_info = ReadClassByteCode().getNameAndTypeInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // UTF8
      case 1:
        cpInfo.info.utf8_info = ReadClassByteCode().getUTF8Info(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // MethodHandle
      case 15:
        cpInfo.info.methodHandle_info = ReadClassByteCode().getMethodHandleInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // MethodType
      case 16:
        cpInfo.info.methodType_info = ReadClassByteCode().getMethodTypeInfo(fp);
        this->constantPool.push_back(cpInfo);
        break;

      // InvokeDynamic
      case 18:
        cpInfo.info.invokeDynamic_info = ReadClassByteCode().getInvokeDynamic_info(fp);
        this->constantPool.push_back(cpInfo);
        break;
    }
  }
}

// Define o valor de accessFlags usando o arquivo fp (.class)
void ClassFile::setAccessFlags(FILE* fp) {
  ReadClassByteCode accessFlags;
  this->accessFlags = accessFlags.read2bytes(fp);
}

// Define o valor de thisClass usando o arquivo fp (.class)
void ClassFile::setThisClass(FILE* fp) {
  ReadClassByteCode thisClass;
  this->thisClass = thisClass.read2bytes(fp);
}

// Define o valor de superClass usando o arquivo fp (.class)
void ClassFile::setSuperClass(FILE* fp) {
  ReadClassByteCode superClass;
  this->superClass = superClass.read2bytes(fp);
}

// Define o valor de interfacesCount usando o arquivo fp (.class)
void ClassFile::setInterfacesCount(FILE* fp) {
  ReadClassByteCode interfacesCount;
  this->interfacesCount = interfacesCount.read2bytes(fp);
}

/* Define a tabela de Interfaces usando o arquivo fp (.class)
 * interfacesCount contem o numero de entradas da tabela (total de entradas)
 */
void ClassFile::setInterfaces(FILE* fp) {
  for (int i = 0; i < this->interfacesCount; i++) {
    u2 interface = ReadClassByteCode().read2bytes(fp);
    this->interfaces.push_back(interface);
  }
}

// Define o valor de fieldsCount usando o arquivo fp (.class)
void ClassFile::setFieldsCount(FILE* fp) {
  ReadClassByteCode fieldsCount;
  this->fieldsCount = fieldsCount.read2bytes(fp);
}

/*
 * Define a tabela Fields com estruturas fieldInfo usando o arquivo fp (.class).
 * fieldsCount para saber o número de entradas da tabela (total de entradas)
 * malloc aloca memoria para o tamanho adequado
 */
void ClassFile::setFields(FILE* fp) {
  for (int i = 0; i < this->fieldsCount; i++) {
    Field_info fieldInfo;
    fieldInfo.access_flags = ReadClassByteCode().read2bytes(fp);
    fieldInfo.name_index = ReadClassByteCode().read2bytes(fp);
    fieldInfo.descriptor_index = ReadClassByteCode().read2bytes(fp);
    fieldInfo.attributesCount = ReadClassByteCode().read2bytes(fp);
    int contador = fieldInfo.attributesCount;
    fieldInfo.attributes = static_cast<Attribute_info*>(malloc(contador * sizeof(Attribute_info)));
    for (int j = 0; j < contador; j++) {
      fieldInfo.attributes[j] = ReadClassByteCode().getAttributeInfo(fp, constantPool);
    }
    this->fields.push_back(fieldInfo);
  }
}

// Define o valor de methodsCount usando o arquivo fp (.class)
void ClassFile::setMethodsCount(FILE* fp) {
  ReadClassByteCode methodsCount;
  this->methodsCount = methodsCount.read2bytes(fp);
}

/* Define Methods com a estrutura methodInfo usando o arquivo fp (.class)
 * methodsCount define o numero de entradas da tabela (total de entradas)
 * malloc aloca memoria para o tamanho adequado
 */
void ClassFile::setMethods(FILE* fp) {
  for (int i = 0; i < this->methodsCount; i++) {
    Method_info methodInfo;
    methodInfo.access_flags = ReadClassByteCode().read2bytes(fp);
    methodInfo.name_index = ReadClassByteCode().read2bytes(fp);
    methodInfo.descriptor_index = ReadClassByteCode().read2bytes(fp);
    methodInfo.attributesCount = ReadClassByteCode().read2bytes(fp);
    int counter = methodInfo.attributesCount;
    methodInfo.attributes = static_cast<Attribute_info*>(malloc(counter * sizeof(Attribute_info)));
    for (int j = 0; j < counter; j++) {
      methodInfo.attributes[j] = ReadClassByteCode().getAttributeInfo(fp, constantPool);
    }
    this->methods.push_back(methodInfo);
  }
}

// Define o valor de  attributesCount usando o arquivo fp (.class)
void ClassFile::setAttributesCount(FILE* fp) {
  ReadClassByteCode attributesCount;
  this->attributesCount = attributesCount.read2bytes(fp);
}

/*
 * Define Attribute_info usando o arquivo fp (.class)
 * attributesCount define o numero de entradas da tabela (total de entradas)
 */
void ClassFile::setAttributes(FILE* fp) {
  for (int i = 0; i < this->attributesCount; i++) {
    this->attributes.push_back(ReadClassByteCode().getAttributeInfo(fp, constantPool));
  }
}

u4 ClassFile::getMagicNumber() { return magicNumber; }
u2 ClassFile::getMinorVersion() { return minorVersion; }
u2 ClassFile::getMajorVersion() { return majorVersion; }
u2 ClassFile::getConstantPoolSize() { return constantPoolSize; }
vector<CP_info> ClassFile::getConstantPool() { return constantPool; }
u2 ClassFile::getAccessFlags() { return accessFlags; }
u2 ClassFile::getThisClass() { return thisClass; }
u2 ClassFile::getSuperClass() { return superClass; }
u2 ClassFile::getInterfacesCount() { return interfacesCount; }
vector<u2> ClassFile::getInterfaces() { return interfaces; }
u2 ClassFile::getFieldsCount() { return fieldsCount; }
vector<Field_info> ClassFile::getFields() { return fields; }
u2 ClassFile::getMethodsCount() { return methodsCount; }
vector<Method_info> ClassFile::getMethods() { return methods; }
u2 ClassFile::getAttributesCount() { return attributesCount; }
vector<Attribute_info> ClassFile::getAttributes() { return attributes; }
