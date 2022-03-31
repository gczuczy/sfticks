
#include "GenericArrayProperty.hh"

GenericArrayProperty::GenericArrayProperty(const std::string& _name, int32_t _index)
  : PropertyInterface(SavePropertyType::ArrayProperty, _name, _index), c_arraytypestr(""), c_data(""), c_count(0) {
}

void GenericArrayProperty::deserialize(Reader& _reader, int32_t _size) {
  _reader(c_arraytypestr).skip(1);
  Reader data(_reader, _size, __FILE__, __LINE__, __PRETTY_FUNCTION__);
  //data(c_count);
  deserializeData(data);
}

void GenericArrayProperty::deserializeData(Reader& _reader) {
  _reader.store(c_data);
}
