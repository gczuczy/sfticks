
#include "FG/GenericEntity.hh"

namespace FG {

  GenericEntity::GenericEntity(Reader& _reader, ObjectHeader& _fgoh)
    : Entity(EntityType::GenericEntity, _reader, _fgoh){
  }

  GenericEntity::~GenericEntity() {
  }

  void GenericEntity::deserialize(Reader &_reader) {
  }

  void GenericEntity::deserializeProperties(Reader &_reader) {
    _reader.store(c_properties);
  }

}
