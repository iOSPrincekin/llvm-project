#include "llvm/Transforms/Obfuscation/Utils.h"
#include "llvm/Transforms/Obfuscation/Substitution.h"
#include "llvm/Transforms/Obfuscation/BogusControlFlow.h"
#include "llvm/Transforms/Obfuscation/Flattening.h"
#include "llvm/Support/raw_ostream.h"
#include <sstream>
#include "llvm/IR/Module.h"


// Shamefully borrowed from ../Scalar/RegToMem.cpp :(
bool valueEscapes(Instruction *Inst) {
    BasicBlock *BB = Inst->getParent();
    for (Value::use_iterator UI = Inst->use_begin(),E = Inst->use_end(); UI != E; ++UI) {
        Instruction *I = cast<Instruction>(*UI);
        if (I->getParent() != BB || isa<PHINode>(I)) {
            return true;
        }
    }
    return false;
}

void fixStack(Function *f) {
    // Try to remove phi node and demote reg to stack
    std::vector<PHINode *> tmpPhi;
    std::vector<Instruction *> tmpReg;
    BasicBlock *bbEntry = &*f->begin();
    
    do{
        tmpPhi.clear();
        tmpReg.clear();
        
        for (Function::iterator i = f->begin(); i != f->end(); ++i) {
            for (BasicBlock::iterator j = i->begin(); j != i->end(); ++j) {
                if (isa<PHINode>(i)) {
                    PHINode *phi = cast<PHINode>(j);
                    tmpPhi.push_back(phi);
                    continue;
                }
                if (!(isa<AllocaInst>(j) && j->getParent() == bbEntry) && (valueEscapes(&*j) || j->isUsedOutsideOfBlock(&*i))) {
                    tmpReg.push_back(&*j);
                    continue;
                }
            }
        }
        for (unsigned int i = 0; i != tmpReg.size(); ++i) {
            DemoteRegToStack(*tmpReg.at(i),f->begin()->getTerminator());
        }
        for (unsigned int i = 0; i != tmpPhi.size(); ++i) {
            DemotePHIToStack(tmpPhi.at(i),f->begin()->getTerminator());
        }
    }while(tmpReg.size() != 0 || tmpPhi.size() != 0);
}

std::string readAnnotate(Function *f) {
    std::string annotation = "";
    
    // Get annotation variable
    GlobalVariable *glob = f->getParent()->getGlobalVariable("llvm.global.annotations");
    if (glob != NULL) {
        // Get the array
        if (ConstantArray *ca = dyn_cast<ConstantArray>(glob->getInitializer())) {
            for (unsigned i = 0; i < ca->User::getNumOperands(); ++i) {
                // Get the struct
                if (ConstantStruct *structAn = dyn_cast<ConstantStruct>(ca->User::getOperand(i))) {
                    if (ConstantExpr *expr = dyn_cast<ConstantExpr>(structAn->getOperand(0))) {
                        // If it's a bitcast we can check if the annotation is concerning
                        // the current function
                        if (expr->getOpcode() == Instruction::BitCast && expr->getOperand(0) == f) {
                            ConstantExpr *note = cast<ConstantExpr>(structAn->getOperand(1));
                            // If it's a GetElementPtr, that means we found the variable 
                            // containing the annotations
                            if (note->getOpcode() == Instruction::GetElementPtr) {
                                if (GlobalVariable *annoteStr = dyn_cast<GlobalVariable>(note->getOperand(0))) {
                                    if (ConstantDataSequential *data = dyn_cast<ConstantDataSequential>(annoteStr->getInitializer())) {
                                        if (data->isString()) {
                                            annotation += data->getAsString().lower() + " ";
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return annotation;
}

bool toObfuscate(bool flag, Function *f, std::string attribute) {
    std::string attr = attribute;
    std::string attrNo = "no" + attr;
    
    // Chcek if declaration
    if (f->isDeclaration()) {
        return false;
    }
    
    // Check external linkage
    if (f->hasAvailableExternallyLinkage() != 0) {
        return false;
    }
    
    // We have to check the nofla flag first
    // Because .find("fla") is true for a string like "fla" or
    // "nofla"
    if (readAnnotate(f).find(attrNo) != std::string::npos) {
        return false;
    }
    
    // If fla annotations
    if (readAnnotate(f).find(attr) != std::string::npos) {
        return true;
    }
    
    // If fla flag is set
    if (flag == true) {
        return true;
    }
    return false;
}



using namespace llvm;


// Flags for obfuscation
static cl::opt<bool> Flattening("fla", cl::init(false),
                                cl::desc("Enable the flattening pass"));

static cl::opt<bool> BogusControlFlow("bcf", cl::init(false),
                                      cl::desc("Enable bogus control flow"));

static cl::opt<bool> Substitution("sub", cl::init(false),
                                  cl::desc("Enable instruction substitutions"));

static cl::opt<std::string> AesSeed("aesSeed", cl::init(""),
                                    cl::desc("seed for the AES-CTR PRNG"));

static cl::opt<bool> Split("split", cl::init(false),
                           cl::desc("Enable basic block splitting"));



PreservedAnalyses LLVMObfuscationPass::run(Function &F, FunctionAnalysisManager &AM)
{
    printf("hello obfuscation!!!\n");
    FunctionPass* s = (FunctionPass*)createSubstitution(Substitution);
    s->runOnFunction(F);
    FunctionPass* b = (FunctionPass*)createBogus(BogusControlFlow);
    b->runOnFunction(F);
    FunctionPass* f = (FunctionPass*)createFlattening(Flattening);
    f->runOnFunction(F);
    return PreservedAnalyses::all();
}

