
#ifndef SFT_FGCONVEYORBELT_H
#define SFT_FGCONVEYORBELT_H

#include "FGBuilding.hh"
#include "FGComponent.hh"
#include "EnumProperty.hh"
#include "ObjectReference.hh"

class FGConveyorBelt: public FGBuilding {
public:
  // Component classes
  class ConveyorAny: public FGComponent {
  public:
    ConveyorAny() = delete;
    ConveyorAny(Reader& _reader, FGObjectHeader& _fgoh);
    virtual ~ConveyorAny()=default;
    static FGComponentSP instantiate(Reader& _reader, FGObjectHeader& _fgoh);

    inline EFactoryConnectionDirection mDirection() const {return c_mDirection;};
    inline ObjectReference mConnectedComponent() const {return c_mConnectedComponent;};

  private:
    EFactoryConnectionDirection c_mDirection;
    ObjectReference c_mConnectedComponent;
  };
public:
  FGConveyorBelt()=delete;
  FGConveyorBelt(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh, int32_t _throughput);
  virtual ~FGConveyorBelt();

  inline int32_t throughput() const {return c_throughput;};

private:
  int32_t c_throughput; // items per minute
  //virtual void deserialize(Reader &_reader);
};

typedef std::shared_ptr<FGConveyorBelt> FGConveyorBeltSP;

#endif
