
#ifndef SFT_OBJECTDICTIONARY_H
#define SFT_OBJECTDICTIONARY_H

#include "FG/BaseObject.hh"
#include "FG/ObjectReference.hh"

#include <string>

namespace FG {

  // this is an interface class, marking
  // dictionaries for ObjectLibrary
  class ObjectDictionary {
  public:
    ObjectDictionary()=default;
    virtual ~ObjectDictionary()=0;

  public:
    virtual BaseObjectSP lookupObject(const std::string& _pathname)=0;
    inline BaseObjectSP lokupObject(const ObjectReference& _ref) {
      return lookupObject(_ref.pathName());
    };
  };
};

#endif
