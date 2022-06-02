
#include "FG/Building.hh"
#include "SFT/Trace.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

#include "FG/FloatProperty.hh"
#include "FG/ObjectProperty.hh"
#include "FG/BoolProperty.hh"
#include "FG/StructProperty.hh"

namespace FG {

  Building::Building(EntityType _et, Reader& _reader, ObjectHeader& _fgoh)
    : Entity(_et, _reader, _fgoh) {
    defineProperty(std::make_shared<FloatProperty>("mTimeSinceStartStopProducing", c_mTimeSinceStartStopProducing));
    defineProperty(std::make_shared<ObjectProperty>("mPowerInfo", c_mPowerInfo));
    defineProperty(std::make_shared<ObjectProperty>("mBuiltWithRecipe", c_mBuiltWithRecipe));
    defineProperty(std::make_shared<FloatProperty>("mBuildTimeStamp", c_mBuildTimeStamp));
    defineProperty(std::make_shared<BoolProperty>("mIsProducing", c_mIsProducing));
    defineProperty(std::make_shared<BoolProperty>("mDidFirstTimeUse", c_mDidFirstTimeUse));
    defineProperty(std::make_shared<StructProperty<FactoryCustomizationData> >("mCustomizationData", c_mCustomizationData));

  }

  Building::~Building() {
  }

  void Building::associateComponents() {
    auto& compdefs = getCompDefs();

    for (auto &compdef: compdefs) {

      //ComponentSP component = compdef.as<Component>();
      if (FactoryConnectionComponentSP fcc; (fcc = compdef.as<FactoryConnectionComponent>()) ) {
	EFactoryConnectionDirection dir = fcc->direction();

	if ( dir == EFactoryConnectionDirection::FCD_OUTPUT ) {
	  c_outputs.push_back(fcc);
	} else if ( dir == EFactoryConnectionDirection::FCD_INPUT ) {
	  c_inputs.push_back(fcc);
	} else {
	  // non-belt components don't seem to have this set
	  // So it goes by name
	  if ( tolower(fcc->componentName(), 5) == "input" ) {
	    c_inputs.push_back(fcc);
	  } else if ( tolower(fcc->componentName(), 6) == "output" ) {
	    c_outputs.push_back(fcc);
	  }
	}
	fcc->finalize();
      } else if ( InventoryComponentSP invcomp; (invcomp = compdef.as<InventoryComponent>()) ) {
	c_inventories[invcomp->componentName()] = invcomp;
	invcomp->finalize();
      } else if ( PowerInfoComponentSP picomp; (picomp = compdef.as<PowerInfoComponent>()) ) {
	c_powerinfo = picomp;
	picomp->finalize();
      } // else it's generic and we don't deal with it
    }
    if ( !c_powerinfo ) c_powerinfo = c_mPowerInfo.as<PowerInfoComponent>();
  } // assicateComponents

  bool Building::recv(DescObjectSP& _item, SFT::tickinfo_t& _tick, FactoryConnectionComponent& _src) {
    // for now we don't accept stuff
    printf("%s\n - %s\n", __PRETTY_FUNCTION__, instance().c_str());
    return false;
  }
} // namespace FG
