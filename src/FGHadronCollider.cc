
#include "FGHadronCollider.hh"

FGHadronCollider::FGHadronCollider(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::HadronCollider, _reader, _fgoh){
}

FGHadronCollider::~FGHadronCollider() {
}

