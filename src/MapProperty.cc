
#include "MapProperty.hh"
#include "Exception.hh"
#include "Trace.hh"
#include "ObjectProperty.hh"
#include "IntProperty.hh"
#include "StructProperty.hh"

MapProperty::Header::Header(Reader &_r, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::MapProperty, _r, _name, _index) {
  TRACE;
  t.detail("name", c_name)
    .detail("reader", _r.id())
    .detail("type", c_ptype)
    .detail("index", c_index)
    .detail("readerpos", _r.pos())
    .detail("readerlen", _r.len());

  std::string kt, vt;
  _r(kt)(vt).skip(1);

  c_key_type = ::ptype(kt);
  c_value_type = ::ptype(vt);

  t.detail("keytype", c_key_type);
  t.detail("valuetype", c_value_type);
};

MapProperty::Header::~Header() {
}


MapProperty::MapProperty(std::shared_ptr<Header> _header, Reader& _reader)
  :SaveProperty(_header) {
  TRACE;
  c_key_type = _header->keytype();
  c_value_type = _header->valuetype();
  t.detail("name", c_name)
    .detail("keytype", c_key_type)
    .detail("valuetype", c_value_type)
    .detail("reader", _reader.id())
    .detail("type", c_type)
    .detail("index", c_index)
    .detail("readerpos", _reader.pos())
    .detail("readerlen", _reader.len());

  int32_t count;
  _reader.skip(4)(count).skip(4);
  t.detail("count", count);

  t.printf("Parsing MapProperty %s\n key type: %s\n value type: %s\n",
	   c_name.c_str(), ptypestr(c_key_type).c_str(), ptypestr(c_value_type).c_str());
  for (int i=0; i<count; ++i) {
    datapair pair;

    for (int j=0; j<=1; ++j) {
      PropertyType pt;
      std::shared_ptr<SaveProperty> v;

      if (j==0) pt = c_key_type;
      else pt = c_value_type;

      if ( pt == PropertyType::ObjectProperty ) {
	try {
	  auto h = std::make_shared<ObjectProperty::Header>(_reader, "", i);
	  v = std::make_shared<ObjectProperty>(h, _reader);
	}
	catch (Exception &e) {
	  t.debug();
	  throw e;
	}
      } else if ( pt == PropertyType::IntProperty ) {
	try {
	  auto h = std::make_shared<IntProperty::Header>(_reader, "", i);
	  v = std::make_shared<IntProperty>(h, _reader);
	}
	catch (Exception &e) {
	  t.debug();
	  throw e;
	}
      } else if ( pt == PropertyType::StructProperty ) {
	std::string n = std::to_string(i);
	//data.debug(128, "StructProp").dump("/tmp/map.struct.dump");
	try {
	  auto h = std::make_shared<StructProperty::Header>(_reader, c_name, i);
	  v = std::make_shared<StructProperty>(h, _reader);
	}
	catch (Exception &e) {
	  t.debug();
	  throw e;
	}
      } else {
	t.printf(" key type: %s\n value type: %s\n",
		 ptypestr(c_key_type).c_str(), ptypestr(c_value_type).c_str());
	EXCEPTION(std::string("Unimplemented type at MapProperty: ")+ptypestr(pt));
      }

      if (j==0) pair.first = v;
      else pair.second = v;
    }
    _reader.skip(4);
    c_data.push_back(pair);
  }

  t.printf("Parsed MapProperty: %s members: %i\n", c_name.c_str(), count);
  t.printf(" key type: %s\n value type: %s\n",
	   ptypestr(c_key_type).c_str(), ptypestr(c_value_type).c_str());
}

MapProperty::~MapProperty() {
}

