#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
	struct Sheap : public FunctionPass {
		static char ID;
		Sheap() : FunctionPass(ID) {}

		bool runOnFunction(Function &F) override {
			errs() << "Sheap: ";
			errs().write_escaped(F.getName()) << '\n';
			return false;
		}
	};
}

char Sheap::ID = 0;
static RegisterPass<Sheap> X("sheap", "Sheap Pass");
