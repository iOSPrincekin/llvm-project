add_llvm_component_library(LLVMObfuscation
  BogusControlFlow.cpp
  CryptoUtils.cpp
  Flattening.cpp
  SplitBasicBlocks.cpp
  Substitution.cpp
  Utils.cpp
  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )
