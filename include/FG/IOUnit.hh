
#ifndef SFT_FGIOUNIT_H
#define SFT_FGIOUNIT_H

#include "FG/Building.hh"
#include "FG/ObjectReference.hh"

namespace FG {

  /*
    This is a base class for Input/Output units.
    An input-output unit is everything that has at least input or output, and
    does something with it, apart from storing it.
  */
  class IOUnit: public Building {
  public:
    IOUnit()=delete;
    IOUnit(EntityType _et, Reader& _reader, ObjectHeader& _fgoh);
    virtual ~IOUnit();

    inline float& currentManufacturingProgress() {return c_mCurrentManufacturingProgress;};
    inline ObjectReference& inputInventory() {return c_mInputInventory;};
    inline ObjectReference& outputInventory() {return c_mOutputInventory;};
    inline ObjectReference& currentRecipe() {return c_mCurrentRecipe;};
    inline ObjectReference& onventoryPotential() {return c_mInventoryPotential;};
    inline float& pendingPotential() {return c_mPendingPotential;};
    inline float& currentPotential() {return c_mCurrentPotential;};
    inline bool isProductionPaused() {return c_mIsProductionPaused;};


  private:
    //virtual void deserialize(Reader &_reader);
    float c_mCurrentManufacturingProgress=0, c_mPendingPotential=0, c_mCurrentPotential=0;
    ObjectReference c_mInputInventory, c_mCurrentRecipe, c_mOutputInventory, c_mInventoryPotential;
    bool c_mIsProductionPaused=false;

  protected:
  };

  typedef std::shared_ptr<IOUnit> IOUnitSP;

}

#endif
