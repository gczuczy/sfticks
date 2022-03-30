
#include "IntProperty.hh"

IntProperty::IntProperty(const std::string& _name, int32_t& _value, int32_t _index)
  : PropertyInterface(SavePropertyType::IntProperty, _name, _index), c_value(_value) {
}

void IntProperty::deserialize(Reader& _reader, int32_t _size) {
  _reader.skip(1);
  Reader data(_reader, _size);
  deserializeData(data);
}

void IntProperty::deserializeData(Reader& _reader) {
  _reader(c_value);
}

