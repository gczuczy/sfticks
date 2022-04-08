
#include "FGEntity.hh"

#include <stdio.h>

#include "Exception.hh"

FGEntity::FGEntity(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh)
  : FGObjectHeader(_fgoh), c_entity_type(_et) {
  deserialize(_reader);
}

FGEntity::~FGEntity() {
}

FGEntity& FGEntity::associate(FGComponentSP _component) {
  c_components[_component->instance()] = _component;
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
