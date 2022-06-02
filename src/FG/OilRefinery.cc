
#include "FG/OilRefinery.hh"
#include "FG/FloatProperty.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  std::string OilRefinery::objtypename("Build_OilRefinery_C");

  OilRefinery::OilRefinery(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::OilRefinery, _reader, _fgoh) {
  }

  OilRefinery::~OilRefinery() {
  }

  void OilRefinery::doTick(SFT::tickinfo_t& _tick) {
    EXCEPTION(strprintf("Check %s", __PRETTY_FUNCTION__));
  }
  
}
