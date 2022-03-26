
#include "FGTrainDockingStation.hh"

FGTrainDockingStation::FGTrainDockingStation(Reader& _reader, FGObjectHeader& _fgoh)
  : FGStorageUnit(FGEntityType::TrainDockingStation, _reader, _fgoh, 48), c_mTimeSinceLastLoadTransferUpdate(0),
    c_mTimeSinceLastUnloadTransferUpdate(0), c_mSmoothedLoadRate(0), c_mIsOrientationReversed(false),
    c_mIsInLoadMode(false), c_mSmoothedUnloadRate(0), c_mHasDockedActor(false), c_mIsLoadUnloading(false) {
  setObjDefDecls({"mInventory", "mRailroadTrack", "mDockedRailroadVehicle", "mStationDockingMaster"});

  defineProperty("mTimeSinceLastLoadTransferUpdate", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mTimeSinceLastLoadTransferUpdate);});
  defineProperty("mTimeSinceLastUnloadTransferUpdate", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mTimeSinceLastUnloadTransferUpdate);});
  defineProperty("mSmoothedLoadRate", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mSmoothedLoadRate);});
  defineProperty("mSmoothedUnloadRate", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{_r(c_mSmoothedUnloadRate);});
  defineProperty("mIsOrientationReversed", "BoolProperty",
		 [&](Reader& _r, int32_t)->void{
		   int8_t b;
		   _r(b);
		   c_mIsOrientationReversed = b == 1;
		 });
  defineProperty("mIsInLoadMode", "BoolProperty",
		 [&](Reader& _r, int32_t)->void{
		   int8_t b;
		   _r(b);
		   c_mIsInLoadMode = b == 1;
		 });
  defineProperty("mHasDockedActor", "BoolProperty",
		 [&](Reader& _r, int32_t)->void{
		   int8_t b;
		   _r(b);
		   c_mHasDockedActor = b == 1;
		 });
  defineProperty("mIsLoadUnloading", "BoolProperty",
		 [&](Reader& _r, int32_t)->void{
		   int8_t b;
		   _r(b);
		   c_mIsLoadUnloading = b == 1;
		 });
  defineProperty("mSavedDockingStatus", "EnumProperty",
		 [&](Reader& _r, int32_t)->void{
		   _r(c_mSavedDockingStatus);
		 });
}

FGTrainDockingStation::~FGTrainDockingStation() {
}

