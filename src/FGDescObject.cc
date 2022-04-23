
#include "FGDescObject.hh"
#include "Exception.hh"
#include "misc.hh"

namespace FG {

  static std::map<std::string, uint32_t> g_stacksizes{
    {"SS_ONE", 1},
    {"SS_SMALL", 50},
    {"SS_MEDIUM", 100},
    {"SS_BIG", 200},
    {"SS_HUGE", 500},
    {"SS_FLUID", 0},
  };

  static std::map<std::string, EResourceForm> g_resourceforms{
    {"RF_INVALID", EResourceForm::INVALID},
    {"RF_SOLID", EResourceForm::SOLID},
    {"RF_LIQUID", EResourceForm::LIQUID},
    {"RF_GAS", EResourceForm::GAS},
    {"RF_HEAT", EResourceForm::HEAT},
  };

  std::set<std::string> DescObject::nativeclasses{
      "Class'/Script/FactoryGame.FGItemDescriptor'",
      "Class'/Script/FactoryGame.FGItemDescriptorBiomass'",
      "Class'/Script/FactoryGame.FGItemDescAmmoTypeProjectile'",
      "Class'/Script/FactoryGame.FGItemDescAmmoTypeInstantHit'",
      "Class'/Script/FactoryGame.FGResourceDescriptor'",
      "Class'/Script/FactoryGame.FGItemDescAmmoTypeColorCartridge'",
      "Class'/Script/FactoryGame.FGGasMask'",
      "Class'/Script/FactoryGame.FGItemDescriptorNuclearFuel'",
  };

  DescObject::DescObject(nlohmann::json& _json): JSONObject(ObjectType::DESC) {
    registerHandler("mForm",
		    [&](nlohmann::json &_json) {
		      auto strform = _json.get<std::string>();
		      auto it = g_resourceforms.find(strform);
		      if ( it == g_resourceforms.end() ) {
			EXCEPTION(strprintf("Unable to find form %s", strform.c_str()));
		      }
		      c_form = it->second;
		    });
    registerHandler("mStackSize",
		    [&](nlohmann::json &_json) {
		      auto strsize = _json.get<std::string>();
		      auto it = g_stacksizes.find(strsize);
		      if ( it == g_stacksizes.end() ) {
			EXCEPTION(strprintf("Unable to find stacksize %s", strsize.c_str()));
		      }
		      c_stacksize = it->second;
		    });
    parseData(_json);
  }

  DescObject::~DescObject() {
  }
}
