
#include "FGSpaceElevator.hh"

namespace FG {

  std::string SpaceElevator::objtypename("Build_SpaceElevator_C");

  SpaceElevator::SpaceElevator(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::SpaceElevator, _reader, _fgoh){
    c_inputs.resize(6);
    c_outputs.resize(0);
    registerComponent("Input1", c_inputs[0]);
    registerComponent("Input2", c_inputs[1]);
    registerComponent("InPut3", c_inputs[2]);
    registerComponent("Input4", c_inputs[3]);
    registerComponent("Input5", c_inputs[4]);
    registerComponent("Input6", c_inputs[5]);
  }

  SpaceElevator::~SpaceElevator() {
  }

}
