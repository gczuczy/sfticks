
#include "FGOilRefinery.hh"
#include "FloatProperty.hh"

std::string FGOilRefinery::objtypename("Build_OilRefinery_C");

FGOilRefinery::FGOilRefinery(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::OilRefinery, _reader, _fgoh) {
}

FGOilRefinery::~FGOilRefinery() {
}
