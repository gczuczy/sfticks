
#include "FGGenericComponent.hh"


FGGenericComponent::FGGenericComponent(Reader& _reader, FGObjectHeader& _fgoh)
  : FGComponent(_reader, _fgoh){
}

FGGenericComponent::~FGGenericComponent() {
}

void FGGenericComponent::deserialize(Reader &_reader) {
}

void FGGenericComponent::deserializeProperties(Reader &_reader) {
  _reader.store(c_properties);
}
