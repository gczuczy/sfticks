
#include "FG/OilRefinery.hh"
#include "FG/FloatProperty.hh"

namespace FG {

  std::string OilRefinery::objtypename("Build_OilRefinery_C");

  OilRefinery::OilRefinery(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::OilRefinery, _reader, _fgoh) {
  }

  OilRefinery::~OilRefinery() {
  }

}
