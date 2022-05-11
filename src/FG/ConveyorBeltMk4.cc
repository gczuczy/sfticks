
#include "FG/ConveyorBeltMk4.hh"

namespace FG {

  std::string ConveyorBeltMk4::objtypename("Build_ConveyorBeltMk4_C");

  ConveyorBeltMk4::ConveyorBeltMk4(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorBelt(EntityType::ConveyorBeltMk4, _reader, _fgoh, 480){
  }

  ConveyorBeltMk4::~ConveyorBeltMk4() {
  }

}
