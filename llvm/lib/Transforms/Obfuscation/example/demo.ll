@.str = private unnamed_addr constant [13 x i8] c"hello world\0A\00"

; External declaretion of the puts function
declare i32 @puts(i8 * nocapture) nounwind

define internal i32 @func() {
entry:
    %retval = alloca i32, align 4
    %a = alloca i32,align 4
    %b = alloca i32,align 4
    store i32 0,i32* %retval
    store i32 1,i32* %a
    store i32 0,i32* %b
    %0 = load i32,i32* %a,align 4
    %cmp = icmp eq i32 %0,0
    br i1 %cmp,label %if.then,label %if.else
if.then:
    store i32 1,i32 * %retval
    br label %return
if.else:
    store i32 10,i32* %retval
    br label %return
return:
    %1 = load i32,i32* %retval
    ret i32 %1
}

define dso_local i32 @main() {
  %1 = call i32 @func()

; Convert [13 * i8]* to i8*...
  %cast210 = getelementptr [13 x i8],[13 x i8]* @.str, i64 0,i64 0

; Call puts function to write out the string to stdout
  call i32 @puts(i8* %cast210);

  ret i32 %1
}

