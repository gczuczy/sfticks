
#include "FGConveyorLiftMk3.hh"

namespace FG {

  std::string ConveyorLiftMk3::objtypename("Build_ConveyorLiftMk3_C");

  ConveyorLiftMk3::ConveyorLiftMk3(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorLift(EntityType::ConveyorLiftMk3, _reader, _fgoh, 270){
  }

  ConveyorLiftMk3::~ConveyorLiftMk3() {
  }

}
