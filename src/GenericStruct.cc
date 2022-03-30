
#include "GenericStruct.hh"
#include "Exception.hh"

GenericStruct::GenericStruct(const std::string& _strtype, const std::string& _name, int32_t _index)
  : StructProperty(_strtype, _name, _index) {
}

void GenericStruct::deserialize(Reader& _reader, int32_t _size) {
  std::string strtype;
  _reader(strtype).skip(17);
  //printf("StructProperty size: %i\n type: '%s'\n", _size, strtype.c_str());
  //_reader.debug(32, "StructProperty").dump("/tmp/struct-generic-data-outer.dump");
  typecheck(strtype);

  Reader data(_reader, _size);
  //data.dump("/tmp/struct-generic-data.dump");
  deserializeData(data);
}

void GenericStruct::deserializeData(Reader& _reader) {
  _reader.store(c_value);
}

