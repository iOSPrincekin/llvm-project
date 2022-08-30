define internal i32 @func() {
    %i.addr = alloca i32
    %temp.addr1 = alloca i32
    store i32 2, i32* %i.addr
    store i32 1, i32 * %temp.addr1
    %current_i  = load i32, i32* %i.addr
    %temp       = load i32, i32* %temp.addr1
    %i_plus_one = add i32 %current_i,%temp

  ret i32 0
}

define dso_local i32 @main() {
  %1 = call i32 @func()
  ret i32 %1
}

