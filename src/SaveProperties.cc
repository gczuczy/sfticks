
#include "SaveProperties.hh"
#include "Exception.hh"

#include <map>

static std::map<std::string, PropertyType> g_propmap = {
  {"IntProperty", PropertyType::IntProperty},
  {"ObjectProperty", PropertyType::ObjectProperty},
  {"ArrayProperty", PropertyType::ArrayProperty},
  {"InterfaceProperty", PropertyType::InterfaceProperty},
  {"StrProperty", PropertyType::StrProperty},
  {"StructProperty", PropertyType::StructProperty},
  {"EnumProperty", PropertyType::EnumProperty},
  {"FloatProperty", PropertyType::FloatProperty}
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
  //_reader.debug(128);
  printf("SaveProperty check pos:%li len:%li\n", _reader.pos(), _reader.len());
  if ( _reader.eof() )
    return std::shared_ptr<SaveProperty>(0);
  try {
    _reader.debug(128);
    _reader.dump("/tmp/saveojbj.dump");
    _reader(name)(type);
  } catch (Exception &e) {
    printf("SaveProperty exception: %s\n", e.what());
    throw e;
  }

#ifdef SFT_DEBUG
  printf("factory(%s/%s) size:%i\n",
	 name.c_str(),
	 type.c_str(),
	 size);
#endif
  //throw Exception("blah");

  if ( name == "None" && type == "" )
    return std::shared_ptr<SaveProperty>(0);

  _reader(size)(index);

  auto it = g_propmap.find(type);
  if ( it == g_propmap.end() ) {
    printf("PropertyType not found: %s\n", type.c_str());
    throw Exception("Unknown property type");
  }
#if 0
  Reader objreader(_reader.pass(size), size);
  _reader.skip(1);
  return factory(it->second, objreader, name, index);
#else
  return factory(it->second, _reader, name, index, size);
#endif
}

std::shared_ptr<SaveProperty> SaveProperty::factory(PropertyType _type, Reader& _reader, std::string _name,
						    int32_t _index, int32_t _size) {
  if ( _type == PropertyType::IntProperty ) {
    return std::make_shared<IntProperty>(_name, _reader, _index, _size);
  } else if ( _type == PropertyType::ObjectProperty ) {
    return std::make_shared<ObjectProperty>(_name, _reader, _index, _size);
  } else if ( _type == PropertyType::ArrayProperty ) {
    return std::make_shared<ArrayProperty>(_name, _reader, _index, _size);
  } else if ( _type == PropertyType::StrProperty ) {
    return std::make_shared<StrProperty>(_name, _reader, _index, _size);
  } else if ( _type == PropertyType::StructProperty ) {
    return std::make_shared<StructProperty>(_name, _reader, _index, _size);
  } else if ( _type == PropertyType::EnumProperty ) {
    return std::make_shared<EnumProperty>(_name, _reader, _index, _size);
  } else if ( _type == PropertyType::FloatProperty ) {
    return std::make_shared<FloatProperty>(_name, _reader, _index, _size);
  } else {
    throw Exception("Not implemented yet");
  }
}

IntProperty::IntProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size): SaveProperty(_name, _index) {
  c_type = PropertyType::IntProperty;

  try {
    _reader(c_value);
    _reader.skip(1);
  } catch (Exception &e) {
    printf("IntProperty exception: %s\n", e.what());
    throw e;
  }
    
#ifdef SFT_DEBUG
  printf("Loaded IntProperty %s: %i\n", c_name.c_str(), c_value);
#endif
}

IntProperty::~IntProperty() {
}

ObjectProperty::ObjectProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size): SaveProperty(_name, _index) {
  c_type = PropertyType::ObjectProperty;

  try {
    _reader.skip(1);
    _reader(c_levelname)(c_pathname);
  } catch (Exception &e) {
    printf("ObjectProperty exception: %s\n", e.what());
    throw e;
  }

#ifdef SFT_DEBUG
  printf("Loaded ObjectProperty/%s\n - Level name: %s\n - Path name: %s\n",
	 c_name.c_str(),
	 c_levelname.c_str(),
	 c_pathname.c_str());
#endif
}

ObjectProperty::~ObjectProperty() {
}

ArrayProperty::ArrayProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size): SaveProperty(_name, _index) {
  c_type = PropertyType::ArrayProperty;

  std::string valuetype;
  try {
    _reader(valuetype).skip(1);
  } catch (Exception &e) {
    printf("ArrayProperty exception: %s\n", e.what());
    throw e;
  }
  printf("Parsing ArrayProperty/%s/%s/%i\n", c_name.c_str(), valuetype.c_str(), _size);
  Reader areader(_reader, _size);

  //areader.dump("/tmp/array.dump");

  auto it = g_propmap.find(valuetype);
  if ( it == g_propmap.end() ) {
    printf("Unimplemented proptype in array %s\n", valuetype.c_str());
    areader.debug(128);
    throw Exception("Unimplemented proptype in array");
  }
  c_valuetype = it->second;

  if ( c_valuetype == PropertyType::InterfaceProperty ) {
    int32_t count;
    areader(count);
#ifdef SFT_DEBUG
    printf("Member count: %i\n", count);
#endif

    for (int i=0; i<count; ++i ) {
#ifdef SFT_DEBUG
      printf(" - interface.%i\n", i);
#endif
      std::string name = c_name + std::string(".") + std::to_string(i);
      c_data.push_back(std::make_shared<InterfaceProperty>(name, areader, i, 0, false));
    }
  } else if ( c_valuetype == PropertyType::StructProperty ) {
    int32_t count;
    areader(count);
    printf("Member count: %i\n", count);

    for (int i=0; i<count; ++i ) {
      std::string name = c_name + std::string(".") + std::to_string(i);
#if 0
      c_data.push_back(std::make_shared<StructProperty>(name, areader, i, ));
#endif
      c_data.push_back(SaveProperty::factory(areader));
    }
  } else {
    printf("ArrayProperty has unimplemented valuetype %s\n", valuetype.c_str());
    areader.debug(128);
    throw Exception("Unimplemented array valuetype");
  }

}

ArrayProperty::~ArrayProperty() {
}

InterfaceProperty::InterfaceProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size, bool _skip): SaveProperty(_name, _index) {
  c_type = PropertyType::InterfaceProperty;

  try{
    if ( _skip ) _reader.skip(1);
    _reader(c_levelname)(c_pathname);
  } catch (Exception &e) {
    printf("InterfaceProperty exception: %s\n", e.what());
    throw e;
  }
#ifdef SFT_DEBUG
  printf("Loaded InterfaceProperty/%s\n - Level name: %s\n - Path name: %s\n",
	 c_name.c_str(),
	 c_levelname.c_str(),
	 c_pathname.c_str());
#endif
}

InterfaceProperty::~InterfaceProperty() {
}

StrProperty::StrProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size): SaveProperty(_name, _index) {
  c_type = PropertyType::StrProperty;

  try {
    _reader.skip(1);
    _reader(c_value);
  } catch (Exception &e) {
    printf("StrProperty exception: %s\n", e.what());
    throw e;
  }
    
#ifdef SFT_DEBUG
  printf("Loaded StrProperty/%s\n - value: %s\n",
	 c_name.c_str(),
	 c_value.c_str());
#endif
}

StrProperty::~StrProperty() {
}

StructProperty::StructProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size): SaveProperty(_name, _index) {  c_type = PropertyType::StructProperty;

  std::string name;
  //_reader.debug(128);
  try {
  _reader(name).skip(4*4+1);
  } catch (Exception &e) {
    printf("StructProperty exception: %s\n", e.what());
    throw e;
  }
  printf("StructProperty name/mcnt: %s\n", name.c_str());

  std::shared_ptr<SaveProperty> obj;
  while ( (obj = SaveProperty::factory(_reader)) ) {
    
  }
  //_reader.debug(128);

  throw Exception("foo");
}

StructProperty::~StructProperty() {
}

EnumProperty::EnumProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size): SaveProperty(_name, _index) {
  try {
    _reader(c_enumtype).skip(1)(c_value);
  } catch (Exception &e) {
    printf("EnumProperty exception: %s\n", e.what());
    throw e;
  }
#ifdef SFT_DEBUG
  printf("Loaded Enum %s\n Enumtype: %s\n Value: %s\n\n",
	 _name.c_str(),
	 c_enumtype.c_str(),
	 c_value.c_str());
#endif
}

EnumProperty::~EnumProperty() {
}

FloatProperty::FloatProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size): SaveProperty(_name, _index) {
  try {
    _reader.skip(1)(c_value);
  } catch (Exception &e) {
    printf("FloatProperty exception: %s\n", e.what());
    throw e;
  }
#ifdef SFT_DEBUG
  printf("Loaded Float %s: %f\n",
	 c_name.c_str(),
	 c_value);
#endif
}

FloatProperty::~FloatProperty() {
}
