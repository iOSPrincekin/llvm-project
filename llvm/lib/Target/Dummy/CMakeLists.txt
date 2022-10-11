add_llvm_component_group(Dummy HAS_JIT)

set(LLVM_TARGET_DEFINITIONS Dummy.td)

tablegen(LLVM DummyGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM DummyGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM DummyGenCallingConv.inc -gen-callingconv)
tablegen(LLVM DummyGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM DummyGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM DummyGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM DummyGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM DummyGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM DummyGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(DummyCommonTableGen)

add_llvm_target(DummyCodeGen
  DelaySlotFiller.cpp
  LeonPasses.cpp
  DummyAsmPrinter.cpp
  DummyInstrInfo.cpp
  DummyISelDAGToDAG.cpp
  DummyISelLowering.cpp
  DummyFrameLowering.cpp
  DummyMachineFunctionInfo.cpp
  DummyRegisterInfo.cpp
  DummySubtarget.cpp
  DummyTargetMachine.cpp
  DummyMCInstLower.cpp
  DummyTargetObjectFile.cpp

  LINK_COMPONENTS
  AsmPrinter
  CodeGen
  Core
  MC
  SelectionDAG
  DummyDesc
  DummyInfo
  Support
  Target

  ADD_TO_COMPONENT
  Dummy
  )

add_subdirectory(AsmParser)
add_subdirectory(Disassembler)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
