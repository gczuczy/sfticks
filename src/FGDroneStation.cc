
#include "FGDroneStation.hh"
#include "ObjectProperty.hh"

namespace FG {

  std::string DroneStation::objtypename("Build_DroneStation_C");

  DroneStation::DroneStation(Reader& _reader, ObjectHeader& _fgoh)
    : StorageUnit(EntityType::DroneStation, _reader, _fgoh, 18){
    defineProperty(std::make_shared<ObjectProperty>("mInputInventory", c_mInputInventory));
    defineProperty(std::make_shared<ObjectProperty>("mOutputInventory", c_mOutputInventory));
    defineProperty(std::make_shared<ObjectProperty>("mBatteryInventory", c_mBatteryInventory));
    defineProperty(std::make_shared<ObjectProperty>("mInfo", c_mInfo));
    defineProperty(std::make_shared<ObjectProperty>("mInventoryPotential", c_mInventoryPotential));
  }

  DroneStation::~DroneStation() {
  }

}
