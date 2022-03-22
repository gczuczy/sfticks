
#include "BoolProperty.hh"
#include "Exception.hh"
#include "Trace.hh"

BoolProperty::Header::Header(Reader &_r, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::BoolProperty, _r, _name, _index) {
};

BoolProperty::Header::~Header() {
}

BoolProperty::BoolProperty(std::shared_ptr<Header> _header, Reader& _reader)
  : SaveProperty(_header) {
  TRACE;
  t.detail("name", c_name)
    .detail("reader", _reader.id())
    .detail("type", c_type)
    .detail("index", c_index)
    .detail("readerpos", _reader.pos())
    .detail("readerlen", _reader.len());
  int8_t v;
  _reader(v).skip(1);
  c_value = v>0;
#ifdef SFT_DEBUG
  t.printf("Loaded Bool %s: %c\n",
	 c_name.c_str(),
	 c_value?'t':'f');
#endif
}

BoolProperty::~BoolProperty() {
}
