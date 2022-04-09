
#include "FGConstructorMk1.hh"
#include "Exception.hh"
#include "Trace.hh"

#include <cassert>

namespace FG {

  std::string ConstructorMk1::objtypename("Build_ConstructorMk1_C");

  ConstructorMk1::ConstructorMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::ConstructorMk1, _reader, _fgoh) {
    c_inputs.resize(1);
    c_outputs.resize(1);
    registerComponent("Input0", c_inputs[0]);
    registerComponent("Output0", c_outputs[0]);
  }

  ConstructorMk1::~ConstructorMk1() {
  }

}
