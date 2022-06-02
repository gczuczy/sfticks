
#include "FG/ManufacturerMk1.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  std::string ManufacturerMk1::objtypename("Build_ManufacturerMk1_C");

  ManufacturerMk1::ManufacturerMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::ManufacturerMk1, _reader, _fgoh) {
  }

  ManufacturerMk1::~ManufacturerMk1() {
  }

  void ManufacturerMk1::doTick(SFT::tickinfo_t& _tick) {
    EXCEPTION(strprintf("Check %s", __PRETTY_FUNCTION__));
  }
  
}
