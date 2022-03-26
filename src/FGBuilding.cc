
#include "FGBuilding.hh"
#include "Trace.hh"
#include "Exception.hh"
#include "misc.hh"

FGBuilding::FactoryCustomizationData::FactoryCustomizationData(Reader &_reader) {
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


FGBuilding::FGBuilding(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh)
  : FGEntity(_et, _reader, _fgoh), c_mTimeSinceStartStopProducing(0), c_mIsProducing(false),
    c_mDidFirstTimeUse(false), c_mBuildTimeStamp(0) {
  defPropLoaders();
}

FGBuilding::~FGBuilding() {
}

void FGBuilding::defPropLoaders() {
  setObjDefDecls({"mBuiltWithRecipe", "mPowerInfo"});
  defineProperty("mCustomizationData", "StructProperty",
		 [&](Reader& _r, int32_t)->void{
		   c_mCustomizationData = FactoryCustomizationData(_r);
		 });
  defineProperty("mTimeSinceStartStopProducing", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mTimeSinceStartStopProducing);});
  defineProperty("mIsProducing", "BoolProperty",
		 [&](Reader& _r, int32_t)->void{
		   int8_t b;
		   _r(b);
		   c_mIsProducing = b == 1;
		 });
  defineProperty("mDidFirstTimeUse", "BoolProperty",
		 [&](Reader& _r, int32_t)->void{
		   int8_t b;
		   _r(b);
		   c_mDidFirstTimeUse = b == 1;
		 });
  defineProperty("mBuildTimeStamp", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mBuildTimeStamp);});
}

