
#include "FGHadronCollider.hh"

namespace FG {

  std::string HadronCollider::objtypename("Build_HadronCollider_C");

  HadronCollider::HadronCollider(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::HadronCollider, _reader, _fgoh){
  }

  HadronCollider::~HadronCollider() {
  }

}
