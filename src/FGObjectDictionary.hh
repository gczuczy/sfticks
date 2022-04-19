
#ifndef SFT_OBJECTDICTIONARY_H
#define SFT_OBJECTDICTIONARY_H

#include "FGObjectHeader.hh"
#include "FGEntity.hh"
#include "FGComponent.hh"

#include <string>

namespace FG {

  // this is an interface class, marking
  // dictionaries for ObjectLibrary
  class ObjectDictionary {
  public:
    ObjectDictionary()=default;
    virtual ~ObjectDictionary()=0;

  public:
    virtual ObjectHeaderSP lookupObject(const std::string& _pathname)=0;
    inline ObjectHeaderSP lokupObject(const ObjectReference& _ref) {
      return lookupObject(_ref.pathName());
    };
  };
};

#endif
