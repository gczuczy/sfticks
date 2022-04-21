
#include "FGBuilding.hh"
#include "Trace.hh"
#include "Exception.hh"
#include "misc.hh"

#include "FloatProperty.hh"
#include "ObjectProperty.hh"
#include "BoolProperty.hh"
#include "StructProperty.hh"

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

    //components
    defineInventories({"InputInventory", "OutputInventory", "InventoryPotential"});
  }

  Building::~Building() {
  }

  void Building::defineInputs(const std::vector<std::string>& _compnames) {
    if ( !c_inputs.empty() )
      EXCEPTION(strprintf("Inputs(%li) already defined %s",
			  c_inputs.size(), instance().c_str()));

    c_inputs.resize(_compnames.size());
    for (auto i=0; i<_compnames.size(); ++i )
      registerComponent(_compnames[i], c_inputs[i]);
  }

  void Building::defineOutputs(const std::vector<std::string>& _compnames) {
    if ( !c_outputs.empty() )
      EXCEPTION(strprintf("Outputs(%li) already defined %s",
			  c_outputs.size(), instance().c_str()));

    c_outputs.resize(_compnames.size());
    for (auto i=0; i<_compnames.size(); ++i )
      registerComponent(_compnames[i], c_outputs[i]);
  }

  void Building::defineInventories(const std::list<std::string>& _compnames) {
    for (auto it: _compnames)
      registerComponent(it, c_inventories[it]);
  }
}
