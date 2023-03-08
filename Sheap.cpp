#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/CallGraphSCCPass.h"
#include "llvm/Analysis/CallGraph.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

struct Sheap : public CallGraphSCCPass {
	static char ID;
	Sheap() : CallGraphSCCPass(ID) {}
	bool runOnFunction(Function &F); // override;
	bool runOnModule(Module &M); // override;
	bool runOnSCC(CallGraphSCC &C) override;
};

char Sheap::ID = 0;
static RegisterPass<Sheap> X("sheap", "Sheap Pass");

bool Sheap::runOnFunction(Function &F) {
	errs() << "Sheap: ";
	errs().write_escaped(F.getName()) << '\n';
	return false;
}

bool Sheap::runOnModule(Module &M) {
	errs() << "Sheap: ";
	errs().write_escaped(M.getName()) << '\n';
	return false;
}

bool Sheap::runOnSCC(CallGraphSCC &C) {
	errs() << "Sheap: ";
	C.getCallGraph().print(errs());
	return false;
}
