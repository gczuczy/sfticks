
#ifndef SFT_FGOBJECTLIBRARY_H
#define SFT_FGOBJECTLIBRARY_H

#include <map>
#include <list>
#include <memory>

#include "ObjectReference.hh"
#include "FGObjectDictionary.hh"

namespace FG {

  // This class is for looking up ObjectReference
  // contents into actual pointer references
  class ObjectLibrary {
  private:
    ObjectLibrary();
  public:
    ObjectLibrary(const ObjectLibrary&) = delete;
    ObjectLibrary(ObjectLibrary&&) = delete;
    ~ObjectLibrary();

    static ObjectLibrary* getInstance();

    void addDictionary(const std::string& _levelname, ObjectDictionary& _library);
    ObjectHeaderSP lookup(const std::string& _levelname, const std::string& _pathname);
    inline ObjectHeaderSP lookup(const ObjectReference& _ref) {
      return lookup(_ref.levelName(), _ref.pathName());
    };

  private:
    static std::unique_ptr<ObjectLibrary> c_instance;
    std::map<std::string, ObjectDictionary&> c_dictionaries;
  };
};

#endif
