
#ifndef SFT_FGDESCOBJECT_H
#define SFT_FGDESCOBJECT_H

#include "FGJSONObject.hh"
#include <stdint.h>
#include <memory>
#include <set>
#include <string>

namespace FG {

  enum class EResourceForm: uint8_t {
    INVALID=0,
    SOLID,
    LIQUID,
    GAS,
    HEAT,
  };

  class DescObject: public JSONObject {
  public:
    static std::set<std::string> nativeclasses;
  public:
    DescObject() = delete;
    DescObject(nlohmann::json& _json);
    virtual ~DescObject();

    inline uint32_t stackSize() const {return c_stacksize;};
    inline EResourceForm form() const {return c_form;};

  private:
    uint32_t c_stacksize=1;
    EResourceForm c_form = EResourceForm::INVALID;
  };
  typedef std::shared_ptr<DescObject> DescObjectSP;
}

#endif
