#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

struct Sheap : public FunctionPass {
	static char ID;
	Sheap() : FunctionPass(ID) {}
	bool runOnFunction(Function &F) override;
};

char Sheap::ID = 0;
static RegisterPass<Sheap> X("sheap", "Sheap Pass");

bool Sheap::runOnFunction(Function &F) {
	errs() << "Sheap: ";
	errs().write_escaped(F.getName()) << '\n';
	return false;
}
