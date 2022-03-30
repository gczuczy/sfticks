
#include "StructProperty.hh"

#include <stdio.h>

#include "Exception.hh"
#include "misc.hh"

StructProperty::StructProperty(const std::string& _strtype, const std::string& _name, int32_t _index)
  : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype(_strtype) {
}

void StructProperty::deserialize(Reader& _reader, int32_t _size) {
  std::string strtype;
  _reader(strtype);
  printf("StructProperty size: %i\n type: '%s'\n", _size, strtype.c_str());
  _reader.debug(32, "StructProperty");
  typecheck(strtype);

  Reader data(_reader, _size);
  data.dump("/tmp/struct-property-data.dump");
  deserializeData(data);
}

void StructProperty::deserializeData(Reader& _reader) {
}

void StructProperty::typecheck(const std::string& _st) {
  if ( _st != c_strtype ) EXCEPTION(strprintf("StructProperty strtype mismatch: read:%s vs expected:%s",
					      _st.c_str(),
					      c_strtype.c_str()));
}
