
#include "FGGenericEntity.hh"

FGGenericEntity::FGGenericEntity(Reader& _reader, FGObjectHeader& _fgoh)
  : FGEntity(FGEntityType::GenericEntity, _reader, _fgoh){
}

FGGenericEntity::~FGGenericEntity() {
}

void FGGenericEntity::deserialize(Reader &_reader) {
}

void FGGenericEntity::deserializeProperties(Reader &_reader) {
  _reader.store(c_properties);
}

