
#include "FGConveyorBeltMk1.hh"

std::string FGConveyorBeltMk1::objtypename("Build_ConveyorBeltMk1_C");

FGConveyorBeltMk1::FGConveyorBeltMk1(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorBelt(FGEntityType::ConveyorBeltMk1, _reader, _fgoh, 60){
}

FGConveyorBeltMk1::~FGConveyorBeltMk1() {
}

