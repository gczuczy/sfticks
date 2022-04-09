
#include "FGManufacturerMk1.hh"

namespace FG {

  std::string ManufacturerMk1::objtypename("Build_ManufacturerMk1_C");

  ManufacturerMk1::ManufacturerMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::ManufacturerMk1, _reader, _fgoh) {
    c_inputs.resize(4);
    c_outputs.resize(1);
    registerComponent("Input0", c_inputs[0]);
    registerComponent("Input1", c_inputs[1]);
    registerComponent("Input2", c_inputs[2]);
    registerComponent("InPut3", c_inputs[3]);
    registerComponent("Output0", c_outputs[0]);
  }

  ManufacturerMk1::~ManufacturerMk1() {
  }

}
