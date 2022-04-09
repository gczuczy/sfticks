
#include "ObjectProperty.hh"
#include "Trace.hh"

#include <stdio.h>

namespace FG {

  ObjectProperty::ObjectProperty(const std::string& _name, ObjectReference& _value, int32_t _index)
    : PropertyInterface(SavePropertyType::ObjectProperty, _name, _index), c_value(_value) {
  }

  void ObjectProperty::deserialize(Reader& _reader, int32_t _size) {
    _reader.skip(1);
    Reader data(_reader, _size);
    deserializeData(data);
  }

  void ObjectProperty::deserializeData(Reader& _reader) {
    //TRACE;
    _reader(c_value.levelName())(c_value.pathName());
    /*
      printf("ObjProp got: '%s'/'%s'\n", c_value.levelName().c_str(),
      c_value.pathName().c_str());
    */
  }

  void ObjectProperty::deserializeNestedHeaders(Reader& _reader, ObjectProperty::NestedHeader& _nh) {
  }

}
