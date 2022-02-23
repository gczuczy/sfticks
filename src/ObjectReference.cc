
#include <stdio.h>

#include "ObjectReference.hh"

ObjectReference::ObjectReference(Reader& _r) {
  _r(c_levelname)(c_pathname);
  printf("Objref(%s, %s) loaded\n", c_levelname.c_str(), c_pathname.c_str());
}

ObjectReference::~ObjectReference() {
}

