
#include <stdio.h>

#include "SaveObject.hh"

SaveObject::SaveObject(Loader::Reader &_reader) {
  _reader
    .fetch(c_name)
    .fetch(c_property_type)
    .fetch(c_instance);
  //printf("SaveObject() ctor\n");
}

SaveObject::~SaveObject() {
}

void SaveObject::debug() {
  printf("---\nName: %s\nProperty type: %s\nInstance: %s\n",
	 c_name.c_str(),
	 c_property_type.c_str(),
	 c_instance.c_str());
}
