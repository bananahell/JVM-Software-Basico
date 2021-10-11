#include "operations.h"

frame *Operations::frame = nullptr;
stack<struct frame *> *Operations::frames = nullptr;
FrameStack *Operations::frameStack = nullptr;
bool Operations::isWide = false;

const fun Operations::functions[] = {
    &Operations::nop,           &Operations::aconst_null,  &Operations::iconst_m1,
    &Operations::iconst_0,      &Operations::iconst_1,     &Operations::iconst_2,
    &Operations::iconst_3,      &Operations::iconst_4,     &Operations::iconst_5,
    &Operations::lconst_0,      &Operations::lconst_1,     &Operations::fconst_0,
    &Operations::fconst_1,      &Operations::fconst_2,     &Operations::dconst_0,
    &Operations::dconst_1,      &Operations::bipush,       &Operations::sipush,
    &Operations::ldc,           &Operations::ldc_w,        &Operations::ldc2_w,
    &Operations::iload,         &Operations::lload,        &Operations::fload,
    &Operations::dload,         &Operations::aload,        &Operations::iload_0,
    &Operations::iload_1,       &Operations::iload_2,      &Operations::iload_3,
    &Operations::lload_0,       &Operations::lload_1,      &Operations::lload_2,
    &Operations::lload_3,       &Operations::fload_0,      &Operations::fload_1,
    &Operations::fload_2,       &Operations::fload_3,      &Operations::dload_0,
    &Operations::dload_1,       &Operations::dload_2,      &Operations::dload_3,
    &Operations::aload_0,       &Operations::aload_1,      &Operations::aload_2,
    &Operations::aload_3,       &Operations::iaload,       &Operations::laload,
    &Operations::faload,        &Operations::daload,       &Operations::aaload,
    &Operations::baload,        &Operations::caload,       &Operations::saload,
    &Operations::istore,        &Operations::lstore,       &Operations::fstore,
    &Operations::dstore,        &Operations::astore,       &Operations::istore_0,
    &Operations::istore_1,      &Operations::istore_2,     &Operations::istore_3,
    &Operations::lstore_0,      &Operations::lstore_1,     &Operations::lstore_2,
    &Operations::lstore_3,      &Operations::fstore_0,     &Operations::fstore_1,
    &Operations::fstore_2,      &Operations::fstore_3,     &Operations::dstore_0,
    &Operations::dstore_1,      &Operations::dstore_2,     &Operations::dstore_3,
    &Operations::astore_0,      &Operations::astore_1,     &Operations::astore_2,
    &Operations::astore_3,      &Operations::iastore,      &Operations::lastore,
    &Operations::fastore,       &Operations::dastore,      &Operations::aastore,
    &Operations::bastore,       &Operations::castore,      &Operations::sastore,
    &Operations::pop,           &Operations::pop2,         &Operations::dup,
    &Operations::dup_x1,        &Operations::dup_x2,       &Operations::dup2,
    &Operations::dup2_x1,       &Operations::dup2_x2,      &Operations::swap,
    &Operations::iadd,          &Operations::ladd,         &Operations::fadd,
    &Operations::dadd,          &Operations::isub,         &Operations::lsub,
    &Operations::fsub,          &Operations::dsub,         &Operations::imul,
    &Operations::lmul,          &Operations::fmul,         &Operations::dmul,
    &Operations::idiv,          &Operations::ldiv,         &Operations::fdiv,
    &Operations::ddiv,          &Operations::irem,         &Operations::lrem,
    &Operations::frem,          &Operations::drem,         &Operations::ineg,
    &Operations::lneg,          &Operations::fneg,         &Operations::dneg,
    &Operations::ishl,          &Operations::lshl,         &Operations::ishr,
    &Operations::lshr,          &Operations::iushr,        &Operations::lushr,
    &Operations::iand,          &Operations::land,         &Operations::ior,
    &Operations::lor,           &Operations::ixor,         &Operations::lxor,
    &Operations::iinc,          &Operations::i2l,          &Operations::i2f,
    &Operations::i2d,           &Operations::l2i,          &Operations::l2f,
    &Operations::l2d,           &Operations::f2i,          &Operations::f2l,
    &Operations::f2d,           &Operations::d2i,          &Operations::d2l,
    &Operations::d2f,           &Operations::i2b,          &Operations::i2c,
    &Operations::i2s,           &Operations::lcmp,         &Operations::fcmpl,
    &Operations::fcmpg,         &Operations::dcmpl,        &Operations::dcmpg,
    &Operations::ifeq,          &Operations::ifne,         &Operations::iflt,
    &Operations::ifge,          &Operations::ifgt,         &Operations::ifle,
    &Operations::if_icmpeq,     &Operations::if_icmpne,    &Operations::if_icmplt,
    &Operations::if_icmpge,     &Operations::if_icmpgt,    &Operations::if_icmple,
    &Operations::if_acmpeq,     &Operations::if_acmpne,    &Operations::funcgoto,
    &Operations::jsr,           &Operations::funcret,      &Operations::tableswitch,
    &Operations::lookupswitch,  &Operations::ireturn,      &Operations::lreturn,
    &Operations::freturn,       &Operations::dreturn,      &Operations::areturn,
    &Operations::func_return,   &Operations::getstatic,    &Operations::putstatic,
    &Operations::getfield,      &Operations::putfield,     &Operations::invokevirtual,
    &Operations::invokespecial, &Operations::invokestatic, &Operations::invokeinterface,
    &Operations::nop,           &Operations::func_new,     &Operations::newarray,
    &Operations::anewarray,     &Operations::arraylength,  &Operations::athrow,
    &Operations::nop,           &Operations::nop,          &Operations::nop,
    &Operations::nop,           &Operations::wide,         &Operations::multianewarray,
    &Operations::ifnull,        &Operations::ifnonnull,    &Operations::goto_w,
    &Operations::jsr_w};

Operations::Operations(struct frame *ref) {
  this->frame = ref;
}

void Operations::setFrame(struct frame *newFrame) {
  frame = newFrame;
}

void Operations::setFrames(stack<struct frame *> *newFrames) {
  frames = newFrames;
}

void Operations::setFrameStack(FrameStack *newFrameStack) {
  frameStack = newFrameStack;
}

void Operations::run(int opcode) {
  functions[opcode]();
}

void Operations::nop() {}
void Operations::aconst_null() {}
void Operations::iconst_m1() {}
void Operations::iconst_0() {}
void Operations::iconst_1() {}
void Operations::iconst_2() {}
void Operations::iconst_3() {}
void Operations::iconst_4() {}
void Operations::iconst_5() {}
void Operations::lconst_0() {}
void Operations::lconst_1() {}
void Operations::fconst_0() {}
void Operations::fconst_1() {}
void Operations::fconst_2() {}
void Operations::dconst_0() {}
void Operations::dconst_1() {}
void Operations::bipush() {}
void Operations::sipush() {}
void Operations::ldc() {
  cout << "É TEEEEEEEEEEEEEEEEEETRA" << endl;
}
void Operations::ldc_w() {}
void Operations::ldc2_w() {}
void Operations::iload() {}
void Operations::lload() {}
void Operations::fload() {}
void Operations::dload() {}
void Operations::aload() {}
void Operations::athrow() {}
void Operations::iload_0() {}
void Operations::iload_1() {}
void Operations::iload_2() {}
void Operations::iload_3() {}
void Operations::lload_0() {}
void Operations::lload_1() {}
void Operations::lload_n(short index) {}
void Operations::lload_2() {}
void Operations::lload_3() {}
void Operations::fload_n(short index) {}
void Operations::fload_0() {}
void Operations::fload_1() {}
void Operations::fload_2() {}
void Operations::fload_3() {}
void Operations::dload_n(short index) {}
void Operations::dload_0() {}
void Operations::dload_1() {}
void Operations::dload_2() {}
void Operations::dload_3() {}
void Operations::aload_n(short index) {}
void Operations::aload_0() {}
void Operations::aload_1() {}
void Operations::aload_2() {}
void Operations::aload_3() {}
void Operations::iaload() {}
void Operations::laload() {}
void Operations::lstore_0() {}
void Operations::lstore() {}
void Operations::istore() {}
void Operations::fstore() {}
void Operations::dstore() {}
void Operations::astore() {}
void Operations::istore_0() {}
void Operations::istore_1() {}
void Operations::istore_2() {}
void Operations::istore_3() {}
void Operations::faload() {}
void Operations::daload() {}
void Operations::aaload() {}
void Operations::baload() {}
void Operations::caload() {}
void Operations::saload() {}
void Operations::lstore_1() {}
void Operations::lstore_2() {}
void Operations::lstore_3() {}
void Operations::fstore_0() {}
void Operations::fstore_1() {}
void Operations::fstore_2() {}
void Operations::fstore_3() {}
void Operations::dstore_0() {}
void Operations::dstore_1() {}
void Operations::dstore_2() {}
void Operations::dstore_3() {}
void Operations::astore_0() {}
void Operations::astore_1() {}
void Operations::astore_2() {}
void Operations::astore_3() {}
void Operations::iastore() {}
void Operations::lastore() {}
void Operations::fastore() {}
void Operations::dastore() {}
void Operations::aastore() {}
void Operations::bastore() {}
void Operations::castore() {}
void Operations::sastore() {}
void Operations::iadd() {}
void Operations::ladd() {}
void Operations::fadd() {}
void Operations::dadd() {}
void Operations::isub() {}
void Operations::lsub() {}
void Operations::fsub() {}
void Operations::dsub() {}
void Operations::imul() {}
void Operations::lmul() {}
void Operations::fmul() {}
void Operations::dmul() {}
void Operations::idiv() {}
void Operations::ldiv() {}
void Operations::fdiv() {}
void Operations::ddiv() {}
void Operations::irem() {}
void Operations::lrem() {}
void Operations::frem() {}
void Operations::drem() {}
void Operations::ineg() {}
void Operations::lneg() {}
void Operations::fneg() {}
void Operations::dneg() {}
void Operations::ishl() {}
void Operations::lshl() {}
void Operations::ishr() {}
void Operations::lshr() {}
void Operations::iushr() {}
void Operations::lushr() {}
void Operations::iand() {}
void Operations::land() {}
void Operations::ior() {}
void Operations::lor() {}
void Operations::ixor() {}
void Operations::lxor() {}
void Operations::iinc() {}
void Operations::i2l() {}
void Operations::i2f() {}
void Operations::i2d() {}
void Operations::l2i() {}
void Operations::l2f() {}
void Operations::l2d() {}
void Operations::f2i() {}
void Operations::f2l() {}
void Operations::f2d() {}
void Operations::d2i() {}
void Operations::d2l() {}
void Operations::d2f() {}
void Operations::i2b() {}
void Operations::i2c() {}
void Operations::i2s() {}
void Operations::lcmp() {}
void Operations::fcmpl() {}
void Operations::fcmpg() {}
void Operations::dcmpl() {}
void Operations::dcmpg() {}
void Operations::ifeq() {}
void Operations::ifne() {}
void Operations::iflt() {}
void Operations::ifge() {}
void Operations::ifgt() {}
void Operations::ifle() {}
void Operations::if_icmpeq() {}
void Operations::if_icmpne() {}
void Operations::if_icmplt() {}
void Operations::if_icmpge() {}
void Operations::if_icmpgt() {}
void Operations::if_icmple() {}
void Operations::if_acmpeq() {}
void Operations::if_acmpne() {}
void Operations::funcgoto() {}
void Operations::jsr() {}
void Operations::funcret() {}
void Operations::tableswitch() {}
void Operations::lookupswitch() {}
void Operations::ireturn() {}
void Operations::lreturn() {}
void Operations::freturn() {}
void Operations::dreturn() {}
void Operations::areturn() {}
void Operations::func_return() {}
void Operations::getstatic() {
  cout << "É TEEEEEEEEEEEEEEEEEETRA" << endl;
}
void Operations::putstatic() {}
void Operations::getfield() {}
void Operations::putfield() {}
void Operations::invokevirtual() {}
void Operations::invokespecial() {}
void Operations::invokestatic() {}
void Operations::invokeinterface() {}
void Operations::func_new() {}
void Operations::newarray() {}
void Operations::anewarray() {}
void Operations::arraylength() {}
void Operations::wide() {}
void Operations::multianewarray() {}
void Operations::ifnull() {}
void Operations::ifnonnull() {}
void Operations::goto_w() {}
void Operations::jsr_w() {}
void Operations::dup() {}
void Operations::pop() {}
void Operations::pop2() {}
void Operations::dup_x1() {}
void Operations::dup_x2() {}
void Operations::dup2() {}
void Operations::dup2_x1() {}
void Operations::dup2_x2() {}
void Operations::swap() {}
