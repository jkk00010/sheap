.POSIX:

LLVM_VERSION=-13

CXX=clang++$(LLVM_VERSION)
LD=clang++$(LLVM_VERSION)
CXXFLAGS=-std=c++17 -Wall -fpic -fPIC $$(llvm-config$(LLVM_VERSION) --cxxflags)
LDFLAGS=-shared $$(llvm-config$(LLVM_VERSION) --ldflags)
SHEAP_OBJS=Sheap.o

all: Sheap.so

Sheap.so: $(SHEAP_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(SHEAP_OBJS)

Sheap.o: Sheap.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $$(cat .gitignore)
