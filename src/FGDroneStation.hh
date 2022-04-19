
#ifndef SFT_FGDRONESTATION_H
#define SFT_FGDRONESTATION_H

#include "FGStorageUnit.hh"
#include "ObjectReference.hh"
#include "FGEnums.hh"

namespace FG {

  class DroneStation: public StorageUnit {
  public:
    DroneStation()=delete;
    DroneStation(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~DroneStation();

    ObjectReference& inputInventory() {return c_mInputInventory;};
    ObjectReference& outputInventory() {return c_mOutputInventory;};
    ObjectReference& batteryInventory() {return c_mOutputInventory;};
    ObjectReference& stationDrone() {return c_mStationDrone;};
    ObjectReference& dockedDrone() {return c_mDockedDrone;};
    EItemTransferringStage itemTransferringStage() {return c_mItemTransferringStage;};

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);

    ObjectReference c_mInputInventory, c_mOutputInventory, c_mBatteryInventory, c_mInfo,
      c_mInventoryPotential, c_mStationDrone, c_mDockedDrone;
    EItemTransferringStage c_mItemTransferringStage;
  };

}

#endif
