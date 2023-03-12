#!/bin/sh

LLVM_VERSION="-13"

while [ $# -gt 0 ]; do
	"clang${LLVM_VERSION}" "$1" -S -emit-llvm -o - | "opt${LLVM_VERSION}" -enable-new-pm=0 -load "$(dirname $0)/Sheap.so" -sheap
	shift
done
