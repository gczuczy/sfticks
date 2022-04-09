
#include "FloatProperty.hh"

namespace FG {

  FloatProperty::FloatProperty(const std::string& _name, float& _value, int32_t _index)
    : PropertyInterface(SavePropertyType::FloatProperty, _name, _index), c_value(_value) {
  }

  void FloatProperty::deserialize(Reader& _reader, int32_t _size) {
    _reader.skip(1);
    deserializeData(_reader);
  }

  void FloatProperty::deserializeData(Reader& _reader) {
    _reader(c_value);
  }

}
