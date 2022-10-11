//===-- DummyTargetInfo.cpp - Dummy Target Implementation -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/DummyTargetInfo.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheDummyTarget() {
  static Target TheDummyTarget;
  return TheDummyTarget;
}
Target &llvm::getTheDummyV9Target() {
  static Target TheDummyV9Target;
  return TheDummyV9Target;
}
Target &llvm::getTheDummyelTarget() {
  static Target TheDummyelTarget;
  return TheDummyelTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeDummyTargetInfo() {
  RegisterTarget<Triple::Dummy, /*HasJIT=*/true> X(getTheDummyTarget(), "Dummy",
                                                   "Dummy", "Dummy");
  RegisterTarget<Triple::Dummyv9, /*HasJIT=*/true> Y(
      getTheDummyV9Target(), "Dummyv9", "Dummy V9", "Dummy");
  RegisterTarget<Triple::Dummyel, /*HasJIT=*/true> Z(
      getTheDummyelTarget(), "Dummyel", "Dummy LE", "Dummy");
}
