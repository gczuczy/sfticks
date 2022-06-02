
#include "FG/Packager.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  std::string Packager::objtypename("Build_Packager_C");

  Packager::Packager(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::Packager, _reader, _fgoh){
  }

  Packager::~Packager() {
  }

  void Packager::doTick(SFT::tickinfo_t& _tick) {
    EXCEPTION(strprintf("Check %s", __PRETTY_FUNCTION__));
  }
}
