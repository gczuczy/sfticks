#ifndef SFT_PROPERTYTYPE_HH
#define SFT_PROPERTYTYPE_HH

#include <stdint.h>

#include <string>

namespace FG {

  enum class SavePropertyType: int8_t {
    IntProperty=0,
    ObjectProperty,
    ArrayProperty,
    InterfaceProperty,
    StrProperty,
    StructProperty,
    EnumProperty,
    FloatProperty,
    BoolProperty,
    TextProperty,
    NameProperty,
    ByteProperty,
    Int64Property,
    MapProperty,
  };

  std::string ptypestr(SavePropertyType _pt);
  SavePropertyType ptype(const std::string &_v);

}

#endif
