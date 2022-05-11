
#ifndef SFT_FGTRUCKSTATION_H
#define SFT_FGTRUCKSTATION_H

#include "FG/StorageUnit.hh"
#include "FG/ObjectReference.hh"
#include "FG/EnumProperty.hh"

namespace FG {

  class TruckStation: public StorageUnit {
  public:
    TruckStation()=delete;
    TruckStation(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~TruckStation();

    inline bool isInLoadMode() {return c_mIsInLoadMode;};

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);

    bool c_mIsInLoadMode=false;
    ObjectReference c_mInventory, c_mFuelInventory;
  };

}

#endif
