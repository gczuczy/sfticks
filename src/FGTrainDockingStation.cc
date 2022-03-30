
#include "FGTrainDockingStation.hh"
#include "ObjectProperty.hh"
#include "FloatProperty.hh"
#include "BoolProperty.hh"


FGTrainDockingStation::FGTrainDockingStation(Reader& _reader, FGObjectHeader& _fgoh)
  : FGStorageUnit(FGEntityType::TrainDockingStation, _reader, _fgoh, 48), c_mTimeSinceLastLoadTransferUpdate(0),
    c_mTimeSinceLastUnloadTransferUpdate(0), c_mSmoothedLoadRate(0), c_mIsOrientationReversed(false),
    c_mIsInLoadMode(false), c_mSmoothedUnloadRate(0), c_mHasDockedActor(false), c_mIsLoadUnloading(false) {
  defineProperty(std::make_shared<ObjectProperty>("mInventory", c_mInventory));
  defineProperty(std::make_shared<ObjectProperty>("mStationDockingMaster", c_mStationDockingMaster));
  defineProperty(std::make_shared<ObjectProperty>("mDockedRailroadVehicle", c_mDockedRailroadVehicle));
  defineProperty(std::make_shared<ObjectProperty>("mRailroadTrack", c_mRailroadTrack));
  defineProperty(std::make_shared<FloatProperty>("mTimeSinceLastLoadTransferUpdate", c_mTimeSinceLastLoadTransferUpdate));
  defineProperty(std::make_shared<FloatProperty>("mTimeSinceLastUnloadTransferUpdate", c_mTimeSinceLastUnloadTransferUpdate));
  defineProperty(std::make_shared<FloatProperty>("mSmoothedLoadRate", c_mSmoothedLoadRate));
  defineProperty(std::make_shared<FloatProperty>("mSmoothedUnloadRate", c_mSmoothedUnloadRate));
  defineProperty(std::make_shared<BoolProperty>("mIsOrientationReversed", c_mIsOrientationReversed));
  defineProperty(std::make_shared<BoolProperty>("mIsInLoadMode", c_mIsInLoadMode));
  defineProperty(std::make_shared<BoolProperty>("mHasDockedActor", c_mHasDockedActor));
  defineProperty(std::make_shared<BoolProperty>("mIsLoadUnloading", c_mIsLoadUnloading));
  //defineProperty(std::make_shared<EnumProperty<>>("mSavedDockingStatus", c_mSavedDockingStatus));
  //defineProperty(std::make_shared<Property>("", c_));
}

FGTrainDockingStation::~FGTrainDockingStation() {
}

