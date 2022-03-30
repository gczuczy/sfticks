
#include "ObjectProperty.hh"

ObjectProperty::ObjectProperty(const std::string& _name, ObjectReference& _value, int32_t _index)
  : PropertyInterface(SavePropertyType::ObjectProperty, _name, _index), c_value(_value) {
}

void ObjectProperty::deserialize(Reader& _reader, int32_t _size) {
  _reader.skip(1);
  Reader data(_reader, _size);
  deserializeData(data);
}

void ObjectProperty::deserializeData(Reader& _reader) {
  _reader(c_value.pathName())(c_value.levelName());
}

