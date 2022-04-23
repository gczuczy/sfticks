
#ifndef SFT_FGJSONOBJECT_H
#define SFT_FGJSONOBJECT_H

#include "FGBaseObject.hh"

#include <nlohmann/json.hpp>
#include <string>
#include <map>
#include <functional>
#include <memory>

#include <stdio.h>
#include "misc.hh"

namespace FG {

  class JSONObject: public BaseObject {
  public:
    typedef std::function<void(nlohmann::json&)> parsehandler_t;
  public:
    JSONObject() = delete;
  protected:
    JSONObject(ObjectType _ot);
  public:
    virtual ~JSONObject()=0;

    inline const std::string& className() const {return c_classname;};

  protected:
    void parseData(nlohmann::json& _json);

    template<typename T>
    void registerMember(const std::string& _name, T& _var) {
      //printf("Registering handler for var %s\n", _name.c_str());
      registerHandler(_name,
		      [&](nlohmann::json& _json) {
			//printf("Storing variable %s\n", _name.c_str());
			try {
			  _var = _json.get<T>();
			  return;
			}
			catch (...) {}
			// now try to manually convert strings
			_var = fromstr<T>(_json.get<std::string>());
		      });
    };
    inline void registerHandler(const std::string& _name, parsehandler_t _handler) {
      c_parsehandlers[_name] = _handler;
    };

    void parseList(const std::string& _list, std::function<void(const std::string&, int32_t)> _handler);

  private:
    std::map<std::string, parsehandler_t> c_parsehandlers;
    std::string c_classname;
  };
  typedef std::shared_ptr<JSONObject> JSONObjectSP;
}

#endif
