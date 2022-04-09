
#include "FGBuilding.hh"
#include "Trace.hh"
#include "Exception.hh"
#include "misc.hh"

#include "FloatProperty.hh"
#include "ObjectProperty.hh"
#include "BoolProperty.hh"

namespace FG {

  Building::FactoryCustomizationData::FactoryCustomizationData(Reader &_reader) {
    //_reader.dump("/tmp/struct-fcd.dump").debug(32, "struct-fcd");
    std::string strtype;

    _reader(strtype);
    if ( strtype != "FactoryCustomizationData" )
      EXCEPTION(strprintf("FactoryCustomizationData struct type does not match: '%s'", strtype.c_str()));

    // i have no idea what these zeroes are
    _reader.skip(4*4+1);

    std::string name, proptype;
    int32_t size, idx;
    do {
      _reader(name);
      if ( name == "None" ) break;
      _reader(proptype);

      if ( name == "SwatchDesc" ) {
	if ( proptype != "ObjectProperty" )
	  EXCEPTION(strprintf("Member %s has wrong proptype: %s", name.c_str(), proptype.c_str()));

	_reader(size)(idx).skip(1);
	//printf("%s/%s size: %i\n", name.c_str(), proptype.c_str(), size);
	Reader r(_reader, size);
	//r.dump("/tmp/struct-FCD-SD.dump");
	r(SwatchDesc_ns)(SwatchDesc_ns);
      } else {
	EXCEPTION(strprintf("Unknown member: '%s'/'%s'",  name.c_str(), proptype.c_str()));
      }
    } while ( name != "None" );
  }


  Building::Building(EntityType _et, Reader& _reader, ObjectHeader& _fgoh)
    : Entity(_et, _reader, _fgoh), c_mTimeSinceStartStopProducing(0), c_mBuildTimeStamp(0), c_mDidFirstTimeUse(false),
      c_mIsProducing(false) {
    c_mCustomizationData = std::make_shared<GenericStruct>("FactoryCustomizationData", "mCustomizationData");

    defineProperty(std::make_shared<FloatProperty>("mTimeSinceStartStopProducing", c_mTimeSinceStartStopProducing));
    defineProperty(std::make_shared<ObjectProperty>("mPowerInfo", c_mPowerInfo));
    defineProperty(std::make_shared<ObjectProperty>("mBuiltWithRecipe", c_mBuiltWithRecipe));
    defineProperty(c_mCustomizationData);
    defineProperty(std::make_shared<FloatProperty>("mBuildTimeStamp", c_mBuildTimeStamp));
    defineProperty(std::make_shared<BoolProperty>("mIsProducing", c_mIsProducing));
    defineProperty(std::make_shared<BoolProperty>("mDidFirstTimeUse", c_mDidFirstTimeUse));
  }

  Building::~Building() {
  }

}
