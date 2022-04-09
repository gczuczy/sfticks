
#include "FGConveyorLiftMk5.hh"

namespace FG {

  std::string ConveyorLiftMk5::objtypename("Build_ConveyorLiftMk5_C");

  ConveyorLiftMk5::ConveyorLiftMk5(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorLift(EntityType::ConveyorLiftMk5, _reader, _fgoh, 780){
  }

  ConveyorLiftMk5::~ConveyorLiftMk5() {
  }

}
