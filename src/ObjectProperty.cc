
#include "ObjectProperty.hh"
#include "Exception.hh"
#include "Trace.hh"

ObjectProperty::Header::Header(Reader &_r, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::ObjectProperty, _r, _name, _index) {
  _r.skip(1);
}

ObjectProperty::Header::Header(std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::ObjectProperty, _name, _index) {
}

ObjectProperty::Header::~Header() {
}

ObjectProperty::ObjectProperty(std::shared_ptr<Header> _header, Reader& _reader)
  : SaveProperty(_header) {
  TRACE;
  t.detail("name", c_name)
    .detail("reader", _reader.id())
    .detail("type", c_type)
    .detail("index", c_index)
    .detail("readerpos", _reader.pos())
    .detail("readerlen", _reader.len());
  try {
    _reader(c_levelname)(c_pathname);
  } catch (Exception &e) {
    t.printf("ObjectProperty exception: %s\n", e.what());
    throw e;
  }
  t.detail("levelname", c_levelname).detail("pathname", c_pathname);

#ifdef SFT_DEBUG
  t.printf("Loaded ObjectProperty/%s\n - Level name: %s\n - Path name: %s\n",
	 c_name.c_str(),
	 c_levelname.c_str(),
	 c_pathname.c_str());
#endif
}

ObjectProperty::~ObjectProperty() {
}

