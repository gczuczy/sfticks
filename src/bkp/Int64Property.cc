
#include "Int64Property.hh"
#include "Exception.hh"
#include "Trace.hh"

Int64Property::Header::Header(Reader &_r, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::Int64Property, _r, _name, _index) {
  _r.skip(1);
};

Int64Property::Header::~Header() {
}

Int64Property::Int64Property(std::shared_ptr<Header> _header, Reader& _reader)
  :SaveProperty(_header) {
  TRACE;
  t.detail("name", c_name)
    .detail("reader", _reader.id())
    .detail("type", c_type)
    .detail("index", c_index)
    .detail("readerpos", _reader.pos())
    .detail("readerlen", _reader.len());

  _reader(c_value);

#ifdef SFT_DEBUG
  t.printf("Loaded Int64Property %s:\n Value: %li\n", c_name.c_str(), c_value);
#endif
}

Int64Property::~Int64Property() {
}
