
#include "TextProperty.hh"
#include "Exception.hh"
#include "Trace.hh"

TextProperty::Header::Header(Reader &_r, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::TextProperty, _r, _name, _index) {
  _r.skip(1);
};

TextProperty::Header::~Header() {
}

TextProperty::TextProperty(std::shared_ptr<Header> _header, Reader& _reader)
  : SaveProperty(_header) {
  TRACE;
  t.detail("name", c_name)
    .detail("reader", _reader.id())
    .detail("type", c_type)
    .detail("index", c_index)
    .detail("readerpos", _reader.pos())
    .detail("readerlen", _reader.len());
  int8_t ht;
  _reader(c_flags)(ht);
  c_historytype = (HistoryType)ht;

  if ( c_historytype == HistoryType::None ) {
    int32_t hcis;
    t.detail("histtype", "none");
    _reader(hcis);
    c_has_culture_invariant_string = hcis == 1;
    if ( c_has_culture_invariant_string ) _reader(c_culture_invariant_string);
#ifdef SFT_DEBUG
    t.printf("Loaded TextProperty/None %s:\n CultureInvString: %s\n",
	   c_name.c_str(), c_culture_invariant_string.c_str());
#endif
  } else if ( c_historytype == HistoryType::Base ) {
    t.detail("histtype", "base");
    _reader(c_namespace)(c_key)(c_value);
#ifdef SFT_DEBUG
    t.printf("Loaded TextProperty/Base %s:\n Namespace: %s\n Key: %s\n Value: %s\n",
	   c_name.c_str(), c_namespace.c_str(), c_key.c_str(), c_value.c_str());
#endif
  } else {
      EXCEPTION("Historytype not implemented: "+std::to_string(ht));
  }
}

TextProperty::~TextProperty() {
}
