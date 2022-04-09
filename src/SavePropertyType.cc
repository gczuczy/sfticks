
#include "SavePropertyType.hh"

#include <map>

#include "Exception.hh"

namespace FG {

  static std::map<std::string, SavePropertyType> g_propmap = {
    {"IntProperty", SavePropertyType::IntProperty},
    {"ObjectProperty", SavePropertyType::ObjectProperty},
    {"ArrayProperty", SavePropertyType::ArrayProperty},
    {"InterfaceProperty", SavePropertyType::InterfaceProperty},
    {"StrProperty", SavePropertyType::StrProperty},
    {"StructProperty", SavePropertyType::StructProperty},
    {"EnumProperty", SavePropertyType::EnumProperty},
    {"FloatProperty", SavePropertyType::FloatProperty},
    {"BoolProperty", SavePropertyType::BoolProperty},
    {"TextProperty", SavePropertyType::TextProperty},
    {"NameProperty", SavePropertyType::NameProperty},
    {"ByteProperty", SavePropertyType::ByteProperty},
    {"Int64Property", SavePropertyType::Int64Property},
    {"MapProperty", SavePropertyType::MapProperty},
  };
  static uint64_t g_callcounter(0);

  std::string ptypestr(SavePropertyType _pt) {
    for (auto it=g_propmap.begin(); it != g_propmap.end(); ++it) {
      if ( it->second == _pt ) return it->first;
    }

    EXCEPTION("Unable to find SavePropertyType");
  }

  SavePropertyType ptype(const std::string &_v) {
    auto it = g_propmap.find(_v);
    if ( it == g_propmap.end() ) {
      EXCEPTION(std::string("Value type not found: "+_v));
    }
    return it->second;
  }

}
