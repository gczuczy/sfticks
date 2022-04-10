
#include "FGDroneStation.hh"
#include "ObjectProperty.hh"
#include "EnumProperty.hh"

namespace FG {

  std::string DroneStation::objtypename("Build_DroneStation_C");

  DroneStation::DroneStation(Reader& _reader, ObjectHeader& _fgoh)
    : StorageUnit(EntityType::DroneStation, _reader, _fgoh, 18),
      c_mItemTransferringStage(EItemTransferringStage::ITS_LOAD) {
    defineProperty(std::make_shared<ObjectProperty>("mInputInventory", c_mInputInventory));
    defineProperty(std::make_shared<ObjectProperty>("mOutputInventory", c_mOutputInventory));
    defineProperty(std::make_shared<ObjectProperty>("mBatteryInventory", c_mBatteryInventory));
    defineProperty(std::make_shared<ObjectProperty>("mInfo", c_mInfo));
    defineProperty(std::make_shared<ObjectProperty>("mInventoryPotential", c_mInventoryPotential));
    defineProperty(std::make_shared<ObjectProperty>("mStationDrone", c_mStationDrone));
    defineProperty(std::make_shared<ObjectProperty>("mDockedDrone", c_mDockedDrone));
    defineProperty(std::make_shared<EnumProperty<EItemTransferringStage> >("mItemTransferringStage", c_mItemTransferringStage));

    defineInputs({"Input0", "Input1"});
    defineOutputs({"Output0"});
  }

  DroneStation::~DroneStation() {
  }

}
