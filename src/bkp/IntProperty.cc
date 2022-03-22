
#include "IntProperty.hh"
#include "Exception.hh"
#include "Trace.hh"

IntProperty::Header::Header(Reader &_r, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::IntProperty, _r, _name, _index) {
  _r.skip(1);
};

IntProperty::Header::Header(std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::IntProperty, _name, _index) {
}

IntProperty::Header::~Header() {
}

IntProperty::IntProperty(std::shared_ptr<Header> _header, Reader& _reader)
  : SaveProperty(_header) {
  TRACE;
  t.detail("name", c_name)
    .detail("ptype", c_type)
    .detail("reader", _reader.id())
    .detail("index", c_index)
    .detail("readerpos", _reader.pos())
    .detail("readerlen", _reader.len());
  _reader(c_value);
#ifdef SFT_DEBUG
  t.printf("Loaded truncated IntProperty -: %i\n", c_value);
#endif
}

IntProperty::~IntProperty() {
}

