
#include "FG/ConveyorBeltMk5.hh"

namespace FG {

  std::string ConveyorBeltMk5::objtypename("Build_ConveyorBeltMk5_C");

  ConveyorBeltMk5::ConveyorBeltMk5(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorBelt(EntityType::ConveyorBeltMk5, _reader, _fgoh, 780){
  }

  ConveyorBeltMk5::~ConveyorBeltMk5() {
  }

}
