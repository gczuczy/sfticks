
#ifndef SFT_FGTRAINDOCKINGSTATION_H
#define SFT_FGTRAINDOCKINGSTATION_H

#include "FGStorageUnit.hh"
#include "ObjectReference.hh"
#include "EnumProperty.hh"

class FGTrainDockingStation: public FGStorageUnit {
public:
  FGTrainDockingStation()=delete;
  FGTrainDockingStation(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGTrainDockingStation();

  inline float& mTimeSinceLastLoadTransferUpdate() {return c_mTimeSinceLastLoadTransferUpdate;};
  inline float& mTimeSinceLastUnloadTransferUpdate() {return c_mTimeSinceLastUnloadTransferUpdate;};
  inline float& mSmoothedLoadRate() {return c_mSmoothedLoadRate;};
  inline float& mSmoothedUnloadRate() {return c_mSmoothedUnloadRate;};
  inline bool& mIsOrientationReversed() {return c_mIsOrientationReversed;};
  inline bool& mIsInLoadMode() {return c_mIsInLoadMode;};
  inline bool& mHasDockedActor() {return c_mHasDockedActor;};
  inline bool& mIsLoadUnloading() {return c_mIsLoadUnloading;};
  inline ETrainPlatformDockingStatus mSavedDockingStatus() {return c_mSavedDockingStatus;};

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);

  float c_mTimeSinceLastLoadTransferUpdate, c_mTimeSinceLastUnloadTransferUpdate,
    c_mSmoothedLoadRate, c_mSmoothedUnloadRate;
  bool c_mIsOrientationReversed, c_mIsInLoadMode, c_mHasDockedActor, c_mIsLoadUnloading;
  ObjectReference c_mInventory, c_mStationDockingMaster, c_mDockedRailroadVehicle, c_mRailroadTrack;
  ETrainPlatformDockingStatus c_mSavedDockingStatus;
};

#endif
