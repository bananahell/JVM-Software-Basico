#include "writeClassAttributes.h"

#include <fstream>
#include <iomanip>
#include <iostream>

bool writeAllToFile(ClassFile *classFile, string outputFileName) {
  ofstream outputFile;
  outputFile.open(outputFileName);
  if (!outputFile.is_open()) {
    cout << "There was a problem opening your file " << outputFileName << "...." << endl;
    return false;
  }

  outputFile << "[-----------------------------Magic, Minor, Major-----------------------------]" << endl;
  outputFile << "Magic number: 0x" << hex << classFile->getMagicNumber() << dec << endl;
  outputFile << "Minor Version: " << classFile->getMinorVersion() << endl;
  outputFile << "Major Version: " << classFile->getMajorVersion() << " (Java ";
  vector<float> javaVersions = {1.2, 1.3, 1.4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  if (classFile->getMajorVersion() >= 46 && classFile->getMajorVersion() <= 60) {
    outputFile << javaVersions.at(classFile->getMajorVersion() - 46) << ")" << endl << endl << endl;
  } else {
    outputFile << "version not found!!!" << endl << endl << endl;
  }

  // TODO
  outputFile << "[--------------------------------Constant Pool--------------------------------]" << endl;
  outputFile << "Constant Pool Count: " << classFile->getConstantPoolSize() - 1 << endl;
  for (int i = 0; i < classFile->getConstantPoolSize() - 1; i++) {
    CP_info cpInfo = classFile->getConstantPool().at(i);
    switch (cpInfo.tag) {
      // Class
      case 7: {
        CP_info classCPInfo = classFile->getConstantPool().at(cpInfo.info.class_info.name_index - 1);
        string className = ReadClassByteCode::getUTF8(classCPInfo);
        outputFile << "[" << i + 1 << "] Class:" << endl;
        outputFile << "    Name: " << className << "    *CP Index: " << cpInfo.info.class_info.name_index << endl;
        break;
      }

      // Fieldref
      case 9: {
        FIELD_REF_INFO fieldRefInfo = cpInfo.info.fieldref_info;
        int classIndex = classFile->getConstantPool().at(fieldRefInfo.class_index - 1).info.class_info.name_index - 1;
        CP_info classCPInfo = classFile->getConstantPool().at(classIndex);
        string className = ReadClassByteCode::getUTF8(classCPInfo);
        int nameAndTypeIndex = fieldRefInfo.nameAndType_index - 1;
        int nameIndex = classFile->getConstantPool().at(nameAndTypeIndex).info.nameAndType_info.name_index - 1;
        CP_info nameCPInfo = classFile->getConstantPool().at(nameIndex);
        string nameName = ReadClassByteCode::getUTF8(nameCPInfo);
        int typeIndex = classFile->getConstantPool().at(nameAndTypeIndex).info.nameAndType_info.descriptor_index - 1;
        CP_info typeCPInfo = classFile->getConstantPool().at(typeIndex);
        string typeName = ReadClassByteCode::getUTF8(typeCPInfo);
        outputFile << "[" << i + 1 << "] FieldRef:" << endl;
        outputFile << "    Class: " << className << "    *CP Index: " << fieldRefInfo.class_index << endl;
        outputFile << "    Name And Type: " << nameName << " <" << typeName
                   << ">    *CP Index: " << fieldRefInfo.nameAndType_index << endl;
        break;
      }

      // Methodref
      case 10: {
        METHOD_REF_INFO methodRefInfo = cpInfo.info.methodref_info;
        int classIndex = classFile->getConstantPool().at(methodRefInfo.class_index - 1).info.class_info.name_index - 1;
        CP_info classCPInfo = classFile->getConstantPool().at(classIndex);
        string className = ReadClassByteCode::getUTF8(classCPInfo);
        int nameAndTypeIndex = methodRefInfo.nameAndType_index - 1;
        int nameIndex = classFile->getConstantPool().at(nameAndTypeIndex).info.nameAndType_info.name_index - 1;
        CP_info nameCPInfo = classFile->getConstantPool().at(nameIndex);
        string nameName = ReadClassByteCode::getUTF8(nameCPInfo);
        int typeIndex = classFile->getConstantPool().at(nameAndTypeIndex).info.nameAndType_info.descriptor_index - 1;
        CP_info typeCPInfo = classFile->getConstantPool().at(typeIndex);
        string typeName = ReadClassByteCode::getUTF8(typeCPInfo);
        outputFile << "[" << i + 1 << "] MethodRef:" << endl;
        outputFile << "    Class: " << className << "    *CP Index: " << methodRefInfo.class_index << endl;
        outputFile << "    Name And Type: " << nameName << " <" << typeName
                   << ">    *CP Index: " << methodRefInfo.nameAndType_index << endl;
        break;
      }

      // InterfaceMethodref
      case 11: {
        INTERFACE_METHOD_REF_INFO intMetRefInfo = cpInfo.info.interfaceMethodref_info;
        int classIndex = classFile->getConstantPool().at(intMetRefInfo.class_index - 1).info.class_info.name_index - 1;
        CP_info classCPInfo = classFile->getConstantPool().at(classIndex);
        string className = ReadClassByteCode::getUTF8(classCPInfo);
        int nameAndTypeIndex = intMetRefInfo.nameAndType_index - 1;
        int nameIndex = classFile->getConstantPool().at(nameAndTypeIndex).info.nameAndType_info.name_index - 1;
        CP_info nameCPInfo = classFile->getConstantPool().at(nameIndex);
        string nameName = ReadClassByteCode::getUTF8(nameCPInfo);
        int typeIndex = classFile->getConstantPool().at(nameAndTypeIndex).info.nameAndType_info.descriptor_index - 1;
        CP_info typeCPInfo = classFile->getConstantPool().at(typeIndex);
        string typeName = ReadClassByteCode::getUTF8(typeCPInfo);
        outputFile << "[" << i + 1 << "] Interface MethodRef:" << endl;
        outputFile << "    Class: " << className << "    *CP Index: " << intMetRefInfo.class_index << endl;
        outputFile << "    Name And Type: " << nameName << " <" << typeName
                   << ">    *CP Index: " << intMetRefInfo.nameAndType_index << endl;
        break;
      }

      // String
      case 8: {
        int stringIndex = cpInfo.info.string_info.string_index;
        outputFile << "[" << i + 1 << "] String:" << endl;
        outputFile << "    String: " << ReadClassByteCode::getUTF8(classFile->getConstantPool().at(stringIndex - 1))
                   << "    *CP Index: " << stringIndex << endl;
        break;
      }

      // Integer
      case 3:
        outputFile << "[" << i + 1 << "] Integer:" << endl;
        outputFile << "    Integer: " << (int)cpInfo.info.integer_info.bytes << endl;
        break;

      // Float
      case 4:
        outputFile << "[" << i + 1 << "] Float:" << endl;
        outputFile << "    Float: " << (float)cpInfo.info.float_info.bytes << endl;
        break;

      // Long
      case 5: {
        outputFile << "[" << i + 1 << "] Long:" << endl;
        long result = ((long)cpInfo.info.long_info.highBytes << 4) + (long)cpInfo.info.long_info.lowBytes;
        outputFile << "    Long: " << result << endl;
        break;
      }

      // Double
      case 6: {
        outputFile << "[" << i + 1 << "] Double:" << endl;
        double result = ((double)(cpInfo.info.long_info.highBytes << 4)) + ((double)cpInfo.info.long_info.lowBytes);
        outputFile << "    Double: " << result << endl;
        break;
      }

      // NameAndType
      case 12: {
        NAME_AND_TYPE_INFO nameAndTypeInfo = cpInfo.info.nameAndType_info;
        CP_info nameCPInfo = classFile->getConstantPool().at(nameAndTypeInfo.name_index - 1);
        string nameName = ReadClassByteCode::getUTF8(nameCPInfo);
        CP_info typeCPInfo = classFile->getConstantPool().at(nameAndTypeInfo.descriptor_index - 1);
        string typeName = ReadClassByteCode::getUTF8(typeCPInfo);
        outputFile << "[" << i + 1 << "] Name and Type:" << endl;
        outputFile << "    Name: " << nameName << "    *CP Index: " << nameAndTypeInfo.name_index << endl;
        outputFile << "    Type: " << typeName << "    *CP Index: " << nameAndTypeInfo.descriptor_index << endl;
        break;
      }

      // UTF8
      case 1:
        outputFile << "[" << i + 1 << "] UTF8:" << endl;
        outputFile << "    Length: " << (int)cpInfo.info.utf8_info.length << endl;
        outputFile << "    Content: " << ReadClassByteCode::getUTF8(cpInfo) << endl;
        break;

      // MethodHandle
      case 15: {
        METHOD_HANDLE_INFO methodHandleInfo = cpInfo.info.methodHandle_info;
        CP_info referenceCPInfo = classFile->getConstantPool().at(methodHandleInfo.reference_index - 1);
        string referenceName = ReadClassByteCode::getUTF8(referenceCPInfo);
        outputFile << "[" << i + 1 << "] Method Handle:" << endl;
        outputFile << "    Reference Kind: " << (int)methodHandleInfo.referenceKind
                   << "    *CP Index: " << methodHandleInfo.referenceKind << endl;
        outputFile << "    Reference: " << referenceName << "    *CP Index: " << methodHandleInfo.reference_index
                   << endl;
        break;
      }

      // MethodType
      case 16: {
        CP_info methodTypeCPInfo = classFile->getConstantPool().at(cpInfo.info.methodType_info.descriptor_index - 1);
        outputFile << "[" << i + 1 << "] Method Type:" << endl;
        outputFile << "    Type: " << ReadClassByteCode::getUTF8(methodTypeCPInfo)
                   << "    *CP Index: " << cpInfo.info.methodType_info.descriptor_index << endl;
        break;
      }

        // InvokeDynamic
        // case 18:
        // break;

      default:
        outputFile << "[" << i + 1 << "]: " << (int)cpInfo.tag << " (tag unknown)" << endl;
        break;
    }
    outputFile << endl;
  }
  outputFile << endl << endl;

  outputFile << "[-----------------------------Access, This, Super-----------------------------]" << endl;
  outputFile << "Access Flags: "
             << "0x" << hex << setfill('0') << setw(4) << classFile->getAccessFlags() << dec << endl;
  outputFile << "This Class: "
             << ReadClassByteCode::getUTF8(classFile->getConstantPool().at(
                    classFile->getConstantPool().at(classFile->getThisClass() - 1).info.class_info.name_index - 1))
             << "    *CP Index: " << classFile->getThisClass() << endl;
  outputFile << "Super Class: "
             << ReadClassByteCode::getUTF8(classFile->getConstantPool().at(
                    classFile->getConstantPool().at(classFile->getSuperClass() - 1).info.class_info.name_index - 1))
             << "    *CP Index: " << classFile->getSuperClass() << endl
             << endl
             << endl;

  outputFile << "[---------------------------------Interfaces----------------------------------]" << endl;
  outputFile << "Interfaces Count: " << classFile->getInterfacesCount() << endl;
  for (int i = 0; i < classFile->getInterfacesCount(); i++) {
    outputFile << "----------------------------------------" << endl;
    outputFile
        << "[" << i + 1 << "]: "
        << ReadClassByteCode::getUTF8(classFile->getConstantPool().at(
               classFile->getConstantPool().at((int)classFile->getInterfaces().at(i) - 1).info.class_info.name_index -
               1))
        << "    *CP Index: " << (int)classFile->getInterfaces().at(i) << endl;
  }
  if (classFile->getInterfacesCount() > 0) {
    outputFile << "----------------------------------------" << endl;
  }
  outputFile << endl << endl;

  outputFile << "[-----------------------------------Fields------------------------------------]" << endl;
  outputFile << "Fields Count: " << classFile->getFieldsCount() << endl;
  for (int i = 0; i < classFile->getFieldsCount(); i++) {
    outputFile << "----------------------------------------" << endl;
    outputFile << "[" << i + 1 << "] Name and Type: "
               << ReadClassByteCode::getUTF8(
                      classFile->getConstantPool().at(classFile->getFields().at(i).name_index - 1))
               << " <"
               << ReadClassByteCode::getUTF8(
                      classFile->getConstantPool().at(classFile->getFields().at(i).descriptor_index - 1))
               << ">" << endl;
    outputFile << "    Access Flags: "
               << "0x" << hex << setfill('0') << setw(4) << classFile->getFields().at(i).access_flags << dec << endl;
    outputFile << "    Name Index: " << classFile->getFields().at(i).name_index << endl;
    outputFile << "    Descriptor Index: " << classFile->getFields().at(i).descriptor_index << endl;
    outputFile << "    Attributes Count: " << classFile->getFields().at(i).attributesCount << endl;
    for (int j = 0; j < classFile->getFields().at(i).attributesCount; j++) {
      outputFile << "      **********" << endl;
      outputFile << "      Attribute Name Index: " << classFile->getFields().at(i).attributes->attributeName_index
                 << endl;
      outputFile << "      Attribute Length: " << classFile->getFields().at(i).attributes->attributeLength << endl;
    }
    if (classFile->getFields().at(i).attributesCount > 0) {
      outputFile << "      **********" << endl;
    }
  }
  if (classFile->getFieldsCount() > 0) {
    outputFile << "----------------------------------------" << endl;
  }
  outputFile << endl << endl;

  // TODO
  outputFile << "[-----------------------------------Methods-----------------------------------]" << endl;
  outputFile << "Methods Count: " << classFile->getMethodsCount() << endl;
  for (int i = 0; i < classFile->getMethodsCount(); i++) {
    outputFile << "----------------------------------------" << endl;
    outputFile << "[" << i + 1 << "] Name and Type: "
               << ReadClassByteCode::getUTF8(
                      classFile->getConstantPool().at(classFile->getMethods().at(i).name_index - 1))
               << " <"
               << ReadClassByteCode::getUTF8(
                      classFile->getConstantPool().at(classFile->getMethods().at(i).descriptor_index - 1))
               << ">" << endl;
    outputFile << "    Access Flags: "
               << "0x" << hex << setfill('0') << setw(4) << classFile->getMethods().at(i).access_flags << dec << endl;
    outputFile << "    Name Index: " << classFile->getMethods().at(i).name_index << endl;
    outputFile << "    Descriptor Index: " << classFile->getMethods().at(i).descriptor_index << endl;
    outputFile << "    Attributes Count: " << classFile->getMethods().at(i).attributesCount << endl;
    for (int j = 0; j < classFile->getMethods().at(i).attributesCount; j++) {
      outputFile << "      **********" << endl;
      outputFile << "      Attribute Name Index: " << classFile->getMethods().at(i).attributes->attributeName_index
                 << endl;
      outputFile << "      Attribute Length: " << classFile->getMethods().at(i).attributes->attributeLength << endl;
    }
    if (classFile->getMethods().at(i).attributesCount > 0) {
      outputFile << "      **********" << endl;
    }
  }
  if (classFile->getMethodsCount() > 0) {
    outputFile << "----------------------------------------" << endl;
  }
  outputFile << endl << endl;

  outputFile << "[---------------------------------Attributes----------------------------------]" << endl;
  outputFile << "Attributes Count: " << classFile->getAttributesCount() << endl;
  for (int i = 0; i < classFile->getAttributesCount(); i++) {
    outputFile << "----------------------------------------" << endl;
    outputFile << "[" << i + 1 << "] Attribute Name: "
               << ReadClassByteCode::getUTF8(
                      classFile->getConstantPool().at(classFile->getAttributes().at(i).attributeName_index - 1))
               << endl;
    outputFile << "    Attribute Name Index: " << classFile->getAttributes().at(i).attributeName_index << endl;
    outputFile << "    Attribute Length: " << classFile->getAttributes().at(i).attributeLength << endl;
  }
  if (classFile->getAttributesCount() > 0) {
    outputFile << "----------------------------------------" << endl;
  }

  outputFile.close();
  return true;
}
