
#include "FGConveyorBeltMk2.hh"

namespace FG {

  std::string ConveyorBeltMk2::objtypename("Build_ConveyorBeltMk2_C");

  ConveyorBeltMk2::ConveyorBeltMk2(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorBelt(EntityType::ConveyorBeltMk2, _reader, _fgoh, 120){
  }

  ConveyorBeltMk2::~ConveyorBeltMk2() {
  }

}
