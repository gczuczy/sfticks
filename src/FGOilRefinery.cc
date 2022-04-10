
#include "FGOilRefinery.hh"
#include "FloatProperty.hh"

namespace FG {

  std::string OilRefinery::objtypename("Build_OilRefinery_C");

  OilRefinery::OilRefinery(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::OilRefinery, _reader, _fgoh) {
    defineInputs({"Input0"});
    defineOutputs({"Output1"});
  }

  OilRefinery::~OilRefinery() {
  }

}
