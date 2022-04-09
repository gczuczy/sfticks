
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
    : Entity(_et, _reader, _fgoh), c_mTimeSinceStartStopProducing(0), c_mBuildTimeStamp(0), c_mDidFirstTimeUse(false),
      c_mIsProducing(false) {
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

}
