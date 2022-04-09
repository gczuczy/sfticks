
#ifndef SFT_FGDRONESTATION_H
#define SFT_FGDRONESTATION_H

#include "FGStorageUnit.hh"
#include "ObjectReference.hh"

class FGDroneStation: public FGStorageUnit {
public:
  FGDroneStation()=delete;
  FGDroneStation(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGDroneStation();

  ObjectReference mInputInventory() const {return c_mInputInventory;};
  ObjectReference mOutputInventory() const {return c_mOutputInventory;};
  ObjectReference mBatteryInventory() const {return c_mOutputInventory;};

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);

  ObjectReference c_mInputInventory, c_mOutputInventory, c_mBatteryInventory, c_mInfo, c_mInventoryPotential;
};

#endif
