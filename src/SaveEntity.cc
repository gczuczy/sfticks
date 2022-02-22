
#include "SaveEntity.hh"

SaveEntity::SaveEntity(Loader::Reader& _reader): SaveObject(_reader) {
  _reader
    .fetch(c_needtransform)
    .fetch(c_rotation)
    .fetch(c_position)
    .fetch(c_scale)
    .fetch(c_placedinlevel)
    ;
  printf("SaveEntity ctor\n");
}

SaveEntity::~SaveEntity() {
}

void SaveEntity::debug() {
  printf("--- SaveEntity\n Name: %s\n Property type: %s\n Instance: %s\n",
	 c_name.c_str(),
	 c_property_type.c_str(),
	 c_instance.c_str());
}
