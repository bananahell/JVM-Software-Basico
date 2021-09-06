#include "readClassByteCode.h"

using namespace std;

class ClassFile {
 private:
  u4 magicNumber;
  u2 minorVersion;
  u2 majorVersion;
  u2 constantPoolSize;
  vector<CP_info> constantPool;
  u2 accessFlags;
  u2 thisClass;
  u2 superClass;
  u2 interfacesCount;
  vector<u2> interfaces;
  u2 fieldsCount;
  vector<Field_info> fields;
  u2 methodsCount;
  vector<Method_info> methods;
  u2 attributesCount;
  vector<Attribute_info> attributes;

  void setMagicNumber(FILE*);
  void setMajorVersion(FILE*);
  void setMinorVersion(FILE*);
  void setConstantPoolSize(FILE*);
  void setConstantPool(FILE*);
  void setAccessFlags(FILE*);
  void setThisClass(FILE*);
  void setSuperClass(FILE*);
  void setInterfacesCount(FILE*);
  void setInterfaces(FILE*);
  void setFieldsCount(FILE*);
  void setFields(FILE*);
  void setMethodsCount(FILE*);
  void setMethods(FILE*);
  void setAttributesCount(FILE*);
  void setAttributes(FILE*);

 public:
  explicit ClassFile(FILE*);
  ClassFile();
  u4 getMagicNumber();
  u2 getMajorVersion();
  u2 getMinorVersion();
  u2 getConstantPoolSize();
  vector<CP_info> getConstantPool();
  u2 getAccessFlags();
  u2 getThisClass();
  u2 getSuperClass();
  u2 getInterfacesCount();
  vector<u2> getInterfaces();
  u2 getFieldsCount();
  vector<Field_info> getFields();
  u2 getMethodsCount();
  vector<Method_info> getMethods();
  u2 getAttributesCount();
  vector<Attribute_info> getAttributes();
};
