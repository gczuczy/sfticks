
#include "FG/Entity.hh"

#include <stdio.h>

#include "SFT/Exception.hh"

namespace FG {

  Entity::Entity(EntityType _et, Reader& _reader, ObjectHeader& _fgoh)
    : ObjectHeader(_fgoh), BaseObject(ObjectType::ENTITY), c_entity_type(_et) {
    deserialize(_reader);
  }

  Entity::~Entity() {
  }

  void Entity::associateComponents() {
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
