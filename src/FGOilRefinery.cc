
#include "FGOilRefinery.hh"
#include "FloatProperty.hh"

FGOilRefinery::FGOilRefinery(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::OilRefinery, _reader, _fgoh) {
}

FGOilRefinery::~FGOilRefinery() {
}
