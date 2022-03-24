
#include "FGTrainDockingStation.hh"

FGTrainDockingStation::FGTrainDockingStation(Reader& _reader, FGObjectHeader& _fgoh)
  : FGStorageUnit(FGEntityType::TrainDockingStation, _reader, _fgoh, 48){
}

FGTrainDockingStation::~FGTrainDockingStation() {
}

