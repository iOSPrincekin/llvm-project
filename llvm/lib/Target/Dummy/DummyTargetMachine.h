//===-- DummyTargetMachine.h - Define TargetMachine for Dummy ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the Dummy specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_DUMMY_DUMMYTARGETMACHINE_H
#define LLVM_LIB_TARGET_DUMMY_DUMMYTARGETMACHINE_H

#include "DummyInstrInfo.h"
#include "DummySubtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class DummyTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  DummySubtarget Subtarget;
  bool is64Bit;
  mutable StringMap<std::unique_ptr<DummySubtarget>> SubtargetMap;
public:
  DummyTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                     CodeGenOpt::Level OL, bool JIT, bool is64bit);
  ~DummyTargetMachine() override;

  const DummySubtarget *getSubtargetImpl() const { return &Subtarget; }
  const DummySubtarget *getSubtargetImpl(const Function &) const override;

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};

/// Dummy 32-bit target machine
///
class DummyV8TargetMachine : public DummyTargetMachine {
  virtual void anchor();
public:
  DummyV8TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                       StringRef FS, const TargetOptions &Options,
                       Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                       CodeGenOpt::Level OL, bool JIT);
};

/// Dummy 64-bit target machine
///
class DummyV9TargetMachine : public DummyTargetMachine {
  virtual void anchor();
public:
  DummyV9TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                       StringRef FS, const TargetOptions &Options,
                       Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                       CodeGenOpt::Level OL, bool JIT);
};

class DummyelTargetMachine : public DummyTargetMachine {
  virtual void anchor();

public:
  DummyelTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                       StringRef FS, const TargetOptions &Options,
                       Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                       CodeGenOpt::Level OL, bool JIT);
};

} // end namespace llvm

#endif
