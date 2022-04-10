
#include "FGAssemblerMk1.hh"

namespace FG {

  std::string AssemblerMk1::objtypename("Build_AssemblerMk1_C");

  AssemblerMk1::AssemblerMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::AssemblerMk1, _reader, _fgoh){

    defineInputs({"Input0", "Input1"});
    defineOutputs({"Output0"});
  }

  AssemblerMk1::~AssemblerMk1() {
  }

}
