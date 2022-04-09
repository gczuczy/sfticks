
#include "FGEntity.hh"

#include <stdio.h>

#include "Exception.hh"

namespace FG {

  Entity::Entity(EntityType _et, Reader& _reader, ObjectHeader& _fgoh)
    : ObjectHeader(_fgoh), c_entity_type(_et) {
    deserialize(_reader);
  }

  Entity::~Entity() {
  }

  Entity& Entity::associate(ComponentSP _component) {
    c_components[_component->instance()] = _component;
    return *this;
  }

  void Entity::deserialize(Reader &_reader) {
    _reader
      (c_needtransform)
      (c_rotation)
      (c_position)
      (c_scale)
      (c_placedinlevel)
      ;
  }

}
