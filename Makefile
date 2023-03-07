.POSIX:

CXX=clang++
LD=clang++
CXXFLAGS=-std=c++17 -Wall -fpic -fPIC $$(llvm-config --cxxflags)
LDFLAGS=-shared $$(llvm-config --ldflags)
SHEAP_OBJS=Sheap.o

all: Sheap.so

Sheap.so: $(SHEAP_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(SHEAP_OBJS)

Sheap.o: Sheap.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $$(cat .gitignore)
