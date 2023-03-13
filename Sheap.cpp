#include <map>

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/Constants.h"

using namespace llvm;

enum class Taint {
	None,
	Dynamic,
	PossiblyFree,
	Free,
};

struct Sheap : public ModulePass {
	static char ID;
	static std::map<unsigned, Taint> Taints;
	Sheap() : ModulePass(ID) { }
	void setTaint(Value &V, Taint t);
	Taint getTaint(Value &V);
	bool runOnFunction(Function &F);
	bool runOnLoad(Instruction &I);
	bool runOnStore(Instruction &I);
	bool runOnCall(Instruction &I);
	bool runOnBlock(BasicBlock &B);
	bool runOnInstruction(Instruction &I);
	bool runOnModule(Module &M) override;
};

char Sheap::ID = 0;
std::map<unsigned, Taint> Sheap::Taints;
static RegisterPass<Sheap> X("sheap", "Sheap Pass");

llvm::raw_ostream& operator<<(llvm::raw_ostream &os, Taint T)
{
	switch (T) {
	case Taint::None:		return os << "None";
	case Taint::Dynamic:		return os << "Dynamic";
	case Taint::PossiblyFree:	return os << "PossiblyFree";
	case Taint::Free:		return os << "Free";
	}
	return os << "???";
}

void Sheap::setTaint(Value &V, Taint T)
{
	errs() << "Tainting " << V.getValueID() << ": " << T << "\n";
	Taints[V.getValueID()] = T;
}

Taint Sheap::getTaint(Value &V)
{
	auto T = Taints[V.getValueID()];
	errs() << "Reading " << V.getValueID() << ": " << T << "\n";
	return T;
}

bool Sheap::runOnCall(Instruction &I)
{
	CallInst* ci = dyn_cast<CallInst>(&I);
	Function *fn = ci->getCalledFunction();
	StringRef name = fn->getName();

	if (name == "malloc") {
		/* taint return value */
		errs() << "MALLOC: " << ci->getValueID() << "\n";
		setTaint(*ci, Taint::Dynamic);

	} else if (name == "realloc") {
		/* taint first parameter as possibly free unless it goes to return value */
		/* taint return value */

	} else if (name == "calloc") {
		/* taint return value */

	} else if (name == "free") {
		/* taint first parameter as definitely free */
		auto addr = ci->getArgOperand(0);
		errs() << "FREE: " << addr->getValueID() << "\n";
		errs() << getTaint(*addr) << "\n";
		setTaint(*addr, Taint::Free);

	} else {
		Sheap::runOnFunction(*fn);
	}

	return false;
}

bool Sheap::runOnLoad(Instruction &I)
{
	LoadInst *li = dyn_cast<LoadInst>(&I);
	auto ptr = li->getPointerOperand();
	errs() << ptr->getValueID() << " = " << li->getValueID() << "\n";
	setTaint(*li, getTaint(*ptr));
	return false;
}

bool Sheap::runOnStore(Instruction &I)
{
	StoreInst* si = dyn_cast<StoreInst>(&I);
	auto val = si->getValueOperand();
	auto ptr = si->getPointerOperand();
	errs() << ptr->getValueID() << " = " << si->getValueID() << " = " << val->getValueID() << "\n";
	setTaint(*ptr, getTaint(*val));
	return false;
}

bool Sheap::runOnInstruction(Instruction &I)
{
	switch (I.getOpcode()) {
	case Instruction::Alloca: {
			AllocaInst *ai = dyn_cast<AllocaInst>(&I);
			errs() << ai->getValueID() << "\n";
			if (ai->hasName()) {
				errs() << ai->getName() << "\n";
			}
			auto VN = ai->getValueName();
			if (VN != nullptr) {
				errs() << VN->first() << "\n";
			}
		}
		break;
	case Instruction::Load:
		runOnLoad(I);
		break;
	case Instruction::Store:
		runOnStore(I);
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

		errs() << "\n";
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
