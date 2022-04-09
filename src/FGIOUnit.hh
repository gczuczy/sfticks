
#ifndef SFT_FGIOUNIT_H
#define SFT_FGIOUNIT_H

#include "FGBuilding.hh"
#include "ObjectReference.hh"
#include "FGInventoryComponent.hh"
#include "FGFactoryConnectionComponent.hh"

#include <vector>

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

    inline float& mCurrentManufacturingProgress() {return c_mCurrentManufacturingProgress;};
    inline ObjectReference& mInputInventory() {return c_mInputInventory;};
    inline ObjectReference& mOutputInventory() {return c_mOutputInventory;};
    inline ObjectReference& mCurrentRecipe() {return c_mCurrentRecipe;};
    inline ObjectReference& mInventoryPotential() {return c_mInventoryPotential;};
    inline float& mPendingPotential() {return c_mPendingPotential;};
    inline float& mCurrentPotential() {return c_mCurrentPotential;};
    inline bool mIsProductionPaused() {return c_mIsProductionPaused;};

    inline std::vector<FactoryConnectionComponentSP>& inputs() {return c_inputs;};
    inline std::vector<FactoryConnectionComponentSP>& outputs() {return c_outputs;};
    inline InventoryComponentSP InputInventory() {return c_input_inventory;};
    inline InventoryComponentSP OutputInventory() {return c_output_inventory;};
    inline InventoryComponentSP InventoryPotential() {return c_inventory_potential;};

  private:
    //virtual void deserialize(Reader &_reader);
    float c_mCurrentManufacturingProgress, c_mPendingPotential, c_mCurrentPotential;
    ObjectReference c_mInputInventory, c_mCurrentRecipe, c_mOutputInventory, c_mInventoryPotential;
    bool c_mIsProductionPaused;

  protected:
    std::vector<FactoryConnectionComponentSP> c_inputs, c_outputs;
    InventoryComponentSP c_input_inventory, c_output_inventory, c_inventory_potential;
  };

  typedef std::shared_ptr<IOUnit> IOUnitSP;

}

#endif
