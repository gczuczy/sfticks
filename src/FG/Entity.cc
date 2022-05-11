
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

  Entity& Entity::associate(ComponentSP _component) {
    // generic component association
    c_components[_component->instance()] = _component;

    // check the registry whether this one is needed directly
    auto it = c_compregs.find(_component->componentName());
    if ( it != c_compregs.end() ) {
      it->second(std::ref(_component));
    }

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
