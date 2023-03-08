#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

struct Sheap : public ModulePass {
	static char ID;
	Sheap() : ModulePass(ID) {}
	bool runOnFunction(Function &F);
	bool runOnCall(Instruction &I);
	bool runOnBlock(BasicBlock &B);
	bool runOnInstruction(Instruction &I);
	bool runOnModule(Module &M) override;
};

char Sheap::ID = 0;
static RegisterPass<Sheap> X("sheap", "Sheap Pass");

bool Sheap::runOnCall(Instruction &I)
{
	CallInst* ci = dyn_cast<CallInst>(&I);
	Function *fn = ci->getCalledFunction();
	StringRef name = fn->getName();

	//errs() << "\t" << name << " : " << ci->getArgOperand(0) << "\n";
	errs() << "\t" << name << "\n";
	for (unsigned i = 0; i < ci->arg_size(); i++) {
		errs() << "\t" << *(ci->getArgOperand(i)) << "\n";
	}

	if (name == "malloc") {
		/* taint return value */
	} else if (name == "realloc") {
		/* taint return value */
		/* taint first parameter as possibly free */
	} else if (name == "calloc") {
		/* taint return value */
	} else if (name == "free") {
		/* taint first parameter as definitely free */
	} else {
		Sheap::runOnFunction(*fn);
	}

	return false;
}

bool Sheap::runOnInstruction(Instruction &I)
{
	switch (I.getOpcode()) {
	case Instruction::Load:
		//runOnLoad(I);
		break;
	case Instruction::Store:
		//runOnStore(I);
		break;
	case Instruction::Call:
		runOnCall(I);
		break;
	}
	return false;
}

bool Sheap::runOnFunction(Function &F)
{
	errs() << "Analyzing function " << F.getName() << "\n";
	int i = 0;
	for (BasicBlock &B : F) {
		errs() << "block " << i << "\n";
		runOnBlock(B);
		i++;
	}
	return false;
}

bool Sheap::runOnBlock(BasicBlock &B)
{
	int j = 0;
	for (Instruction &I : B) {
		errs() << j << ":\t";
		I.print(errs());
		errs() << "\n";
		runOnInstruction(I);
		j++;
	}
	return false;
}

bool Sheap::runOnModule(Module &M)
{
	errs() << "Sheap: ";
	errs().write_escaped(M.getName()) << '\n';
	auto main = M.getFunction("main");
	if (!main) {
		errs() << "main() not found, can't complete analysis\n";
		return false;
	}
	runOnFunction(*main);
	return false;
}
