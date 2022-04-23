
#ifndef SFT_FGDOCSJSON_H
#define SFT_FGDOCSJSON_H

#include "FGObjectDictionary.hh"
#include "FGBaseObject.hh"

#include <stdint.h>
#include <string>
#include <map>
#include <nlohmann/json.hpp>

namespace FG {

  class DocsJSON: public ObjectDictionary {
  public:
    struct itemdescr {
      std::string ClassName;
      std::string DisplayName;
      uint32_t StackSize;
      std::string Ingredients_str="";
      float ManufactoringDuration=0.0;
      std::string Product_str="";
    };
  public:
    DocsJSON() = delete;
    DocsJSON(const std::string& _file);
    virtual ~DocsJSON();

    virtual BaseObjectSP lookupObject(const std::string& _pathname);

    template<class T>
    void registerHandler() {
      for (auto it: T::nativeclasses) {
	//printf("Registering handler for native %s\n", it.c_str());
	c_handlers[it] = [&](nlohmann::json& _json)->BaseObjectSP {
	  //printf("Instantiating object\n");
	  return std::make_shared<T>(std::ref(_json));
	};
      }
    };

  private:
    nlohmann::json c_dumpjson;
    std::map<std::string, std::function<BaseObjectSP(nlohmann::json&)> > c_handlers;
    // classname->object
    std::map<std::string, BaseObjectSP> c_objects;
  };
}

#endif
