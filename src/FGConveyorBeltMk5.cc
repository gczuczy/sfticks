
#include "FGConveyorBeltMk5.hh"

std::string FGConveyorBeltMk5::objtypename("Build_ConveyorBeltMk5_C");

FGConveyorBeltMk5::FGConveyorBeltMk5(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorBelt(FGEntityType::ConveyorBeltMk5, _reader, _fgoh, 780){
}

FGConveyorBeltMk5::~FGConveyorBeltMk5() {
}

