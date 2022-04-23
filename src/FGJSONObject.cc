
#include "FGJSONObject.hh"
#include "Exception.hh"
#include "misc.hh"

namespace FG {

  JSONObject::JSONObject(ObjectType _ot): BaseObject(_ot) {
    registerMember("ClassName", c_classname);
  }

  JSONObject::~JSONObject() {
  }
  
  void JSONObject::parseData(nlohmann::json& _json) {
  }

  void JSONObject::registerHandler(const std::string& _name, parsehandler_t _handler) {
    parsedef pd;

    pd.field = _name;
    pd.handler = _handler;
    c_parsehandlers.push_back(std::move(pd));
  }

  void JSONObject::parseList(const std::string& _list, std::function<void(const std::string&, int32_t)> _handler) {
    std::string instr = _list;
    instr.erase(0, 1);
    instr.erase(instr.size()-1, 1);

    std::string::iterator start = instr.end();
    for (auto it=instr.begin(); it!=instr.end(); ++it) {
      if ( *it == '(') {
	start = it;
	++start;
	continue;
      } else if ( *it == ')' ) {
	std::string substr(start, it);

	// get the path between the quotes
	size_t first = substr.find('"', 0);
	size_t second = substr.find('"', first+1);
	std::string path(substr, first+1, second-first-1);
	//printf("Path: %s\n", path.c_str());

	// now find the number
	first = substr.find('=', second+1)+1;
	second = substr.find(')', first+1);
	std::string num(substr, first, second-first-1);

	//printf("Amount: %s/%i\n", num.c_str(), std::stoi(num));
	_handler(std::cref(path), std::stoi(num));
	continue;
      }
    }
  }
}
