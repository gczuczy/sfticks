
#include "FGDocsJSON.hh"
#include "Exception.hh"
#include "FGObjectLibrary.hh"
#include "FGDescObject.hh"
#include "FGRecipeObject.hh"

#include <codecvt>
#include <locale>
#include <fstream>
#include <sstream>
#include <iostream>

#include <set>

namespace FG {

  DocsJSON::DocsJSON(const std::string& _file) {
    // register the handlers
    registerHandler<DescObject>();
    registerHandler<RecipeObject>();

    // read the json
    std::ifstream i(_file, std::ios::binary);

    if ( ! i.is_open() ) {
      EXCEPTION("failed to open");
    }
    i.seekg(0, std::ios::end);
    size_t size = (size_t)i.tellg();
    i.seekg(2, std::ios::beg);
    size -= 2;
    
    std::u16string stru16((size/2)+1, '\0');
    i.read((char*)&stru16[0], size);

    std::string strutf8 = std::wstring_convert<
      std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(stru16);

    c_dumpjson = nlohmann::json::parse(strutf8);
    //std::cout << std::setw(2) << c_dumpjson << std::endl;

    //index the data
    for (auto& vit: c_dumpjson.items()) {
      //printf("Nativeclass: %s\n", vit.value()["NativeClass"].get<std::string>().c_str());
      // now go through the classes
      auto handler = c_handlers.find(vit.value()["NativeClass"].get<std::string>());
      if ( handler == c_handlers.end() ) continue;
      for (auto& [key, value]: vit.value()["Classes"].items()) {
	//printf("\ne!\n");
	//std::cout << value << std::endl;
	c_objects[value["ClassName"]] = handler->second(std::ref(value));
      }
    }

    // and finally regiser ourselves
    ObjectLibrary::getInstance()->addDictionary("", *this);

    // results
    printf("Docs.json: loaded %lu objects\n", c_objects.size());
  }

  DocsJSON::~DocsJSON() {
  }

  BaseObjectSP DocsJSON::lookupObject(const std::string& _pathname) {
    //printf("%s called on %s\n", __PRETTY_FUNCTION__, _pathname.c_str());
    if ( _pathname.length() == 0 ) return nullptr;

    // get the class, it's after the last dot
    size_t dotpos = _pathname.rfind('.');
    std::string classname = _pathname.substr(dotpos+1);
    //printf(" - Classname: %s\n", classname.c_str());

    auto it = c_objects.find(classname);
    if ( it != c_objects.end() ) return it->second;
    return nullptr;
  }
}
