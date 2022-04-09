
#include "FGHadronCollider.hh"

std::string FGHadronCollider::objtypename("Build_HadronCollider_C");

FGHadronCollider::FGHadronCollider(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::HadronCollider, _reader, _fgoh){
}

FGHadronCollider::~FGHadronCollider() {
}

