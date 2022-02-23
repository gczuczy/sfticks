
#include "SaveProperties.hh"
#include "Exception.hh"

#include <map>

static std::map<std::string, PropertyType> g_propmap = {
  {"IntProperty", PropertyType::IntProperty},
  {"ObjectProperty", PropertyType::ObjectProperty},
  {"ArrayProperty", PropertyType::ArrayProperty},
  {"InterfaceProperty", PropertyType::InterfaceProperty}
};

SaveProperty::SaveProperty(std::string& _name, std::string& _type, int32_t _index): c_name(_name), c_index(_index) {
  c_type = g_propmap[_type];
}

SaveProperty::SaveProperty(std::string& _name, int32_t _index): c_name(_name), c_index(_index) {
}

SaveProperty::~SaveProperty() {
}

// factory
std::shared_ptr<SaveProperty> SaveProperty::factory(Reader& _reader) {
  std::string name,type;
  int32_t size, index;
  _reader.debug(32);
  _reader(name)(type)(size)(index);

  if ( name == "None" && type == "" )
    return std::shared_ptr<SaveProperty>(0);

  if ( type == "IntProperty" ) {
    return std::shared_ptr<IntProperty>(new IntProperty(name, _reader, index));
  } else if ( type == "ObjectProperty" ) {
    return std::shared_ptr<ObjectProperty>(new ObjectProperty(name, _reader, index));
  } else if ( type == "ArrayProperty" ) {
    return std::shared_ptr<ArrayProperty>(new ArrayProperty(name, _reader, index));
  } else {
    printf(" !!! Got unimplemented type '%s'(%lu)\n", type.c_str(), type.length());
    throw Exception("Not implemented yet");
  }
}

IntProperty::IntProperty(std::string& _name, Reader& _reader, int32_t _index): SaveProperty(_name, _index) {
  c_type = PropertyType::IntProperty;

  _reader(c_value);
  _reader.skip(1);
  printf("Loaded IntProperty %s: %i\n", c_name.c_str(), c_value);
}

IntProperty::~IntProperty() {
}

ObjectProperty::ObjectProperty(std::string& _name, Reader& _reader, int32_t _index): SaveProperty(_name, _index) {
  c_type = PropertyType::ObjectProperty;

  _reader.skip(1);
  _reader(c_levelname)(c_pathname);
  printf("Loaded ObjectProperty/%s\n - Level name: %s\n - Path name: %s\n",
	 c_name.c_str(),
	 c_levelname.c_str(),
	 c_pathname.c_str());
}

ObjectProperty::~ObjectProperty() {
}

ArrayProperty::ArrayProperty(std::string& _name, Reader& _reader, int32_t _index): SaveProperty(_name, _index) {
  c_type = PropertyType::ArrayProperty;

  std::string valuetype;
  _reader(valuetype).skip(1);
  printf("Parsing ArrayProperty/%s/%s\n", c_name.c_str(), valuetype.c_str());

  auto it = g_propmap.find(valuetype);
  if ( it == g_propmap.end() ) {
    printf("Unimplemented proptype in array %s\n", valuetype.c_str());
    throw Exception("Unimplemented proptype in array");
  }
  c_valuetype = it->second;
  _reader.debug(128);

  if ( c_valuetype == PropertyType::InterfaceProperty ) {
    int32_t count;
    _reader(count);
    printf("Member count: %i\n", count);

    for (int i=0; i<count; ++i ) {
      std::string name = c_name + std::string(".") + std::to_string(i);
      c_data.push_back(std::make_shared<InterfaceProperty>(name, _reader, i, false));
    }
  } else {
    printf("ArrayProperty has unimplemented valuetype %s\n", valuetype.c_str());
    throw Exception("Unimplemented array valuetype");
  }

}

ArrayProperty::~ArrayProperty() {
}

InterfaceProperty::InterfaceProperty(std::string& _name, Reader& _reader, int32_t _index, bool _skip): SaveProperty(_name, _index) {
  c_type = PropertyType::InterfaceProperty;

  if ( _skip ) _reader.skip(1);
  _reader(c_levelname)(c_pathname);
  printf("Loaded InterfaceProperty/%s\n - Level name: %s\n - Path name: %s\n",
	 c_name.c_str(),
	 c_levelname.c_str(),
	 c_pathname.c_str());
}

InterfaceProperty::~InterfaceProperty() {
}

