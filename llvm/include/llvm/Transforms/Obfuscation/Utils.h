#ifndef __UTILS_OBF__
#define __UTILS_OBF__

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Transforms/Utils/Local.h" // For DemoteRegToStack and DemotePHIToStack

#include <stdio.h>

using namespace llvm;

#define DEBUG_TYPE "obfuscation"

void fixStack(Function *f);
std::string readAnnotate(Function *f);
bool toObfuscate(bool flag, Function *f, std::string attribute);



namespace llvm {

class LLVMObfuscationPass : public PassInfoMixin<LLVMObfuscationPass> {
public:
    PreservedAnalyses
    run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm


#endif
