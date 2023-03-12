#!/bin/sh

LLVM_PATH=/usr/local/bin/
LLVM_VERSION=

while [ $# -gt 0 ]; do
	"${LLVM_PATH}clang${LLVM_VERSION}" "$1" -g -S -emit-llvm -o - | "${LLVM_PATH}opt${LLVM_VERSION}" -enable-new-pm=0 -f -load "$(dirname $0)/Sheap.so" -sheap
	shift
done
