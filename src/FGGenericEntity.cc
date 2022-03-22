
#include "FGGenericEntity.hh"

FGGenericEntity::FGGenericEntity(Reader& _reader, FGObjectHeader& _fgoh)
  : FGEntity(FGEntityTypes::GenericEntity, _reader, _fgoh){
}

FGGenericEntity::~FGGenericEntity() {
}

void FGGenericEntity::deserialize(Reader &_reader) {
}

