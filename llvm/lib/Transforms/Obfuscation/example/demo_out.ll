; ModuleID = '/Users/lee/Desktop/Compiler/Learn_LLVM_12/Learn-LLVM-12/Chapter08/demo.ll'
source_filename = "/Users/lee/Desktop/Compiler/Learn_LLVM_12/Learn-LLVM-12/Chapter08/demo.ll"

define internal i32 @func() {
  %i.addr = alloca i32, align 4
  %temp.addr1 = alloca i32, align 4
  store i32 2, i32* %i.addr, align 4
  store i32 1, i32* %temp.addr1, align 4
  %current_i = load i32, i32* %i.addr, align 4
  %temp = load i32, i32* %temp.addr1, align 4
  %1 = sub i32 0, %temp
  %2 = sub i32 %current_i, %1
  %i_plus_one = add i32 %current_i, %temp
  ret i32 0
}

define dso_local i32 @main() {
  %1 = call i32 @func()
  ret i32 %1
}
