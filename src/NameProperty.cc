
#include "NameProperty.hh"
#include "Exception.hh"
#include "Trace.hh"

NameProperty::Header::Header(Reader &_r, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::NameProperty, _r, _name, _index) {
  _r.skip(1);
};

NameProperty::Header::~Header() {
}

NameProperty::NameProperty(std::shared_ptr<Header> _header, Reader& _reader)
  : SaveProperty(_header) {
  TRACE;
  t.detail("name", c_name)
    .detail("reader", _reader.id())
    .detail("type", c_type)
    .detail("index", c_index)
    .detail("readerpos", _reader.pos())
    .detail("readerlen", _reader.len());

  _reader(c_value);

#ifdef SFT_DEBUG
  t.printf("Loaded NameProperty %s:\n Value: %s\n", c_name.c_str(), c_value.c_str());
#endif
}

NameProperty::~NameProperty() {
}
