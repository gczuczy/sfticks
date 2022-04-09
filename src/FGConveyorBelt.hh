
#ifndef SFT_FGCONVEYORBELT_H
#define SFT_FGCONVEYORBELT_H

#include "FGBuilding.hh"

namespace FG {

  class ConveyorBelt: public Building {
  public:
    ConveyorBelt()=delete;
    ConveyorBelt(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _throughput);
    virtual ~ConveyorBelt();

    inline int32_t throughput() const {return c_throughput;};

  private:
    int32_t c_throughput; // items per minute
    //virtual void deserialize(Reader &_reader);
  };

  typedef std::shared_ptr<ConveyorBelt> ConveyorBeltSP;

}

#endif
