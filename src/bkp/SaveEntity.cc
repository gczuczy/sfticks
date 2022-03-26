
#include "SaveEntity.hh"

#include <stdio.h>

SaveEntity::SaveEntity(Reader& _reader): SaveObject(_reader) {
  c_type = Type::Entity;
  _reader
    (c_needtransform)
    (c_rotation)
    (c_position)
    (c_scale)
    (c_placedinlevel)
    ;
  //printf("SaveEntity ctor\n");
#ifdef SFT_DEBUG
  printf("SaveEntity loaded:\n - Name: %\n - PropType: %s\n - Instance: %s\n",
	 c_name.c_str(), c_property_type.c_str(), c_instance.c_str());
#endif
}

SaveEntity::~SaveEntity() {
}

SaveObject& SaveEntity::loadProperties(Reader &_reader) {
  int32_t compcnt;

  printf(" ** Loading properties\n");
  debug();

  _reader(c_parent_object_root)(c_parent_object_name)(compcnt);

  printf("Parent object root: %s\n", c_parent_object_root.c_str());
  printf("Parent object name: %s\n", c_parent_object_name.c_str());
  printf("Component count: %i\n", compcnt);

  for (int i=0; i<compcnt; ++i) {
    printf("Loading component %i/%i\n", i, compcnt);
    c_components.push_back(std::make_shared<ObjectReference>(_reader));
  }

  return SaveObject::loadProperties(_reader);
}

void SaveEntity::debug() {
  printf("--- SaveEntity\n Name: %s\n Property type: %s\n Instance: %s\n",
	 c_name.c_str(),
	 c_property_type.c_str(),
	 c_instance.c_str());
}