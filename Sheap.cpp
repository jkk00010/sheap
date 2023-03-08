#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/CallGraphSCCPass.h"
#include "llvm/Analysis/CallGraph.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

struct Sheap : public ModulePass {
	static char ID;
	Sheap() : ModulePass(ID) {}
	bool runOnFunction(Function &F); // override;
	bool runOnModule(Module &M) override;
	bool runOnSCC(CallGraphSCC &C);// override;
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
	auto main = M.getFunction("main");
	if (!main) {
		errs() << "main() not found, can't complete analysis\n";
		return false;
	}
	//main->print(errs());
	int i = 0;
	//for (auto block = main->front(); block != main->back(); block++) {
	//for (Function::iterator b = main->begin(), be = main->end(); b != be; b++) {
	for (BasicBlock &block : *main) {
		errs() << "block " << i << "\n";
		//block.print(errs());
		i++;

		int j = 0;
		for (Instruction &inst : block) {
			// Instruction::Load
			// Instruction::Store
			if (inst.getOpcode() == Instruction::Call || true) {
				errs() << "Instruction " << j << "\n";
				errs() << inst << "\n";
				errs() << inst.getOpcode() << "\n";
				errs() << inst.getOpcodeName() << "\n";
			}
			j++;
		}
	}
	return false;
}

bool Sheap::runOnSCC(CallGraphSCC &C) {
	errs() << "Sheap: ";
	//auto cg = CallGraph(C.getCallGraph());
	//C.getCallGraph().print(errs());
	for (auto i = C.begin(); i < C.end(); i++) {
		//errs() << i << "\n";
		errs() << "iterating\n";
	}
	return false;
}
