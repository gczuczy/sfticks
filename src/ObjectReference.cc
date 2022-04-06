
#include "ObjectReference.hh"

ObjectReference::ObjectReference(): c_levelname(""), c_pathname("") {
}

ObjectReference::ObjectReference(const std::string& _ln, const std::string& _pn)
  : c_levelname(_ln), c_pathname(_pn) {
}

ObjectReference::~ObjectReference() {
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

