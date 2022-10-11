; ModuleID = '/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/demo.ll'
source_filename = "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/demo.ll"

@.str = private unnamed_addr constant [13 x i8] c"hello world\0A\00"

; Function Attrs: nounwind
declare i32 @puts(i8* nocapture) #0

define internal i32 @func() {
entry:
  %.reg2mem = alloca i32, align 4
  %retval = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 1, i32* %a, align 4
  store i32 0, i32* %b, align 4
  %0 = load i32, i32* %a, align 4
  store i32 %0, i32* %.reg2mem, align 4
  %switchVar = alloca i32, align 4
  store i32 -1828813787, i32* %switchVar, align 4
  br label %loopEntry

loopEntry:                                        ; preds = %entry, %loopEnd
  %switchVar1 = load i32, i32* %switchVar, align 4
  switch i32 %switchVar1, label %switchDefault [
    i32 -1828813787, label %first
    i32 1333979598, label %if.then
    i32 194786863, label %if.else
    i32 -1325694551, label %return
  ]

switchDefault:                                    ; preds = %loopEntry
  br label %loopEnd

first:                                            ; preds = %loopEntry
  %.reload = load volatile i32, i32* %.reg2mem, align 4
  %cmp = icmp eq i32 %.reload, 0
  %1 = select i1 %cmp, i32 1333979598, i32 194786863
  store i32 %1, i32* %switchVar, align 4
  br label %loopEnd

if.then:                                          ; preds = %loopEntry
  store i32 1, i32* %retval, align 4
  store i32 -1325694551, i32* %switchVar, align 4
  br label %loopEnd

if.else:                                          ; preds = %loopEntry
  store i32 10, i32* %retval, align 4
  store i32 -1325694551, i32* %switchVar, align 4
  br label %loopEnd

return:                                           ; preds = %loopEntry
  %2 = load i32, i32* %retval, align 4
  ret i32 %2

loopEnd:                                          ; preds = %if.else, %if.then, %first, %switchDefault
  br label %loopEntry
}

define dso_local i32 @main() {
  %1 = call i32 @func()
  %cast210 = getelementptr [13 x i8], [13 x i8]* @.str, i64 0, i64 0
  %2 = call i32 @puts(i8* %cast210)
  ret i32 %1
}

attributes #0 = { nounwind }
