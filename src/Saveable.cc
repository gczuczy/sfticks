
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

Saveable::Saveable() {
}

Saveable::Saveable(const std::set<std::string>& _objdefdecls): c_objdef_decls(std::move(_objdefdecls)) {
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
  std::set<std::string> noskips{"StructProperty"};
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

    if ( noskips.find(proptype) == noskips.end() ) {
      //printf(" + skip(1) for %s\n", proptype.c_str());
      _reader.skip(1);
    } else {
      //printf(" + no skip for %s\n", proptype.c_str());
    }

    if ( len == 0 ) {
      //_reader.dump("/tmp/prop-len0.dump");
      len = 1;
    }

    // first special-case objdefs
    if ( proptype == "ObjectProperty" ) {
      auto oit = c_objdef_decls.find(name);
      if ( oit != c_objdef_decls.end() ) {
	// so it's both and ObjectProperty, and it's
	// also defined to use this mechanics
	Reader objreader(_reader, len, __FILE__, __LINE__, __PRETTY_FUNCTION__);
	c_objdefs.emplace(name, objreader);
	// this specialization is handled, proceed
	continue;
      }
    }

    auto it = c_propdefs.find(name);

    if ( it == c_propdefs.end() ) {
      printf("!! UNHANDLED\n name: '%s'\n proptype: '%s'\n len: %i\n idx: %i\n",
	     name.c_str(), proptype.c_str(), len, idx);
      printf("%s", str().c_str());
      _reader.debug(32, "prop pos");
      Reader uh(_reader, len);
      uh.dump("/tmp/unhandled-prop.dump");
      EXCEPTION(strprintf("Unhandled property %s", name.c_str()));
    }

    if ( it->second.proptype != proptype ) {
      printf("!! Proptype mismatch\n name: '%s'\n proptype(def/read): '%s'/'%s'\n len: %i\n idx: %i\n",
	     name.c_str(), it->second.proptype.c_str(), proptype.c_str(), len, idx);
      EXCEPTION(strprintf("Unhandled property %s", name.c_str()));
    }

    //printf("Calling handler for %s len:%i idx:%i\n", name.c_str(), len, idx);

    try {
      if ( proptype == "StructProperty" ) {
	it->second.handler(std::ref(_reader), idx);
      } else {
	Reader propreader(_reader, len, __FILE__, __LINE__, __PRETTY_FUNCTION__);
	it->second.handler(std::ref(propreader), idx);
      }
    }
    catch (std::exception &e) {
      printf("Exception while calling handler: %s\n", e.what());
      throw e;
    }
  }
}

