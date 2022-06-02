
#include "FG/AssemblerMk1.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  std::string AssemblerMk1::objtypename("Build_AssemblerMk1_C");

  AssemblerMk1::AssemblerMk1(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::AssemblerMk1, _reader, _fgoh){

  }

  AssemblerMk1::~AssemblerMk1() {
  }

  void AssemblerMk1::doTick(SFT::tickinfo_t& _tick) {
    EXCEPTION(strprintf("Check %s", __PRETTY_FUNCTION__));
  }
  
}
