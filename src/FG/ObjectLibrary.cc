
#include "FG/ObjectLibrary.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  std::unique_ptr<ObjectLibrary> ObjectLibrary::c_instance(nullptr);

  ObjectLibrary* ObjectLibrary::getInstance() {
    if ( !c_instance ) c_instance = std::unique_ptr<ObjectLibrary>(new ObjectLibrary());
    return c_instance.get();
  }

  ObjectLibrary::ObjectLibrary() {
  }

  ObjectLibrary::~ObjectLibrary() {
  }

  void ObjectLibrary::addDictionary(const std::string& _levelname, ObjectDictionary& _library) {
    c_dictionaries.emplace(_levelname, _library);
  }
  
  BaseObjectSP ObjectLibrary::lookup(const std::string& _levelname, const std::string& _pathname) {
    auto it = c_dictionaries.find(_levelname);
    if ( it != c_dictionaries.end() ) return it->second.lookupObject(_pathname);
#if 0
    for (auto xit: c_dictionaries) {
      printf("Level: '%s'\n", it->first.c_str());
    }
#endif
    EXCEPTION(strprintf("ObjectLibrary::lookup(%s, %s) failed: no such level", _levelname.c_str(), _pathname.c_str()));
  }
}
