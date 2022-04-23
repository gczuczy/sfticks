
#ifndef SFT_FGJSONOBJECT_H
#define SFT_FGJSONOBJECT_H

#include "FGBaseObject.hh"

#include <nlohmann/json.hpp>
#include <string>
#include <list>
#include <functional>

namespace FG {

  class JSONObject: public BaseObject {
  public:
    typedef std::function<void(nlohmann::json&)> parsehandler_t;
  private:
    struct parsedef {
      std::string field;
      parsehandler_t handler;
    };
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
      registerHandler(_name,
		      [&](nlohmann::json& _json) {
			_var = _json.get<T>();
		      });
    };
    void registerHandler(const std::string& _name, parsehandler_t _handler);

    void parseList(const std::string& _list, std::function<void(const std::string&, int32_t)> _handler);

  private:
    std::list<parsedef> c_parsehandlers;
    std::string c_classname;
  };
  
}

#endif
