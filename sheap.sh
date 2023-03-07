#!/bin/sh
opt -enable-new-pm=0 -load "$(dirname $0)/Sheap.so" -sheap "$@"
