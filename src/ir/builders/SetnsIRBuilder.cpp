#include <iostream>
#include <sstream>
#include <stdexcept>

#include "SetnsIRBuilder.h"
#include "Registers.h"
#include "SMT2Lib.h"
#include "SymbolicElement.h"


SetnsIRBuilder::SetnsIRBuilder(uint64_t address, const std::string &disassembly):
  BaseIRBuilder(address, disassembly) {
}


void SetnsIRBuilder::imm(AnalysisProcessor &ap, Inst &inst) const {
  OneOperandTemplate::stop(this->disas);
}


void SetnsIRBuilder::reg(AnalysisProcessor &ap, Inst &inst) const {
  SymbolicElement   *se;
  std::stringstream expr, reg1e, sf;
  uint64_t          reg     = std::get<1>(this->operands[0]);
  uint64_t          regSize = std::get<2>(this->operands[0]);
  uint64_t          symReg  = ap.getRegSymbolicID(reg);
  uint64_t          symSF   = ap.getRegSymbolicID(ID_SF);

  /* Create the SMT semantic */
  if (symSF != UNSET)
    sf << "#" << std::dec << symSF;
  else
    sf << smt2lib::bv(ap.getFlagValue(ID_SF), 1);

  /* Create the reg1 SMT semantic */
  if (symReg != UNSET)
    reg1e << smt2lib::extract(regSize, "#" + std::to_string(symReg));
  else
    reg1e << smt2lib::bv(ap.getRegisterValue(reg), regSize * REG_SIZE);

  /* Finale expr */
  expr << smt2lib::ite(
            smt2lib::equal(
              sf.str(),
              smt2lib::bvfalse()),
            smt2lib::bv(1, 8),
            smt2lib::bv(0, 8));

  /* Create the symbolic element */
  se = ap.createRegSE(expr, reg);

  /* Apply the taint via the concretization */
  if (ap.getFlagValue(ID_SF) == 0)
    ap.assignmentSpreadTaintRegReg(se, reg, ID_SF);

  /* Add the symbolic element to the current inst */
  inst.addElement(se);
}


void SetnsIRBuilder::mem(AnalysisProcessor &ap, Inst &inst) const {
  SymbolicElement   *se;
  std::stringstream expr, mem1e, sf;
  uint64_t          mem     = std::get<1>(this->operands[0]);
  uint64_t          memSize = std::get<2>(this->operands[0]);
  uint64_t          symMem  = ap.getMemSymbolicID(mem);
  uint64_t          symSF   = ap.getRegSymbolicID(ID_SF);

  /* Create the SMT semantic */
  if (symSF != UNSET)
    sf << "#" << std::dec << symSF;
  else
    sf << smt2lib::bv(ap.getFlagValue(ID_SF), 1);

  /* Create the reg1 SMT semantic */
  if (symMem != UNSET)
    mem1e << smt2lib::extract(memSize, "#" + std::to_string(symMem));
  else
    mem1e << smt2lib::bv(ap.getMemValue(mem, memSize), memSize * REG_SIZE);

  /* Finale expr */
  expr << smt2lib::ite(
            smt2lib::equal(
              sf.str(),
              smt2lib::bvfalse()),
            smt2lib::bv(1, 8),
            smt2lib::bv(0, 8));

  /* Create the symbolic element */
  se = ap.createMemSE(expr, mem);

  /* Apply the taint via the concretization */
  if (ap.getFlagValue(ID_SF) == 0)
    ap.assignmentSpreadTaintMemReg(se, mem, ID_SF, memSize);

  /* Add the symbolic element to the current inst */
  inst.addElement(se);
}


void SetnsIRBuilder::none(AnalysisProcessor &ap, Inst &inst) const {
  OneOperandTemplate::stop(this->disas);
}


Inst *SetnsIRBuilder::process(AnalysisProcessor &ap) const {
  this->checkSetup();

  Inst *inst = new Inst(ap.getThreadID(), this->address, this->disas);

  try {
    this->templateMethod(ap, *inst, this->operands, "SETNS");
    ap.incNumberOfExpressions(inst->numberOfElements()); /* Used for statistics */
    inst->addElement(ControlFlow::rip(ap, this->nextAddress));
  }
  catch (std::exception &e) {
    delete inst;
    throw;
  }

  return inst;
}
