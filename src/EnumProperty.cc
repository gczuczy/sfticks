
#include "EnumProperty.hh"
#include "Exception.hh"
#include "Trace.hh"

EnumProperty::Header::Header(Reader &_r, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::EnumProperty, _r, _name, _index) {
  _r(c_enumtype).skip(1);
};

EnumProperty::Header::Header(std::string _name, int32_t _index, std::string _enumtype)
  : SaveProperty::Header(PropertyType::EnumProperty, _name, _index), c_enumtype(_enumtype) {
}

EnumProperty::Header::~Header() {
}

EnumProperty::EnumProperty(std::shared_ptr<Header> _header, Reader& _reader)
  : SaveProperty(_header) {
  TRACE;
  c_enumtype = _header->enumtype();
  t.detail("name", c_name)
    .detail("reader", _reader.id())
    .detail("index", c_index)
    .detail("enumtype", c_enumtype)
    .detail("readerpos", _reader.pos())
    .detail("readerlen", _reader.len());
  try {
    _reader(c_value);
  } catch (Exception &e) {
    t.printf("EnumProperty exception: %s\n", e.what());
    throw e;
  }
#ifdef SFT_DEBUG
  t.printf("Loaded Enum %s\n Enumtype: %s\n Value: %s\n\n",
	 c_name.c_str(),
	 c_enumtype.c_str(),
	 c_value.c_str());
#endif
}

EnumProperty::~EnumProperty() {
}
