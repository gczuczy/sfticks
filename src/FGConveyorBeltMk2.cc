
#include "FGConveyorBeltMk2.hh"

std::string FGConveyorBeltMk2::objtypename("Build_ConveyorBeltMk2_C");

FGConveyorBeltMk2::FGConveyorBeltMk2(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorBelt(FGEntityType::ConveyorBeltMk2, _reader, _fgoh, 120){
}

FGConveyorBeltMk2::~FGConveyorBeltMk2() {
}

