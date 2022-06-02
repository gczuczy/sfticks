
#include "FG/SpaceElevator.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  std::string SpaceElevator::objtypename("Build_SpaceElevator_C");

  SpaceElevator::SpaceElevator(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::SpaceElevator, _reader, _fgoh){
  }

  SpaceElevator::~SpaceElevator() {
  }

  void SpaceElevator::doTick(SFT::tickinfo_t& _tick) {
    EXCEPTION(strprintf("Check %s", __PRETTY_FUNCTION__));
  }
}
