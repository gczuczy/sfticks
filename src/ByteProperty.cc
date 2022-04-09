
#include "ByteProperty.hh"

namespace FG {

  ByteProperty::ByteProperty(const std::string& _name, value_type& _value, int32_t _index)
    : PropertyInterface(SavePropertyType::ByteProperty, _name, _index), c_value(_value) {
  }

  void ByteProperty::deserialize(Reader& _reader, int32_t _size) {
    _reader.skip(1);
    Reader data(_reader, _size);
    deserializeData(data);
  }

  void ByteProperty::deserializeData(Reader& _reader) {
    _reader(c_value);
  }

}
