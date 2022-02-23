
#include "SaveComponent.hh"

SaveComponent::SaveComponent(Reader& _reader): SaveObject(_reader) {
  c_type = Type::Component;
  _reader(c_parent_entity_name);
}

SaveComponent::~SaveComponent() {
}

void SaveComponent::debug() {
  printf("--- SaveEntity\n Name: %s\n Property type: %s\n Instance: %s\n Parent: %s\n",
	 c_name.c_str(),
	 c_property_type.c_str(),
	 c_instance.c_str(),
	 c_parent_entity_name.c_str());
}


