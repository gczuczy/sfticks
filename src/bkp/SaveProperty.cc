
#include "SaveProperty.hh"
#include "Exception.hh"
#include "Trace.hh"
#include "IntProperty.hh"
#include "ObjectProperty.hh"
#include "ArrayProperty.hh"
#include "InterfaceProperty.hh"
#include "StrProperty.hh"
#include "StructProperty.hh"
#include "EnumProperty.hh"
#include "FloatProperty.hh"
#include "BoolProperty.hh"
#include "TextProperty.hh"
#include "NameProperty.hh"
#include "ByteProperty.hh"
#include "Int64Property.hh"
#include "MapProperty.hh"

#include <set>
#include <map>

static std::map<std::string, PropertyType> g_propmap = {
  {"IntProperty", PropertyType::IntProperty},
  {"ObjectProperty", PropertyType::ObjectProperty},
  {"ArrayProperty", PropertyType::ArrayProperty},
  {"InterfaceProperty", PropertyType::InterfaceProperty},
  {"StrProperty", PropertyType::StrProperty},
  {"StructProperty", PropertyType::StructProperty},
  {"EnumProperty", PropertyType::EnumProperty},
  {"FloatProperty", PropertyType::FloatProperty},
  {"BoolProperty", PropertyType::BoolProperty},
  {"TextProperty", PropertyType::TextProperty},
  {"NameProperty", PropertyType::NameProperty},
  {"ByteProperty", PropertyType::ByteProperty},
  {"Int64Property", PropertyType::Int64Property},
  {"MapProperty", PropertyType::MapProperty},
};
static uint64_t g_callcounter(0);

std::string ptypestr(PropertyType _pt) {
  for (auto it=g_propmap.begin(); it != g_propmap.end(); ++it) {
    if ( it->second == _pt ) return it->first;
  }

  EXCEPTION("Unable to find PropertyType");
}

PropertyType ptype(const std::string &_v) {
  auto it = g_propmap.find(_v);
  if ( it == g_propmap.end() ) {
    EXCEPTION(std::string("Value type not found: "+_v));
  }
  return it->second;
}

SaveProperty::Header::Header(PropertyType _pt, Reader &_r, std::string& _name, int32_t _index)
  : c_ptype(_pt), c_name(_name), c_index(_index), c_len(0) {
};

SaveProperty::Header::Header(PropertyType _pt, std::string& _name, int32_t _index)
  : c_ptype(_pt), c_name(_name), c_index(_index), c_len(0) {
}

SaveProperty::Header::~Header() {
}

std::shared_ptr<SaveProperty::Header> SaveProperty::Header::factory(Reader &_r, PropertyType _pt,
						      std::string _name, int32_t _index) {
  TRACE;
  t.detail("proptype", _pt)
    .detail("name", _name)
    .detail("index", _index)
    .detail("reader", _r.id())
    .detail("readerpos", _r.pos())
    .detail("readerlen", _r.len());
  
  t.debug();
  if ( _pt == PropertyType::IntProperty ) {
    return std::make_shared<IntProperty::Header>(_r, _name, _index);
  } else if ( _pt == PropertyType::ObjectProperty ) {
    return std::make_shared<ObjectProperty::Header>(_r, _name, _index);
  } else if ( _pt == PropertyType::ArrayProperty ) {
    return std::make_shared<ArrayProperty::Header>(_r, _name, _index);
  } else if ( _pt == PropertyType::InterfaceProperty ) {
    return std::make_shared<InterfaceProperty::Header>(_r, _name, _index);
  } else if ( _pt == PropertyType::StrProperty ) {
    return std::make_shared<StrProperty::Header>(_r, _name, _index);
  } else if ( _pt == PropertyType::StructProperty ) {
    return std::make_shared<StructProperty::Header>(_r, _name, _index);
  } else if ( _pt == PropertyType::EnumProperty ) {
    return std::make_shared<EnumProperty::Header>(_r, _name, _index);
  } else if ( _pt == PropertyType::FloatProperty ) {
    return std::make_shared<FloatProperty::Header>(_r, _name, _index);
  } else if ( _pt == PropertyType::BoolProperty ) {
    return std::make_shared<BoolProperty::Header>(_r, _name, _index);
  } else if ( _pt == PropertyType::TextProperty ) {
    return std::make_shared<TextProperty::Header>(_r, _name, _index);
  } else if ( _pt == PropertyType::NameProperty ) {
    return std::make_shared<NameProperty::Header>(_r, _name, _index);
  } else if ( _pt == PropertyType::ByteProperty ) {
    return std::make_shared<ByteProperty::Header>(_r, _name, _index);
  } else if ( _pt == PropertyType::Int64Property ) {
    return std::make_shared<Int64Property::Header>(_r, _name, _index);
  } else if ( _pt == PropertyType::MapProperty ) {
    return std::make_shared<MapProperty::Header>(_r, _name, _index);
    /*
  } else if ( _pt == PropertyType:: ) {
    return std::make_shared<::Header>(_r, _name, _index);
    */
  } else {
    t.debug();
    EXCEPTION("Unhandled property type");
  }
}

SaveProperty::SaveProperty(std::string& _name, std::string& _type, int32_t _index): c_name(_name), c_index(_index) {
  c_type = g_propmap[_type];
}

SaveProperty::SaveProperty(PropertyType _type, std::string& _name, int32_t _index):
  c_type(_type), c_name(_name), c_index(_index) {
}

SaveProperty::SaveProperty(std::shared_ptr<Header> _header) {
  c_type = _header->ptype();
  c_name = _header->name();
  c_index = _header->index();
}

SaveProperty::SaveProperty(PropertyType _type, int32_t _index):
  c_type(_type), c_index(_index) {
}

SaveProperty::~SaveProperty() {
}

// factory
std::shared_ptr<SaveProperty> SaveProperty::factory(Reader& _reader) {
  ++g_callcounter;
  std::string name,type;
  int32_t size, index;

  TRACE;
  t.detail("reader", _reader.id())
    .detail("readerpos", _reader.pos())
    .detail("readerlen", _reader.len());
  //_reader.debug(128, "NameProperty check").dump("/tmp/unprop2.dump");
  t.printf("SaveProperty check pos:%li len:%li\n", _reader.pos(), _reader.len());
  _reader.dump("/tmp/lofasz");
  if ( _reader.eof() )
    return std::shared_ptr<SaveProperty>(0);
  try {
    _reader(name);
  } catch (Exception &e) {
    t.debug();
    t.printf("SaveProperty exception: %s\n", e.what());
    throw e;
  }
  _reader.debug(32, "SaveProperty::factory name read");
  t.detail("name", name);

  if ( name == "None" ) {
    t.printf("Got a None name\n");
    t.debug();
    _reader.dump("/tmp/none.dump").debug(128, "None");
    if ( _reader.len() - _reader.pos() == 4 ) _reader.skip(4);
    return std::shared_ptr<SaveProperty>(0);
  }
  _reader(type);
  _reader.debug(32, "SaveProperty::factory type read");
  t.detail("type", type);

  //throw Exception("blah");

  if ( name == "None" || type == "None" ) {
#ifdef SFT_DEBUG
    t.debug();
    t.printf("factory(%s/%s)\n",
	   name.c_str(),
	   type.c_str());
#endif
    return std::shared_ptr<SaveProperty>(0);
  }

  auto it = g_propmap.find(type);
  if ( it == g_propmap.end() ) {
    _reader.debug(32).dump("/tmp/unprop.dump");
    t.printf("(factory) PropertyType not found: '%s' for name '%s'\n", type.c_str(), name.c_str());
    EXCEPTION(std::string("Unknown property type ")+type);
  }
  PropertyType ptype = it->second;
  t.detail("ptype", ptype);

  _reader(size)(index);
  t.detail("size", size).detail("index", index);
  t.debug();
  if ( size == 0 )
    EXCEPTION("Factory size 0");
  auto header = SaveProperty::Header::factory(_reader, ptype, name, index);

  // factory-reader, not fucking-reader :)
  _reader.debug(32, "factory orig-pre");
  Reader freader(_reader, size, __FILE__, __LINE__, __PRETTY_FUNCTION__);
  _reader.debug(32, "factory orig").dump("/tmp/factory-orig.dump");
  freader.debug(32, "factory sub").dump("/tmp/factory-sub.dump");
#ifdef SFT_DEBUG
  t.printf("factory(%s/%s) size:%i\n",
	 name.c_str(),
	 type.c_str(),
	 size);
#endif
  if ( g_callcounter == 4 ) {
    t.debug();
    printf("LOFASZ\n");
    throw Exception("size check");
  }
  _reader.debug(32, "SaveProperty::factory calling factory(header)");
  return factory(header, freader);
}

std::shared_ptr<SaveProperty> SaveProperty::factory(std::shared_ptr<Header> _header, Reader& _reader) {
  TRACE;
  PropertyType pt = _header->ptype();
  t.detail("ptype", pt)
    .detail("reader", _reader.id())
    .detail("name", _header->name())
    .detail("index", _header->index());
  
  if ( pt == PropertyType::IntProperty ) {
    return std::make_shared<IntProperty>(std::dynamic_pointer_cast<IntProperty::Header>(_header), _reader);
  } else if ( pt == PropertyType::ObjectProperty ) {
    return std::make_shared<ObjectProperty>(std::dynamic_pointer_cast<ObjectProperty::Header>(_header), _reader);
  } else if ( pt == PropertyType::ArrayProperty ) {
    return std::make_shared<ArrayProperty>(std::dynamic_pointer_cast<ArrayProperty::Header>(_header), _reader);
  } else if ( pt == PropertyType::StrProperty ) {
    return std::make_shared<StrProperty>(std::dynamic_pointer_cast<StrProperty::Header>(_header), _reader);
  } else if ( pt == PropertyType::StructProperty ) {
    return std::make_shared<StructProperty>(std::dynamic_pointer_cast<StructProperty::Header>(_header), _reader);
  } else if ( pt == PropertyType::EnumProperty ) {
    return std::make_shared<EnumProperty>(std::dynamic_pointer_cast<EnumProperty::Header>(_header), _reader);
  } else if ( pt == PropertyType::FloatProperty ) {
    return std::make_shared<FloatProperty>(std::dynamic_pointer_cast<FloatProperty::Header>(_header), _reader);
  } else if ( pt == PropertyType::BoolProperty ) {
    return std::make_shared<BoolProperty>(std::dynamic_pointer_cast<BoolProperty::Header>(_header), _reader);
  } else if ( pt == PropertyType::TextProperty ) {
    return std::make_shared<TextProperty>(std::dynamic_pointer_cast<TextProperty::Header>(_header), _reader);
  } else if ( pt == PropertyType::NameProperty ) {
    return std::make_shared<NameProperty>(std::dynamic_pointer_cast<NameProperty::Header>(_header), _reader);
  } else if ( pt == PropertyType::ByteProperty ) {
    return std::make_shared<ByteProperty>(std::dynamic_pointer_cast<ByteProperty::Header>(_header), _reader);
  } else if ( pt == PropertyType::Int64Property ) {
    return std::make_shared<Int64Property>(std::dynamic_pointer_cast<Int64Property::Header>(_header), _reader);
  } else if ( pt == PropertyType::MapProperty ) {
    return std::make_shared<MapProperty>(std::dynamic_pointer_cast<MapProperty::Header>(_header), _reader);
  } else {
    t.debug();
    EXCEPTION("Not implemented yet");
  }
}
