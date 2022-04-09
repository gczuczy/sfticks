
#ifndef SFT_FGCONVEYORLIFT_H
#define SFT_FGCONVEYORLIFT_H

#include "FGConveyorBelt.hh"
#include "ObjectReference.hh"
#include "Transform.hh"

#include <vector>

namespace FG {

  class ConveyorLift: public ConveyorBelt {
  public:
    ConveyorLift()=delete;
    ConveyorLift(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _throughput);
    virtual ~ConveyorLift();

    inline bool& mIsReversed() {return c_mIsReversed;};

  private:
    std::vector<ObjectReference> c_mSnappedPassthroughs;
    bool c_mIsReversed;
    Transform c_mTopTransform;
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
