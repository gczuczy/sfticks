
#include "FG/TruckStation.hh"
#include "FG/ObjectProperty.hh"
#include "FG/FloatProperty.hh"
#include "FG/BoolProperty.hh"

namespace FG {

  std::string TruckStation::objtypename("Build_TruckStation_C");

  TruckStation::TruckStation(Reader& _reader, ObjectHeader& _fgoh)
    : StorageUnit(EntityType::TruckStation, _reader, _fgoh, 48) {
    defineProperty(std::make_shared<BoolProperty>("mIsInLoadMode", c_mIsInLoadMode));
    defineProperty(std::make_shared<ObjectProperty>("mInventory", c_mInventory));
    defineProperty(std::make_shared<ObjectProperty>("mFuelInventory", c_mFuelInventory));

    //registerComponent("Inventory", c_inventory);
    //registerComponent("FuelInventory", c_fuelinventory);
    defineInventories({"Inventory", "FuelInventory"});
    defineOutputs({"Output0", "Output1"});
    defineInputs({"Input0", "Input1", "Input2"});
  }

  TruckStation::~TruckStation() {
  }

}
