
#include "FG/ConveyorLiftMk1.hh"

namespace FG {

  std::string ConveyorLiftMk1::objtypename("Build_ConveyorLiftMk1_C");

  ConveyorLiftMk1::ConveyorLiftMk1(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorLift(EntityType::ConveyorLiftMk1, _reader, _fgoh, 60){
  }

  ConveyorLiftMk1::~ConveyorLiftMk1() {
  }

}
