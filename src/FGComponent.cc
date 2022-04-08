
#include "FGComponent.hh"

FGComponent::FGComponent(FGComponentType _comptype, Reader& _reader, FGObjectHeader& _fgoh)
  : FGObjectHeader(_fgoh), c_comptype(_comptype) {
  deserialize(_reader);
}

FGComponent::~FGComponent() {
}

void FGComponent::deserializeProperties(Reader &_reader) {
  //TRACE;
  loadProperties(_reader);
}

void FGComponent::deserialize(Reader &_reader) {
  _reader(c_parent_entity_name);
}
