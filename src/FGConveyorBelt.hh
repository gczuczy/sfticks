
#ifndef SFT_FGCONVEYORBELT_H
#define SFT_FGCONVEYORBELT_H

#include "FGBuilding.hh"
#include "FGComponent.hh"

class FGConveyorBelt: public FGBuilding {
public:
  // Component classes
  class ConveyorAny: public FGComponent {
  public:
    ConveyorAny() = delete;
    ConveyorAny(Reader& _reader, FGObjectHeader& _fgoh);
    virtual ~ConveyorAny()=default;
    static FGComponentSP instantiate(Reader& _reader, FGObjectHeader& _fgoh);

  private:
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
