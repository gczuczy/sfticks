
#ifndef SFT_FGTRAINDOCKINGSTATION_H
#define SFT_FGTRAINDOCKINGSTATION_H

#include "FG/StorageUnit.hh"
#include "FG/ObjectReference.hh"
#include "FG/EnumProperty.hh"

namespace FG {

  class TrainDockingStation: public StorageUnit {
  public:
    TrainDockingStation()=delete;
    TrainDockingStation(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~TrainDockingStation();

    inline float timeSinceLastLoadTransferUpdate() {return c_mTimeSinceLastLoadTransferUpdate;};
    inline float timeSinceLastUnloadTransferUpdate() {return c_mTimeSinceLastUnloadTransferUpdate;};
    inline float smoothedLoadRate() {return c_mSmoothedLoadRate;};
    inline float smoothedUnloadRate() {return c_mSmoothedUnloadRate;};
    inline bool isOrientationReversed() {return c_mIsOrientationReversed;};
    inline bool isInLoadMode() {return c_mIsInLoadMode;};
    inline bool hasDockedActor() {return c_mHasDockedActor;};
    inline bool isLoadUnloading() {return c_mIsLoadUnloading;};
    inline ETrainPlatformDockingStatus savedDockingStatus() {return c_mSavedDockingStatus;};
    inline InventoryComponentSP inventory() {return c_inventory;};

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);

    float c_mTimeSinceLastLoadTransferUpdate, c_mTimeSinceLastUnloadTransferUpdate,
      c_mSmoothedLoadRate, c_mSmoothedUnloadRate;
    bool c_mIsOrientationReversed, c_mIsInLoadMode, c_mHasDockedActor, c_mIsLoadUnloading;
    ObjectReference c_mInventory, c_mStationDockingMaster, c_mDockedRailroadVehicle, c_mRailroadTrack;
    ETrainPlatformDockingStatus c_mSavedDockingStatus;
    InventoryComponentSP c_inventory;
  };

}

#endif
