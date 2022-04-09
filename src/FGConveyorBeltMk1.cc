
#include "FGConveyorBeltMk1.hh"

namespace FG {

  std::string ConveyorBeltMk1::objtypename("Build_ConveyorBeltMk1_C");

  ConveyorBeltMk1::ConveyorBeltMk1(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorBelt(EntityType::ConveyorBeltMk1, _reader, _fgoh, 60){
  }

  ConveyorBeltMk1::~ConveyorBeltMk1() {
  }

}
