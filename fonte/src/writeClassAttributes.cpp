#include "writeClassAttributes.h"

#include <fstream>
#include <iomanip>
#include <iostream>

bool writeAllToFile(ClassFile *classFile, string outputFileName) {
  ReadClassByteCode byteCodeInfo;
  ofstream outputFile;
  outputFile.open(outputFileName);
  if (!outputFile.is_open()) {
    cout << "There was a problem opening your file " << outputFileName << "...." << endl;
    return false;
  }

  outputFile << "[-----------------------------Magic, Minor, Major-----------------------------]" << endl;
  outputFile << "Magic number: 0x" << hex << classFile->getMagicNumber() << dec << endl;
  outputFile << "Minor Version: " << classFile->getMinorVersion() << endl;
  outputFile << "Major Version: " << classFile->getMajorVersion() << endl << endl << endl;

  // TODO
  outputFile << "[--------------------------------Constant Pool--------------------------------]" << endl;
  outputFile << "Constant Pool Count: " << classFile->getConstantPoolSize() - 1 << endl;
  for (int i = 0; i < classFile->getConstantPoolSize() - 1; i++) {
    CP_info cpInfo = classFile->getConstantPool().at(i);
    switch (cpInfo.tag) {
      // Class
      case 7:
        outputFile << "[" << i + 1 << "] Class:" << endl;
        outputFile << "    Name: "
                   << byteCodeInfo.getUTF8(classFile->getConstantPool().at(cpInfo.info.class_info.name_index - 1))
                   << "    *CP Index: " << cpInfo.info.class_info.name_index << endl;
        break;

      // Fieldref
      case 9:
        outputFile << "[" << i + 1 << "] FieldRef:" << endl;
        outputFile << "    Class: "
                   << byteCodeInfo.getUTF8(
                          classFile->getConstantPool().at(classFile->getConstantPool()
                                                              .at(cpInfo.info.fieldref_info.class_index - 1)
                                                              .info.class_info.name_index -
                                                          1))
                   << "    *CP Index: " << cpInfo.info.fieldref_info.class_index << endl;
        outputFile << "    Name And Type: "
                   << byteCodeInfo.getUTF8(
                          classFile->getConstantPool().at(classFile->getConstantPool()
                                                              .at(cpInfo.info.fieldref_info.nameAndType_index - 1)
                                                              .info.nameAndType_info.name_index -
                                                          1))
                   << " <"
                   << byteCodeInfo.getUTF8(
                          classFile->getConstantPool().at(classFile->getConstantPool()
                                                              .at(cpInfo.info.fieldref_info.nameAndType_index - 1)
                                                              .info.nameAndType_info.descriptor_index -
                                                          1))
                   << ">    *CP Index: " << cpInfo.info.fieldref_info.nameAndType_index << endl;
        break;

      // Methodref
      case 10:
        outputFile << "[" << i + 1 << "] MethodRef:" << endl;
        outputFile << "    Class: "
                   << byteCodeInfo.getUTF8(
                          classFile->getConstantPool().at(classFile->getConstantPool()
                                                              .at(cpInfo.info.methodref_info.class_index - 1)
                                                              .info.class_info.name_index -
                                                          1))
                   << "    *CP Index: " << cpInfo.info.methodref_info.class_index << endl;
        outputFile << "    Name And Type: "
                   << byteCodeInfo.getUTF8(
                          classFile->getConstantPool().at(classFile->getConstantPool()
                                                              .at(cpInfo.info.methodref_info.nameAndType_index - 1)
                                                              .info.nameAndType_info.name_index -
                                                          1))
                   << " <"
                   << byteCodeInfo.getUTF8(
                          classFile->getConstantPool().at(classFile->getConstantPool()
                                                              .at(cpInfo.info.methodref_info.nameAndType_index - 1)
                                                              .info.nameAndType_info.descriptor_index -
                                                          1))
                   << ">    *CP Index: " << cpInfo.info.methodref_info.nameAndType_index << endl;
        break;

      // InterfaceMethodref
      case 11:
        outputFile << "[" << i + 1 << "] Interface MethodRef:" << endl;
        outputFile << "    Class: "
                   << byteCodeInfo.getUTF8(
                          classFile->getConstantPool().at(classFile->getConstantPool()
                                                              .at(cpInfo.info.interfaceMethodref_info.class_index - 1)
                                                              .info.class_info.name_index -
                                                          1))
                   << "    *CP Index: " << cpInfo.info.interfaceMethodref_info.class_index << endl;
        outputFile << "    Name And Type: "
                   << byteCodeInfo.getUTF8(classFile->getConstantPool().at(
                          classFile->getConstantPool()
                              .at(cpInfo.info.interfaceMethodref_info.nameAndType_index - 1)
                              .info.nameAndType_info.name_index -
                          1))
                   << " <"
                   << byteCodeInfo.getUTF8(classFile->getConstantPool().at(
                          classFile->getConstantPool()
                              .at(cpInfo.info.interfaceMethodref_info.nameAndType_index - 1)
                              .info.nameAndType_info.descriptor_index -
                          1))
                   << ">    *CP Index: " << cpInfo.info.interfaceMethodref_info.nameAndType_index << endl;
        break;

      // String
      case 8:
        outputFile << "[" << i + 1 << "] String:" << endl;
        outputFile << "    String: "
                   << byteCodeInfo.getUTF8(classFile->getConstantPool().at(cpInfo.info.string_info.string_index - 1))
                   << "    *CP Index: " << cpInfo.info.string_info.string_index << endl;
        break;

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
      case 12:
        outputFile << "[" << i + 1 << "] Name and Type:" << endl;
        outputFile << "    Name: "
                   << byteCodeInfo.getUTF8(classFile->getConstantPool().at(cpInfo.info.nameAndType_info.name_index - 1))
                   << "    *CP Index: " << cpInfo.info.nameAndType_info.name_index << endl;
        outputFile << "    Type: "
                   << byteCodeInfo.getUTF8(
                          classFile->getConstantPool().at(cpInfo.info.nameAndType_info.descriptor_index - 1))
                   << "    *CP Index: " << cpInfo.info.nameAndType_info.descriptor_index << endl;
        break;

      // UTF8
      case 1:
        outputFile << "[" << i + 1 << "] UTF8:" << endl;
        outputFile << "    Length: " << (int)cpInfo.info.utf8_info.length << endl;
        outputFile << "    Content: " << byteCodeInfo.getUTF8(cpInfo) << endl;
        break;

      // MethodHandle
      case 15:
        outputFile << "[" << i + 1 << "] Method Handle:" << endl;
        outputFile << "    Reference Kind: " << (int)cpInfo.info.methodHandle_info.referenceKind
                   << "    *CP Index: " << cpInfo.info.methodHandle_info.referenceKind << endl;
        outputFile << "    Reference: "
                   << byteCodeInfo.getUTF8(
                          classFile->getConstantPool().at(cpInfo.info.methodHandle_info.reference_index - 1))
                   << "    *CP Index: " << cpInfo.info.methodHandle_info.reference_index << endl;
        break;

      // MethodType
      case 16:
        outputFile << "[" << i + 1 << "] Method Type:" << endl;
        outputFile << "    Type: "
                   << byteCodeInfo.getUTF8(
                          classFile->getConstantPool().at(cpInfo.info.methodType_info.descriptor_index - 1))
                   << "    *CP Index: " << cpInfo.info.methodType_info.descriptor_index << endl;
        break;

        // InvokeDynamic
        // case 18:
        // break;

      default:
        outputFile << "[" << i + 1 << "]: " << (int)cpInfo.tag << endl;
        break;
    }
    outputFile << endl;
  }
  outputFile << endl << endl;

  outputFile << "[-----------------------------Access, This, Super-----------------------------]" << endl;
  outputFile << "Access Flags: "
             << "0x" << hex << setfill('0') << setw(4) << classFile->getAccessFlags() << dec << endl;
  outputFile << "This Class: " << classFile->getThisClass() << endl;
  outputFile << "Super Class: " << classFile->getSuperClass() << endl << endl << endl;

  outputFile << "[---------------------------------Interfaces----------------------------------]" << endl;
  outputFile << "Interfaces Count: " << classFile->getInterfacesCount() << endl;
  for (int i = 0; i < classFile->getInterfacesCount(); i++) {
    outputFile << "[" << i + 1 << "]: " << classFile->getInterfaces().at(i) << endl;
  }
  outputFile << endl << endl;

  // TODO
  outputFile << "[-----------------------------------Fields------------------------------------]" << endl;
  outputFile << "Fields Count: " << classFile->getFieldsCount() << endl;
  for (int i = 0; i < classFile->getFieldsCount(); i++) {
    outputFile << "----------------------------------------" << endl;
    outputFile << "[" << i + 1 << "]: "
               << byteCodeInfo.getUTF8(
                      classFile->getConstantPool().at(classFile->getFields().at(i).descriptor_index - 1))
               << " "
               << byteCodeInfo.getUTF8(classFile->getConstantPool().at(classFile->getFields().at(i).name_index - 1))
               << endl;
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
  outputFile << "----------------------------------------" << endl;
  outputFile << endl << endl;

  // TODO
  outputFile << "[-----------------------------------Methods-----------------------------------]" << endl;
  outputFile << "Methods Count: " << classFile->getMethodsCount() << endl;
  for (int i = 0; i < classFile->getMethodsCount(); i++) {
    outputFile << "----------------------------------------" << endl;
    outputFile << "[" << i + 1 << "]: "
               << byteCodeInfo.getUTF8(
                      classFile->getConstantPool().at(classFile->getMethods().at(i).descriptor_index - 1))
               << " "
               << byteCodeInfo.getUTF8(classFile->getConstantPool().at(classFile->getMethods().at(i).name_index - 1))
               << endl;
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
  outputFile << "----------------------------------------" << endl;
  outputFile << endl << endl;

  // TODO
  outputFile << "[---------------------------------Attributes----------------------------------]" << endl;
  outputFile << "Attributes Count: " << classFile->getAttributesCount() << endl;
  for (int i = 0; i < classFile->getAttributesCount(); i++) {
    outputFile << "----------------------------------------" << endl;
    outputFile << "[" << i + 1 << "]: " << endl;
    outputFile << "    Attribute Name Index: " << classFile->getAttributes().at(i).attributeName_index << endl;
    outputFile << "    Attribute Length: " << classFile->getAttributes().at(i).attributeLength << endl;
  }
  outputFile << "----------------------------------------" << endl;

  outputFile.close();
  return true;
}
