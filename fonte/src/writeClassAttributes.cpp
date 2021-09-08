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
        long result = (long)cpInfo.info.long_info.bytes;
        outputFile << "    Long: " << result << endl;
        break;
      }

      // Double
      case 6: {
        outputFile << "[" << i + 1 << "] Double:" << endl;
        double result = (double)cpInfo.info.double_info.bytes;
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
  vector<string> accessFlags = readAccessFlags(classFile->getAccessFlags());
  outputFile << "Access Flags: "
             << "0x" << hex << setfill('0') << setw(4) << classFile->getAccessFlags() << dec << " (";
  for (unsigned i = 0; i < accessFlags.size(); i++) {
    outputFile << accessFlags.at(i);
    if (i != accessFlags.size() - 1) {
      outputFile << " ";
    }
  }
  outputFile << ")" << endl;
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
    accessFlags = readAccessFlags(classFile->getFields().at(i).access_flags);
    outputFile << "    Access Flags: "
               << "0x" << hex << setfill('0') << setw(4) << classFile->getFields().at(i).access_flags << dec << " (";
    for (unsigned j = 0; j < accessFlags.size(); j++) {
      outputFile << accessFlags.at(j);
      if (j != accessFlags.size() - 1) {
        outputFile << " ";
      }
    }
    outputFile << ")" << endl;
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
  for (int i = 0; i < classFile->getMethodsCount(); i++) {
    Method_info mi = classFile->getMethods().at(i);
    vector<CP_info> cp = classFile->getConstantPool();
    outputFile << cp.at(mi.name_index - 1).info.utf8_info.bytes << " "
               << cp.at(mi.descriptor_index - 1).info.utf8_info.bytes << endl;

    outputFile << "Access Flags: ";
    vector<string> aflg = readAccessFlags((int)mi.access_flags);
    for (int j = 0; j < (int)aflg.size(); j++) outputFile << aflg.at(j) << " ";
    outputFile << "(0x0" << hex << mi.access_flags << dec << ")" << endl;

    outputFile << "Attributes: " << endl;
    for (int j = 0; j < mi.attributesCount; j++) {
      outputFile << "  " << cp.at(mi.attributes[j].attributeName_index - 1).info.utf8_info.bytes << endl;
      outputFile << "  Attribute Length: " << mi.attributes[j].attributeLength << endl;
      outputFile << "  Code Length: " << mi.attributes[j].info.code_info.codeLength << endl;
      outputFile << "  Bytecode:" << endl;

      for (int k = 0; k < (int)mi.attributes[j].info.code_info.codeLength; k++) {
        int byteCode = (int)mi.attributes[j].info.code_info.code[k];
        outputFile << "    " << k << ((k > 99) ? "" : ((k > 9) ? " " : "  ")) << "  " << ops[byteCode].first;
        for (int l = 1; l <= ops[byteCode].second; l++) {
          int idx = (int)mi.attributes[j].info.code_info.code[k + l];
          if (idx != 0 && idx <= classFile->getConstantPoolSize()) {
            outputFile << "  #" << idx << ((idx > 99) ? "" : ((idx > 9) ? " " : "  ")) << "  ";
            CP_info cpInfo = cp.at(idx - 1);
            switch (cpInfo.tag) {
              // UTF8
              case 1:
                outputFile << cpInfo.info.utf8_info.bytes;
                break;

              // Integer
              case 3:
                outputFile << (int)cpInfo.info.integer_info.bytes;
                break;

              // Float
              case 4:
                outputFile << (float)cpInfo.info.float_info.bytes;
                break;

              // Long
              case 5:
                outputFile << 1;
                break;

              // Double
              case 6:
                outputFile << 1;
                break;

              // Class
              case 7:
                outputFile << cp.at((int)cpInfo.info.class_info.name_index - 1).info.utf8_info.bytes;
                break;

              // String
              case 8:
                outputFile << cp.at(cpInfo.info.string_info.string_index - 1).info.utf8_info.bytes;
                break;

              // Fieldref
              case 9:
                outputFile
                    << cp.at(cp.at(cpInfo.info.fieldref_info.class_index - 1).info.class_info.name_index - 1)
                           .info.utf8_info.bytes
                    << "."
                    << cp.at(cp.at(cpInfo.info.fieldref_info.nameAndType_index - 1).info.nameAndType_info.name_index -
                             1)
                           .info.utf8_info.bytes;
                break;

              // Methodref
              case 10:
                outputFile
                    << cp.at(cp.at(cpInfo.info.methodref_info.class_index - 1).info.class_info.name_index - 1)
                           .info.utf8_info.bytes
                    << "."
                    << cp.at(cp.at(cpInfo.info.methodref_info.nameAndType_index - 1).info.nameAndType_info.name_index -
                             1)
                           .info.utf8_info.bytes;
                break;

              // InterfaceMethodref
              case 11:
                outputFile
                    << cp.at(cp.at(cpInfo.info.interfaceMethodref_info.class_index - 1).info.class_info.name_index - 1)
                           .info.utf8_info.bytes
                    << "."
                    << cp.at(cp.at(cpInfo.info.interfaceMethodref_info.nameAndType_index - 1)
                                 .info.nameAndType_info.name_index -
                             1)
                           .info.utf8_info.bytes;
                break;

              // NameAndType
              case 12:
                outputFile
                    << cp.at(cp.at(cpInfo.info.interfaceMethodref_info.class_index - 1).info.class_info.name_index - 1)
                           .info.utf8_info.bytes
                    << "."
                    << cp.at(cp.at(cpInfo.info.interfaceMethodref_info.nameAndType_index - 1)
                                 .info.nameAndType_info.name_index -
                             1)
                           .info.utf8_info.bytes;
                break;

              default:
                outputFile << "[" << i + 1 << "]: " << (int)cpInfo.tag << " (tag unknown)" << endl;
                break;
            }
          }
        }
        k += ops[byteCode].second;
        outputFile << endl;
      }
      outputFile << "  Attributes Count: " << mi.attributes[j].info.code_info.attributesCount << endl;

      for (int k = 0; k < (int)mi.attributes[j].info.code_info.attributesCount; k++) {
        Attribute_info attr = mi.attributes[j].info.code_info.attributes[k];
        outputFile << "    cp_index #" << attr.attributeName_index << " "
                   << cp.at(attr.attributeName_index - 1).info.utf8_info.bytes << endl;
        // outputFile << "    Line Number Table Length: " <<
        // (int)mi.attributes[j].info.code_info.attributes[k].info.lineNumberTable_info.lineNumberTableLength << endl;
        for (int l = 0;
             l < (int)mi.attributes[j].info.code_info.attributes[k].info.lineNumberTable_info.lineNumberTableLength;
             l++) {
          LineNumberTable lnt =
              mi.attributes[j].info.code_info.attributes[k].info.lineNumberTable_info.lineNumberTable[l];
          outputFile << "    Start PC: " << (int)lnt.startPc
                     << ((lnt.startPc > 99) ? "" : ((lnt.startPc > 9) ? " " : "  "))
                     << "    Line Number: " << (int)lnt.lineNumber << endl;
        }
      }
    }
    outputFile << endl << endl;
  }
  ///////////////////////////////////////////

  outputFile << "[---------------------------------Attributes----------------------------------]" << endl;
  outputFile << "Attributes Count: " << classFile->getAttributesCount() << endl;
  for (int i = 0; i < classFile->getAttributesCount(); i++) {
    int attributeNameIndex = classFile->getAttributes().at(i).attributeName_index - 1;
    string attributeName = ReadClassByteCode::getUTF8(classFile->getConstantPool().at(attributeNameIndex));
    outputFile << "----------------------------------------" << endl;
    outputFile << "[" << i + 1 << "] Attribute Name: " << attributeName << endl;
    outputFile << "    Attribute Name Index: " << classFile->getAttributes().at(i).attributeName_index << endl;
    outputFile << "    Attribute Length: " << classFile->getAttributes().at(i).attributeLength << endl;
    if (attributeName == "SourceFile") {
      outputFile << "    SourceFile: "
                 << ReadClassByteCode::getUTF8(classFile->getConstantPool().at(attributeNameIndex + 1))
                 << "    *CP Index: " << attributeNameIndex + 2 << endl;
    }
  }
  if (classFile->getAttributesCount() > 0) {
    outputFile << "----------------------------------------" << endl;
  }

  outputFile.close();
  return true;
}

vector<string> readAccessFlags(int accessFlag) {
  vector<string> resultFlags;
  if (accessFlag & 0x0001) {
    resultFlags.push_back("public");
  }
  if (accessFlag & 0x0002) {
    resultFlags.push_back("private");
  }
  if (accessFlag & 0x0004) {
    resultFlags.push_back("protected");
  }
  if (accessFlag & 0x0008) {
    resultFlags.push_back("static");
  }
  if (accessFlag & 0x0010) {
    resultFlags.push_back("final");
  }
  if (accessFlag & 0x0040) {
    resultFlags.push_back("volatile");
  }
  if (accessFlag & 0x0080) {
    resultFlags.push_back("transient");
  }
  if (accessFlag & 0x1000) {
    resultFlags.push_back("synthetic");
  }
  if (accessFlag & 0x4000) {
    resultFlags.push_back("enum");
  }
  return resultFlags;
}
