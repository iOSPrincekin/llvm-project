add_llvm_component_library(LLVMDummyInfo
  DummyTargetInfo.cpp

  LINK_COMPONENTS
  Support

  ADD_TO_COMPONENT
  Dummy
  )
