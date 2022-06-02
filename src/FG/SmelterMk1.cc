
#include "FG/SmelterMk1.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  std::string SmelterMk1::objtypename("Build_SmelterMk1_C");

  SmelterMk1::SmelterMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::SmelterMk1, _reader, _fgoh){
  }

  SmelterMk1::~SmelterMk1() {
  }

  void SmelterMk1::doTick(SFT::tickinfo_t& _tick) {
    EXCEPTION(strprintf("Check %s", __PRETTY_FUNCTION__));
  }
  
}
