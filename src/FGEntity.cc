
#include "FGEntity.hh"

FGEntity::FGEntity(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh)
  : FGObjectHeader(_fgoh), c_entity_type(_et) {
  deserialize(_reader);
}

FGEntity::~FGEntity() {
}

FGEntity& FGEntity::associate(FGComponentSP _component) {
  c_components[_component->instanceName()] = _component;
  return *this;
}

void FGEntity::deserialize(Reader &_reader) {
  _reader
    (c_needtransform)
    (c_rotation)
    (c_position)
    (c_scale)
    (c_placedinlevel)
    ;
}

