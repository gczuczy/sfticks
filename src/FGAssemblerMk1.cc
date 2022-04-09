
#include "FGAssemblerMk1.hh"

namespace FG {

  std::string AssemblerMk1::objtypename("Build_AssemblerMk1_C");

  AssemblerMk1::AssemblerMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::AssemblerMk1, _reader, _fgoh){
    c_inputs.resize(2);
    c_outputs.resize(1);
    registerComponent("Input0", c_inputs[0]);
    registerComponent("Input1", c_inputs[1]);
    registerComponent("Output0", c_outputs[0]);
  }

  AssemblerMk1::~AssemblerMk1() {
  }

}
