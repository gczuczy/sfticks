
#include "FGConveyorBeltMk3.hh"

std::string FGConveyorBeltMk3::objtypename("Build_ConveyorBeltMk3_C");

FGConveyorBeltMk3::FGConveyorBeltMk3(Reader& _reader, FGObjectHeader& _fgoh)
  : FGConveyorBelt(FGEntityType::ConveyorBeltMk3, _reader, _fgoh, 270){
}

FGConveyorBeltMk3::~FGConveyorBeltMk3() {
}

