
#include "ObjectProperty.hh"
#include "Trace.hh"

#include <stdio.h>

namespace FG {

  ObjectProperty::ObjectProperty(const std::string& _name, ObjectReference& _value, int32_t _index, bool _debug)
    : PropertyInterface(SavePropertyType::ObjectProperty, _name, _index), c_value(_value),
      c_debug(_debug) {
  }

  void ObjectProperty::deserialize(Reader& _reader, int32_t _size) {
    _reader.skip(1);
    Reader data(_reader, _size);
    deserializeData(data);
  }

  void ObjectProperty::deserializeData(Reader& _reader) {
    //TRACE;
    std::string level, path;
    _reader(level)(path);
    c_value = std::move(ObjectReference(level, path));
    /*
      printf("ObjProp got: '%s'/'%s'\n", c_value.levelName().c_str(),
      c_value.pathName().c_str());
    */
  }

  void ObjectProperty::deserializeNestedHeaders(Reader& _reader, ObjectProperty::NestedHeader& _nh) {
  }

}
