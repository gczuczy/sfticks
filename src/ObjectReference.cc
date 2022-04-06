
#include "ObjectReference.hh"

ObjectReference::ObjectReference(): c_levelname(""), c_pathname("") {
}

ObjectReference::ObjectReference(const std::string& _ln, const std::string& _pn)
  : c_levelname(_ln), c_pathname(_pn) {
}

ObjectReference::~ObjectReference() {
}

