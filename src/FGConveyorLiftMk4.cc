
#include "FGConveyorLiftMk4.hh"

namespace FG {

  std::string ConveyorLiftMk4::objtypename("Build_ConveyorLiftMk4_C");

  ConveyorLiftMk4::ConveyorLiftMk4(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorLift(EntityType::ConveyorLiftMk4, _reader, _fgoh, 480){
  }

  ConveyorLiftMk4::~ConveyorLiftMk4() {
  }

}
