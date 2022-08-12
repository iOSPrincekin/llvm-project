#include "llvm/Transforms/CountIR/CountIR.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/Debug.h"

// Run as:
// bin/opt --passes="countir" ../countirpass/a.ll --stats
using namespace llvm;

#define DEBUG_TYPE "countir"

STATISTIC(NumOfInst, "Number of instructions.");
STATISTIC(NumOfBB, "Number of basic blocks.");

PreservedAnalyses
CountIRPass::run(Function &F, FunctionAnalysisManager &AM) {
  for (BasicBlock &BB : F) {
    ++NumOfBB;
    for (Instruction &I : BB) {
      (void)I;
      ++NumOfInst;
    }
  }
  return PreservedAnalyses::all();
}
