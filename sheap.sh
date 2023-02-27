#!/bin/sh
opt -enable-new-pm=0 -load ~/src/llvm-build/lib/LLVMSheap.so -sheap "$@"
