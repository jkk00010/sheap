.POSIX:

all: Sheap.so

Sheap.so: Sheap.cpp
	clang++ -std=c++17 $$(llvm-config --cxxflags --ldflags) -fpic -Wall -shared -fPIC Sheap.cpp -o $@
