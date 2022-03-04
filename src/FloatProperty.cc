
#include "FloatProperty.hh"
#include "Exception.hh"
#include "Trace.hh"

FloatProperty::Header::Header(Reader &_r, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::FloatProperty, _r, _name, _index) {
  _r.skip(1);
};

FloatProperty::Header::~Header() {
}

FloatProperty::FloatProperty(std::shared_ptr<Header> _header, Reader& _reader)
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
    t.printf("FloatProperty exception: %s\n", e.what());
    throw e;
  }
#ifdef SFT_DEBUG
  t.printf("Loaded Float %s: %f\n",
	 c_name.c_str(),
	 c_value);
#endif
}

FloatProperty::~FloatProperty() {
}
