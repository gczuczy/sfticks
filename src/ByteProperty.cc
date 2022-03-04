
#include "ByteProperty.hh"
#include "Exception.hh"
#include "Trace.hh"

ByteProperty::Header::Header(Reader &_r, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::ByteProperty, _r, _name, _index) {
  _r(c_bytetype);
};

ByteProperty::Header::Header(std::string _bytetype, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::ByteProperty, _name, _index), c_bytetype(_bytetype) {
}

ByteProperty::Header::~Header() {
}

ByteProperty::ByteProperty(std::shared_ptr<Header> _header, Reader& _reader)
  : SaveProperty(_header) {
  TRACE;
  c_bytetype = _header->bytetype();
  t.detail("name", c_name)
    .detail("reader", _reader.id())
    .detail("type", c_type)
    .detail("bytetype", c_bytetype)
    .detail("index", c_index)
    .detail("readerpos", _reader.pos())
    .detail("readerlen", _reader.len());

  if ( c_bytetype == "None") {
    int8_t v;
    _reader(v);
    c_value = std::to_string(v);
  } else {
    _reader(c_value);
  }

#ifdef SFT_DEBUG
  t.printf("Loaded ByteProperty %s:\n Type: %s\n Value: %s\n",
	   c_name.c_str(), c_bytetype.c_str(), c_value.c_str());
#endif
  EXCEPTION("ByteProperty untyped");
}

ByteProperty::~ByteProperty() {
}
