
#include "FG/HadronCollider.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  std::string HadronCollider::objtypename("Build_HadronCollider_C");

  HadronCollider::HadronCollider(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::HadronCollider, _reader, _fgoh){
  }

  HadronCollider::~HadronCollider() {
  }

  void HadronCollider::doTick(SFT::tickinfo_t& _tick) {
    EXCEPTION(strprintf("Check %s", __PRETTY_FUNCTION__));
  }
  
}
