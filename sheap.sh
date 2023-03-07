#!/bin/sh

while [ $# -gt 0 ]; do
	clang "$1" -S -emit-llvm -o - | opt -enable-new-pm=0 -load "$(dirname $0)/Sheap.so" -sheap
	shift
done
