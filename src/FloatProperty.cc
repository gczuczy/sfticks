
#include "FloatProperty.hh"

namespace FG {

  FloatProperty::FloatProperty(const std::string& _name, float& _value, int32_t _index, bool _debug)
    : PropertyInterface(SavePropertyType::FloatProperty, _name, _index), c_value(_value), c_debug(_debug) {
  }

  void FloatProperty::deserialize(Reader& _reader, int32_t _size) {
    _reader.skip(1);
    deserializeData(_reader);
  }

  void FloatProperty::deserializeData(Reader& _reader) {
    _reader(c_value);
    if ( c_debug ) {
      printf("FloatProperty::deserializeData(%s)->%.3f\n", name().c_str(), c_value);
    }
  }

}
