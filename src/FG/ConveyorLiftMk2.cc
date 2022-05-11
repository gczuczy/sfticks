
#include "FG/ConveyorLiftMk2.hh"

namespace FG {

  std::string ConveyorLiftMk2::objtypename("Build_ConveyorLiftMk2_C");

  ConveyorLiftMk2::ConveyorLiftMk2(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorLift(EntityType::ConveyorLiftMk2, _reader, _fgoh, 120){
  }

  ConveyorLiftMk2::~ConveyorLiftMk2() {
  }

}
