
#include "StrProperty.hh"
#include "Exception.hh"
#include "Trace.hh"

StrProperty::Header::Header(Reader &_r, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::StrProperty, _r, _name, _index) {
  _r.skip(1);
};

StrProperty::Header::~Header() {
}

StrProperty::StrProperty(std::shared_ptr<Header> _header, Reader& _reader)
  : SaveProperty(_header) {
  TRACE;
  t.detail("name", c_name)
    .detail("reader", _reader.id())
    .detail("type", c_type)
    .detail("index", c_index)
    .detail("readerpos", _reader.pos())
    .detail("readerlen", _reader.len());
  try {
    _reader(c_value);
  } catch (Exception &e) {
    t.printf("StrProperty exception: %s\n", e.what());
    throw e;
  }
    
#ifdef SFT_DEBUG
  t.printf("Loaded StrProperty/%s\n - value: %s\n",
	 c_name.c_str(),
	 c_value.c_str());
#endif
}

StrProperty::~StrProperty() {
}
