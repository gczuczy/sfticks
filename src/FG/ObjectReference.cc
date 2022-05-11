
#include "FG/ObjectReference.hh"
#include "FG/ObjectLibrary.hh"
#include "SFT/Exception.hh"

#include <boost/core/null_deleter.hpp>

#include "misc.hh"

namespace FG {

  ObjectReference::ObjectReference() {
  }

  ObjectReference::ObjectReference(const std::string& _ln, const std::string& _pn)
    : c_levelname(_ln), c_pathname(_pn) {
    if ( c_levelname.length() > c_pathname.length() ) {
      EXCEPTION(strprintf("Levelname(%s) longer than pathname(%s)", _ln.c_str(), _pn.c_str()));
    }
  }

  ObjectReference::ObjectReference(const ObjectReference& _other)
    : c_levelname(_other.c_levelname), c_pathname(_other.c_pathname) {
  }

  ObjectReference::ObjectReference(ObjectReference&& _other)
    : c_levelname(std::move(_other.c_levelname)), c_pathname(std::move(_other.c_pathname)) {
  }

  ObjectReference::~ObjectReference() {
  }

  ObjectReference& ObjectReference::operator=(const ObjectReference& other) {
    c_levelname = other.c_levelname;
    c_pathname = other.c_pathname;
    c_obj = other.c_obj;
    return *this;
  }

  ObjectReference& ObjectReference::operator=(ObjectReference&& other) {
    c_levelname = std::move(other.c_levelname);
    c_pathname = std::move(other.c_pathname);
    c_obj = std::move(other.c_obj);
    return *this;
  }

  bool ObjectReference::operator<(const ObjectReference& b) const {
    if ( c_levelname < b.c_levelname ) return true;
    return c_pathname < b.c_pathname;
  }

  bool ObjectReference::operator>(const ObjectReference& b) const {
    if ( c_levelname > b.c_levelname ) return true;
    return c_pathname > b.c_pathname;
  }

  bool ObjectReference::operator==(const ObjectReference& b) const {
    return c_levelname == b.c_levelname &&
      c_pathname == b.c_pathname;
  }

  void ObjectReference::resolve() {
    if ( c_obj ) return;
    if ( c_pathname.size()==0 ) {
      c_obj = nullptr;
#if 0
      EXCEPTION(strprintf("Unable to resolve empty objref %s:%s",
			  c_levelname.c_str(),
			  c_pathname.c_str()));
#endif
    }
    c_obj = ObjectLibrary::getInstance()->lookup(*this);
  }

  std::string ObjectReference::str() {
    return strprintf("ObjectReference(%s:%s)", c_levelname.c_str(), c_pathname.c_str());
  }
}
