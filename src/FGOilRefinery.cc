
#include "FGOilRefinery.hh"
#include "FloatProperty.hh"

namespace FG {

  std::string OilRefinery::objtypename("Build_OilRefinery_C");

  OilRefinery::OilRefinery(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::OilRefinery, _reader, _fgoh) {
    c_inputs.resize(1);
    c_outputs.resize(1);
    registerComponent("Input0", c_inputs[0]);
    registerComponent("Output1", c_outputs[0]);
  }

  OilRefinery::~OilRefinery() {
  }

}
