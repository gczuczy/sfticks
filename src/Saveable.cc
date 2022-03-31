
#include "Saveable.hh"

#include <utility>

#include "Exception.hh"
#include "misc.hh"

Saveable::objdef::objdef(std::string _ns, std::string _compname)
  : ns(std::move(_ns)), compname(std::move(_compname)) {
}

Saveable::objdef::objdef(objdef&& other)
  : ns(std::move(other.ns)), compname(std::move(other.compname)) {
}

Saveable::objdef::objdef(Reader& _r) {
  _r(ns)(compname);
}

Saveable::prophdef::prophdef(std::string _pn, std::string _pt, prophfn_t _h)
  : propname(std::move(_pn)), proptype(std::move(_pt)), handler(_h) {
}

Saveable::prophdef::prophdef(prophdef&& other)
  : propname(std::move(other.propname)), proptype(std::move(other.proptype)), handler(other.handler) {
}

Saveable::pdkey::pdkey(const std::string& _name, const int32_t _index): name(_name), index(_index) {
}

bool Saveable::pdkey::operator<(const pdkey& other) const {
  if ( name == other.name ) return index < other.index;
  return name < other.name;
}

bool Saveable::pdkey::operator==(const pdkey& other) const {
  if ( name == other.name ) return index == other.index;
  return name == other.name;
}

Saveable::Saveable() {
}

Saveable::~Saveable() {
}

#if 0
void Saveable::defineProperty(const std::string& _propname, const std::string& _proptype, prophfn_t _handler) {
  auto it = c_propdefs.find(_propname);
  if ( it != c_propdefs.end() ) EXCEPTION(strprintf("Property '%s'(/%s) already defined",
						    _propname.c_str(), _proptype.c_str()));
  c_propdefs.insert({_propname, prophdef(_propname, _proptype, _handler)});
}
#endif
void Saveable::defineProperty(PropertyInterfaceSP _prop) {
  pdkey key(_prop->name(), _prop->index());

  if ( c_propdefs.find(key) != c_propdefs.end() ) {
    EXCEPTION(strprintf("Key %s.%i already defined", _prop->name().c_str(), _prop->index()));
  }

  c_propdefs.emplace(std::make_pair(key, std::move(_prop)));
}

void Saveable::loadProperties(Reader& _reader) {
  std::string name, proptype;
  int32_t len, idx;

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
      _reader.dump("/tmp/prop-notfound.dump").debug(128, "notfound");
      printf("Saveable::loadProperties() key not found: %s:%s.%i %i\n",
	     proptype.c_str(), name.c_str(), idx, len);
      printf("%s", str().c_str());
      EXCEPTION(strprintf("Saveable::loadProperties() key not found: %s:%s.%i %i\n",
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

