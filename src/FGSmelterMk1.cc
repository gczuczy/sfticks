
#include "FGSmelterMk1.hh"

namespace FG {

  std::string SmelterMk1::objtypename("Build_SmelterMk1_C");

  SmelterMk1::SmelterMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::SmelterMk1, _reader, _fgoh){
    c_inputs.resize(1);
    c_outputs.resize(1);
    registerComponent("Input0", c_inputs[0]);
    registerComponent("Output2", c_outputs[0]);
  }

  SmelterMk1::~SmelterMk1() {
  }

}
