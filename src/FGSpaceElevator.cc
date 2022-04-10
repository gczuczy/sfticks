
#include "FGSpaceElevator.hh"

namespace FG {

  std::string SpaceElevator::objtypename("Build_SpaceElevator_C");

  SpaceElevator::SpaceElevator(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::SpaceElevator, _reader, _fgoh){
    defineInputs({"Input1", "Input2", "InPut3", "Input4", "Input5", "Input6"});
  }

  SpaceElevator::~SpaceElevator() {
  }

}
