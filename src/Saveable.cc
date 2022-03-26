
#include "Saveable.hh"

#include <utility>

#include "Exception.hh"
#include "misc.hh"

Saveable::prophdef::prophdef(std::string _pn, std::string _pt, prophfn_t _h)
  : propname(std::move(_pn)), proptype(std::move(_pt)), handler(_h) {
}

Saveable::prophdef::prophdef(prophdef&& other)
  : propname(std::move(other.propname)), proptype(std::move(other.proptype)), handler(other.handler) {
}

Saveable::Saveable() {
}

Saveable::~Saveable() {
}

void Saveable::defineProperty(const std::string& _propname, const std::string& _proptype, prophfn_t _handler) {
  auto it = c_propdefs.find(_propname);
  if ( it != c_propdefs.end() ) EXCEPTION(strprintf("Property '%s'(/%s) already defined",
						    _propname.c_str(), _proptype.c_str()));
  c_propdefs.insert({_propname, prophdef(_propname, _proptype, _handler)});
}

void Saveable::loadProperties(Reader& _reader) {
  std::string name, proptype;
  int32_t len, idx;
  while ( !_reader.eof() ) {
    _reader(name)(proptype);

    // "None" means the end of it
    if ( name == "None" ) break;

    _reader(len)(idx).skip(1);

    auto it = c_propdefs.find(name);

    if ( it == c_propdefs.end() ) {
      printf("!! UNHANDLED\n name: '%s'\n proptype: '%s'\n len: %i\n idx: %i\n",
	     name.c_str(), proptype.c_str(), len, idx);
      printf("%s", str().c_str());
      EXCEPTION(strprintf("Unhandled property %s", name.c_str()));
    }

    if ( it->second.proptype != proptype ) {
      printf("!! Proptype mismatch\n name: '%s'\n proptype(def/read): '%s'/'%s'\n len: %i\n idx: %i\n",
	     name.c_str(), it->second.proptype.c_str(), proptype.c_str(), len, idx);
      EXCEPTION(strprintf("Unhandled property %s", name.c_str()));
    }

    printf("Calling handler for %s len:%i idx:%i\n", name.c_str(), len, idx);
    try {
      Reader propreader(_reader, len, __FILE__, __LINE__, __PRETTY_FUNCTION__);
      propreader.debug(4, "propreader-pre");
      it->second.handler(std::ref(propreader), idx);
      propreader.debug(4, "propreader-post");
    }
    catch (std::exception &e) {
      printf("Exception while calling handler: %s\n", e.what());
    }
  }
}

