
#include "FG/ConveyorBeltMk3.hh"

namespace FG {

  std::string ConveyorBeltMk3::objtypename("Build_ConveyorBeltMk3_C");

  ConveyorBeltMk3::ConveyorBeltMk3(Reader& _reader, ObjectHeader& _fgoh)
    : ConveyorBelt(EntityType::ConveyorBeltMk3, _reader, _fgoh, 270){
  }

  ConveyorBeltMk3::~ConveyorBeltMk3() {
  }

}
