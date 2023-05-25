# The LLVM Compiler Infrastructure

This directory and its sub-directories contain source code for LLVM,
a toolkit for the construction of highly optimized compilers,
optimizers, and run-time environments.

The README briefly describes how to get started with building LLVM.
For more information on how to contribute to the LLVM project, please
take a look at the
[Contributing to LLVM](https://llvm.org/docs/Contributing.html) guide.

## Getting Started with the LLVM System

Taken from https://llvm.org/docs/GettingStarted.html.

### Overview

Welcome to the LLVM project!

The LLVM project has multiple components. The core of the project is
itself called "LLVM". This contains all of the tools, libraries, and header
files needed to process intermediate representations and converts it into
object files.  Tools include an assembler, disassembler, bitcode analyzer, and
bitcode optimizer.  It also contains basic regression tests.

C-like languages use the [Clang](http://clang.llvm.org/) front end.  This
component compiles C, C++, Objective-C, and Objective-C++ code into LLVM bitcode
-- and from there into object files, using LLVM.

Other components include:
the [libc++ C++ standard library](https://libcxx.llvm.org),
the [LLD linker](https://lld.llvm.org), and more.

### Getting the Source Code and Building LLVM

The LLVM Getting Started documentation may be out of date.  The [Clang
Getting Started](http://clang.llvm.org/get_started.html) page might have more
accurate information.

This is an example work-flow and configuration to get and build the LLVM source:

1. Checkout LLVM (including related sub-projects like Clang):

     * ``git clone https://github.com/llvm/llvm-project.git``

     * Or, on windows, ``git clone --config core.autocrlf=false
    https://github.com/llvm/llvm-project.git``

2. Configure and build LLVM and Clang:

     * ``cd llvm-project``

     * ``mkdir build``

     * ``cd build``

     * ``cmake -G <generator> [options] ../llvm``

        Some common build system generators are:

        * ``Ninja`` --- for generating [Ninja](https://ninja-build.org)
          build files. Most llvm developers use Ninja.
        * ``Unix Makefiles`` --- for generating make-compatible parallel makefiles.
        * ``Visual Studio`` --- for generating Visual Studio projects and
          solutions.
        * ``Xcode`` --- for generating Xcode projects.

        Some Common options:

        * ``-DLLVM_ENABLE_PROJECTS='...'`` --- semicolon-separated list of the LLVM
          sub-projects you'd like to additionally build. Can include any of: clang,
          clang-tools-extra, libcxx, libcxxabi, libunwind, lldb, compiler-rt, lld,
          polly, or debuginfo-tests.

          For example, to build LLVM, Clang, libcxx, and libcxxabi, use
          ``-DLLVM_ENABLE_PROJECTS="clang;libcxx;libcxxabi"``.

        * ``-DCMAKE_INSTALL_PREFIX=directory`` --- Specify for *directory* the full
          path name of where you want the LLVM tools and libraries to be installed
          (default ``/usr/local``).

        * ``-DCMAKE_BUILD_TYPE=type`` --- Valid options for *type* are Debug,
          Release, RelWithDebInfo, and MinSizeRel. Default is Debug.

        * ``-DLLVM_ENABLE_ASSERTIONS=On`` --- Compile with assertion checks enabled
          (default is Yes for Debug builds, No for all other build types).

      * ``cmake --build . [-- [options] <target>]`` or your build system specified above
        directly.

        * The default target (i.e. ``ninja`` or ``make``) will build all of LLVM.

        * The ``check-all`` target (i.e. ``ninja check-all``) will run the
          regression tests to ensure everything is in working order.

        * CMake will generate targets for each tool and library, and most
          LLVM sub-projects generate their own ``check-<project>`` target.

        * Running a serial build will be **slow**.  To improve speed, try running a
          parallel build.  That's done by default in Ninja; for ``make``, use the option
          ``-j NNN``, where ``NNN`` is the number of parallel jobs, e.g. the number of
          CPUs you have.

      * For more information see [CMake](https://llvm.org/docs/CMake.html)

Consult the
[Getting Started with LLVM](https://llvm.org/docs/GettingStarted.html#getting-started-with-llvm)
page for detailed information on configuring and compiling LLVM. You can visit
[Directory Layout](https://llvm.org/docs/GettingStarted.html#directory-layout)
to learn about the layout of the source code tree.



## 1.4 opt 调试参数 （可以调试 ollvm）

-S -fla -debug-only=flattening --passes="obfuscation"  /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/demo.ll -o /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/demo_out.ll

## 1.5 clang调试参数

-S -emit-llvm /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.c -o  /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.ll


SDKROOT = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk

## 1.6 lldb 调试 obfuscation ,调试 clang
### 1.首先使用 Xcode的Debug模式下 clang -### 输出参数

-### -S -emit-llvm -mllvm -sub -mllvm -bcf -mllvm -fla /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.c -o  /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.ll

获得

clang version 12.0.0 (git@github.com:iOSPrincekin/llvm-project.git f460958227210abde112d224b8c156555321c34b)
Target: x86_64-apple-darwin21.5.0
Thread model: posix
InstalledDir: /Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/bin
 (in-process)
 "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/bin/clang" "-cc1" "-triple" "x86_64-apple-macosx12.0.0" "-Wundef-prefix=TARGET_OS_" "-Werror=undef-prefix" "-Wdeprecated-objc-isa-usage" "-Werror=deprecated-objc-isa-usage" "-emit-llvm" "-disable-free" "-main-file-name" "main.c" "-mrelocation-model" "pic" "-pic-level" "2" "-mframe-pointer=all" "-fno-rounding-math" "-munwind-tables" "-target-sdk-version=12.3" "-fcompatibility-qualified-id-block-type-checking" "-fvisibility-inlines-hidden-static-local-var" "-target-cpu" "penryn" "-tune-cpu" "generic" "-debugger-tuning=lldb" "-target-linker-version" "762" "-resource-dir" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/lib/clang/12.0.0" "-isysroot" "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk" "-internal-isystem" "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk/usr/local/include" "-internal-isystem" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/lib/clang/12.0.0/include" "-internal-externc-isystem" "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk/usr/include" "-fdebug-compilation-dir" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/bin" "-ferror-limit" "19" "-stack-protector" "1" "-fblocks" "-fencode-extended-block-signature" "-fregister-global-dtors-with-atexit" "-fgnuc-version=4.2.1" "-fmax-type-align=16" "-mllvm" "-sub" "-mllvm" "-bcf" "-mllvm" "-fla" "-o" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.ll" "-x" "c" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.c"
### 2.使用新的参数，重新运行Xcode Debug模式下的clang

参数

"-cc1" "-triple" "x86_64-apple-macosx12.0.0" "-Wundef-prefix=TARGET_OS_" "-Werror=undef-prefix" "-Wdeprecated-objc-isa-usage" "-Werror=deprecated-objc-isa-usage" "-emit-llvm" "-disable-free" "-main-file-name" "main.c" "-mrelocation-model" "pic" "-pic-level" "2" "-mframe-pointer=all" "-fno-rounding-math" "-munwind-tables" "-target-sdk-version=12.3" "-fcompatibility-qualified-id-block-type-checking" "-fvisibility-inlines-hidden-static-local-var" "-target-cpu" "penryn" "-tune-cpu" "generic" "-debugger-tuning=lldb" "-target-linker-version" "762" "-resource-dir" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/lib/clang/12.0.0" "-isysroot" "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk" "-internal-isystem" "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk/usr/local/include" "-internal-isystem" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/lib/clang/12.0.0/include" "-internal-externc-isystem" "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.3.sdk/usr/include" "-fdebug-compilation-dir" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvmorg-Xcode/Debug/bin" "-ferror-limit" "19" "-stack-protector" "1" "-fblocks" "-fencode-extended-block-signature" "-fregister-global-dtors-with-atexit" "-fgnuc-version=4.2.1" "-fmax-type-align=16" "-mllvm" "-sub" "-mllvm" "-bcf" "-mllvm" "-fla" "-o" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.ll" "-x" "c" "/Users/lee/Desktop/Compiler/Learn_LLVM_12/llvm-project/llvm/lib/Transforms/Obfuscation/example/main.c"

## 1.7 解决clang 调试时，LLVM_DEBUG(dbgs() 不输出log的问题，-mllvm -debug、-mllvm -debug-only=isel 必须加 -mllvm

参数

--target=riscv32 -mllvm -debug -O2 /Users/lee/Desktop/Compiler/Learn_LLVM_12/Learn-LLVM-12/Chapter09/tblgen/LLVM笔记/LLVM笔记\(10\)-指令选择\(二\)lowering/1.c  -S -mllvm -view-dag-combine1-dags=true
