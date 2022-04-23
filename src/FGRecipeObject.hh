
#ifndef SFT_FGRECIPEOBJECT_H
#define SFT_FGRECIPEOBJECT_H

#include "FGJSONObject.hh"
#include "ObjectReference.hh"
#include <stdint.h>
#include <memory>
#include <set>
#include <string>
#include <map>

namespace FG {

  class RecipeObject: public JSONObject {
  public:
    static std::set<std::string> nativeclasses;
  public:
    RecipeObject() = delete;
    RecipeObject(nlohmann::json& _json);
    virtual ~RecipeObject();

    inline float manufacturingDuration() const {return c_mManufactoringDuration;};

  private:
    float c_mManufactoringDuration;
    std::map<ObjectReference, int32_t> c_ingredients;
    std::map<ObjectReference, int32_t> c_products;
  };
  typedef std::shared_ptr<RecipeObject> RecipeObjectSP;
}

#endif
