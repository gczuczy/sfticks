
#ifndef SFT_FGOBJECTLIBRARY_H
#define SFT_FGOBJECTLIBRARY_H

#include <map>
#include <list>
#include <memory>

#include "FG/ObjectReference.hh"
#include "FG/ObjectDictionary.hh"

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
    BaseObjectSP lookup(const std::string& _levelname, const std::string& _pathname);
    inline BaseObjectSP lookup(const ObjectReference& _ref) {
      return lookup(_ref.levelName(), _ref.pathName());
    };

  private:
    static std::unique_ptr<ObjectLibrary> c_instance;
    std::map<std::string, ObjectDictionary&> c_dictionaries;
  };
};

#endif
