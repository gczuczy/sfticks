
#include "FGDroneStation.hh"

FGDroneStation::FGDroneStation(Reader& _reader, FGObjectHeader& _fgoh)
  : FGStorageUnit(FGEntityType::DroneStation, _reader, _fgoh, 18){
}

FGDroneStation::~FGDroneStation() {
}

