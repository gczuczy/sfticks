
#include "BoolProperty.hh"

BoolProperty::BoolProperty(const std::string& _name, bool& _value, int32_t _index)
  : PropertyInterface(SavePropertyType::BoolProperty, _name, _index), c_value(_value) {
}

void BoolProperty::deserialize(Reader& _reader, int32_t _size) {
  deserializeData(_reader);
  _reader.skip(1);
}

void BoolProperty::deserializeData(Reader& _reader) {
  int8_t v;
  _reader(v);
  c_value = (v==1);
}

