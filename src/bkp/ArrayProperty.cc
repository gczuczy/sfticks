
#include "ArrayProperty.hh"
#include "Exception.hh"
#include "Trace.hh"

#include "InterfaceProperty.hh"
#include "StructProperty.hh"
#include "ObjectProperty.hh"
#include "ByteProperty.hh"
#include "IntProperty.hh"
//#include "Property.hh"

ArrayProperty::Header::Header(Reader &_r, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::ArrayProperty, _r, _name, _index) {
  TRACE;
  t.detail("name", c_name)
    .detail("reader", _r.id())
    .detail("valuetype", c_valuetype)
    .detail("index", c_index)
    .detail("readerpos", _r.pos())
    .detail("readerlen", _r.len());

  //_r.debug(32, "array-header").dump("/tmp/array-header.dump");
  std::string valuetype;
  try {
    _r(valuetype).skip(1);
  } catch (Exception &e) {
    t.printf("ArrayProperty exception: %s\n", e.what());
    t.debug();
    throw e;
  }
  t.detail("valuetypestr", valuetype);

  c_valuetype = ::ptype(valuetype);
};

ArrayProperty::Header::~Header() {
}

ArrayProperty::ArrayProperty(std::shared_ptr<Header> _header, Reader& _reader)
  : SaveProperty(_header), c_count(0) {
  TRACE;
  c_valuetype = _header->valuetype();
  //c_count = _header->count();
  t.detail("name", c_name)
    .detail("reader", _reader.id())
    .detail("valuetype", c_valuetype)
    //.detail("count", c_count)
    .detail("type", c_type)
    .detail("index", c_index)
    .detail("readerpos", _reader.pos())
    .detail("readerlen", _reader.len());
  c_valuetype = _header->valuetype();
  _reader(c_count);
  parse(_reader);
}

void ArrayProperty::parse(Reader &_reader) {
  TRACE;
  t.detail("name", c_name)
    .detail("valuetype", c_valuetype)
    .detail("count", c_count)
    .detail("reader", _reader.id())
    .detail("type", c_type)
    .detail("index", c_index)
    .detail("readerlen", _reader.len())
    .detail("readerpos", _reader.pos());

  t.detail("count", c_count);
  t.printf("Member count: %i\n", c_count);

  t.printf("Parsing ArrayProperty/%s/%s/%i\n", c_name.c_str(), ptypestr(c_valuetype).c_str(), c_count);
  try {
    t.debug();
    _reader.debug(32,"array").dump("/tmp/array.dump");

    if ( c_valuetype == PropertyType::InterfaceProperty ) {
#ifdef SFT_DEBUG
      t.printf("Member count: %i\n", c_count);
#endif

      for (int i=0; i<c_count; ++i ) {
#ifdef SFT_DEBUG
	t.printf(" - interface.%i/%i\n", i, c_count);
#endif
	std::string name = c_name + std::string(".") + std::to_string(i);
	auto header = std::make_shared<InterfaceProperty::Header>(name, i);
	c_data.push_back(std::make_shared<InterfaceProperty>(header, _reader));
      }
    } else if ( c_valuetype == PropertyType::StructProperty ) {

      _reader.debug(32, "array-struct").dump("/tmp/array-struct.dump");
      std::string name, type;
      int32_t idx(0);
      while ( !_reader.eof() ) {
	_reader(name)(type);
	printf("array-struct name: %s/%s\n",
	       name.c_str(), type.c_str());
	if ( name == "None" ) {
	  _reader.debug(128, "array-struct-none").dump("/tmp/array-struct-none.dump");
	  throw Exception("blah");
	}
	if ( type != "StructProperty" ) {
	  EXCEPTION("Should be a structproperty");
	}
	int32_t size,int2;
	std::string strtype;
	_reader(size)(int2)(strtype).skip(17).debug(32, "array-struct-pre");
	printf("%i(0x%x)/%i(0x%x) %s\n",
	       size, size, int2, int2, strtype.c_str());

	Reader strreader(_reader, size, __FILE__, __LINE__, __PRETTY_FUNCTION__);
	_reader.debug(32, "array-struct-post");
	strreader.dump("/tmp/array-struct-internal.dump");
	auto header = std::make_shared<StructProperty::Header>(strtype, name, idx);
	printf("LOFASZ2-1\n");
	c_data.push_back(std::make_shared<StructProperty>(header, strreader));
	++idx;
	printf("LOFASZ2-2\n");
	throw Exception("LOFASZ2");
      }
      t.debug();
      throw Exception("blah");
      /*
      for (int i=0; i<count; ++i ) {
	std::string name = c_name + std::string(".") + std::to_string(i);
	c_data.push_back(SaveProperty::factory(areader));
      }
      */
    } else if ( c_valuetype == PropertyType::ObjectProperty ) {

      for (int i=0; i<c_count; ++i ) {
	std::string name = c_name + std::string(".") + std::to_string(i);
	auto header = std::make_shared<ObjectProperty::Header>(name, i);
	c_data.push_back(std::make_shared<ObjectProperty>(header, _reader));
      }
    } else if ( c_valuetype == PropertyType::ByteProperty ) {
      std::string btype("None");

      for (int i=0; i<c_count; ++i ) {
	std::string name = c_name + std::string(".") + std::to_string(i);
	auto header = std::make_shared<ByteProperty::Header>(btype, name, i);
	c_data.push_back(std::make_shared<ByteProperty>(header, _reader));
      }
    } else if ( c_valuetype == PropertyType::IntProperty ) {

      for (int i=0; i<c_count; ++i ) {
	std::string name = c_name + std::string(".") + std::to_string(i);
	auto header = std::make_shared<IntProperty::Header>(name, i);
	c_data.push_back(std::make_shared<IntProperty>(header, _reader));
      }
    } else {
      t.printf("ArrayProperty has unimplemented valuetype %s\n", ptypestr(c_valuetype).c_str());
      _reader.debug(128);
      EXCEPTION("Unimplemented array valuetype");
    }
  }
  catch (Exception &e) {
    t.debug();
    throw e;
  }
}

ArrayProperty::~ArrayProperty() {
}
