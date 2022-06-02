
#include "FG/FoundryMk1.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  std::string FoundryMk1::objtypename("Build_FoundryMk1_C");

  FoundryMk1::FoundryMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::FoundryMk1, _reader, _fgoh){
  }

  FoundryMk1::~FoundryMk1() {
  }

  void FoundryMk1::doTick(SFT::tickinfo_t& _tick) {
    EXCEPTION(strprintf("Check %s", __PRETTY_FUNCTION__));
  }
  
}
