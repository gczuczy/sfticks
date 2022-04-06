
#include "SaveProperties.hh"

#include "misc.hh"
#include "Exception.hh"
#include "Trace.hh"

SaveProperties::pdkey::pdkey(const std::string& _name, const int32_t _index): name(_name), index(_index) {
}

bool SaveProperties::pdkey::operator<(const pdkey& other) const {
  if ( name == other.name ) return index < other.index;
  return name < other.name;
}

bool SaveProperties::pdkey::operator==(const pdkey& other) const {
  if ( name == other.name ) return index == other.index;
  return name == other.name;
}

void SaveProperties::defineProperty(PropertyInterfaceSP _prop) {
  pdkey key(_prop->name(), _prop->index());

  if ( c_propdefs.find(key) != c_propdefs.end() ) {
    EXCEPTION(strprintf("Key %s.%i already defined", _prop->name().c_str(), _prop->index()));
  }

  c_propdefs.emplace(std::make_pair(key, std::move(_prop)));
}

void SaveProperties::loadProperties(Reader& _reader) {
  std::string name, proptype;
  int32_t len, idx;
  //TRACE;

  while ( !_reader.eof() ) {
    //printf("\n\nStarting on next property\n");
    //_reader.dump("/tmp/prop.dump").debug(32, "prop starting");
    _reader(name)(proptype);
    //printf("+Read '%s'/'%s'\n", name.c_str(), proptype.c_str());

    // "None" means the end of it
    if ( name == "None" ) break;

    _reader(len)(idx);

    pdkey key(name, idx);
    auto it = c_propdefs.find(key);
    if ( it == c_propdefs.end() ) {
      _reader.dump("/tmp/prop-notfound.dump").debug(16, "notfound");
      printf("SaveProperties::loadProperties() key not found: %s:%s.%i %i\n",
	     proptype.c_str(), name.c_str(), idx, len);
      printf("Defined keys:\n");
      for (auto it: c_propdefs) {
	printf(" - %s.%i\n", it.first.name.c_str(), it.first.index);
      }
      //printf("%s", str().c_str());
      EXCEPTION(strprintf("SaveProperties::loadProperties() key not found: %s:%s.%i %i",
			  proptype.c_str(), name.c_str(), idx, len));
    }
#if 0
    printf(" Loading property (%s) %s.%i\n", it->second->savePropertyTypeStr().c_str(),
	   it->second->name().c_str(), it->second->index());
#endif
    it->second->deserialize(_reader, len);
  }
  // sometimes there's some trailing null data, get rid of that
  // so our reader doesn't throw
  int64_t remnants = _reader.len() - _reader.pos();
  if ( remnants ) _reader.skip(remnants);
}
