.POSIX:

LLVM_VERSION=
LLVM_PATH=/usr/local/bin/

CXX=$(LLVM_PATH)clang++$(LLVM_VERSION)
LD=$(LLVM_PATH)clang++$(LLVM_VERSION)
CXXFLAGS=-std=c++17 -Wall -fpic -fPIC $$($(LLVM_PATH)llvm-config$(LLVM_VERSION) --cxxflags)
LDFLAGS=-shared $$($(LLVM_PATH)llvm-config$(LLVM_VERSION) --ldflags)
SHEAP_OBJS=Sheap.o

all: Sheap.so

Sheap.so: $(SHEAP_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(SHEAP_OBJS)

Sheap.o: Sheap.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $$(cat .gitignore)
