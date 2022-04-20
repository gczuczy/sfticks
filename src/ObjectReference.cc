
#include "ObjectReference.hh"
#include "FGObjectLibrary.hh"

#include <boost/core/null_deleter.hpp>

#include "misc.hh"

namespace FG {

  ObjectReference::ObjectReference() {
  }

  ObjectReference::ObjectReference(const std::string& _ln, const std::string& _pn)
    : c_levelname(_ln), c_pathname(_pn) {
    fillme();
  }

  ObjectReference::ObjectReference(const ObjectReference& _other)
    : c_levelname(_other.c_levelname), c_pathname(_other.c_pathname) {
    fillme();
  }

  ObjectReference::ObjectReference(ObjectReference&& _other)
    : c_levelname(std::move(_other.c_levelname)), c_pathname(std::move(_other.c_pathname)) {
    fillme();
  }

  ObjectReference::~ObjectReference() {
  }

  void ObjectReference::fillme() {
#if 0
    c_me = std::shared_ptr<ObjectReference>(this, boost::null_deleter());
    ObjectLibrary::getInstance()->addReference(c_me);
#endif
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
    if ( c_pathname.size()==0 )
      EXCEPTION(strprintf("Unable to resolve empty objref %s:%s",
			  c_levelname.c_str(),
			  c_pathname.c_str()));
    c_obj = ObjectLibrary::getInstance()->lookup(*this);
  }

  std::string ObjectReference::str() {
    return strprintf("ObjectReference(%s:%s)", c_levelname.c_str(), c_pathname.c_str());
  }
}
