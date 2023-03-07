.POSIX:

.SUFFIXES: .c .ll

all: double-free.ll tricky-free.ll

.c.ll:
	clang $< -S -emit-llvm -o $@
