
#include "FGManufacturerMk1.hh"

std::string FGManufacturerMk1::objtypename("Build_ManufacturerMk1_C");

FGManufacturerMk1::FGManufacturerMk1(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::ManufacturerMk1, _reader, _fgoh) {
}

FGManufacturerMk1::~FGManufacturerMk1() {
}

