
#include "FGFoundryMk1.hh"

namespace FG {

  std::string FoundryMk1::objtypename("Build_FoundryMk1_C");

  FoundryMk1::FoundryMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::FoundryMk1, _reader, _fgoh){
    c_inputs.resize(2);
    c_outputs.resize(1);
    registerComponent("Input0", c_inputs[0]);
    registerComponent("Input1", c_inputs[1]);
    registerComponent("Output2", c_outputs[0]);
  }

  FoundryMk1::~FoundryMk1() {
  }

}
