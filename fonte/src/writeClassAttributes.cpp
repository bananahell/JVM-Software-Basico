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
    outputFile << "[" << i + 1 << "]: " << byteCodeInfo.getUTF8(classFile->getConstantPool().at(i)) << endl;
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
