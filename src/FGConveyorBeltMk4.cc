
#include "FGConveyorBeltMk4.hh"

std::string FGConveyorBeltMk4::objtypename("Build_ConveyorBeltMk4_C");

FGConveyorBeltMk4::FGConveyorBeltMk4(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorBelt(FGEntityType::ConveyorBeltMk4, _reader, _fgoh, 480){
}

FGConveyorBeltMk4::~FGConveyorBeltMk4() {
}

