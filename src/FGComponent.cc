
#include "FGComponent.hh"

FGComponent::FGComponent(Reader& _reader, FGObjectHeader& _fgoh): FGObjectHeader(_fgoh) {
  deserialize(_reader);
}

FGComponent::~FGComponent() {
}

void FGComponent::deserialize(Reader &_reader) {
  _reader(c_parent_entity_name);
}
