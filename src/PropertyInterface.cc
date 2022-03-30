
#include "PropertyInterface.hh"

#include <map>

#include "Exception.hh"
#include "misc.hh"

PropertyInterface::PropertyInterface(SavePropertyType _pt, const std::string& _name, int32_t _index)
  : c_pt(_pt), c_name(std::move(_name)), c_index(_index){
}

void PropertyInterface::deserialize(Reader& _reader, int32_t _size) {
  EXCEPTION(strprintf("Unimplemented %s::deserialize", ptypestr(c_pt).c_str()));
}

void PropertyInterface::deserializeData(Reader& _reader) {
  EXCEPTION(strprintf("Unimplemented %s::deserializeData", ptypestr(c_pt).c_str()));
}

