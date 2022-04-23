
#include "FGRecipeObject.hh"
#include "Exception.hh"
#include "misc.hh"

namespace FG {

  std::set<std::string> RecipeObject::nativeclasses{
      "Class'/Script/FactoryGame.FGRecipe'",
  };

  RecipeObject::RecipeObject(nlohmann::json& _json): JSONObject(ObjectType::RECIPE) {
    registerMember("mManufactoringDuration", c_mManufactoringDuration);
    registerHandler("mIngredients",
		    [&](nlohmann::json &_json) {
		      parseList(_json.get<std::string>(),
				[&](const std::string& _path, int32_t _amount) {
				  c_ingredients[ObjectReference("", _path)] = _amount;
				});
		    });
    registerHandler("mProduct",
		    [&](nlohmann::json &_json) {
		      parseList(_json.get<std::string>(),
				[&](const std::string& _path, int32_t _amount) {
				  c_products[ObjectReference("", _path)] = _amount;
				});
		    });
    parseData(_json);
  }

  RecipeObject::~RecipeObject() {
  }
}
