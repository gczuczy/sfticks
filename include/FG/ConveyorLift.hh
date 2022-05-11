
#ifndef SFT_FGCONVEYORLIFT_H
#define SFT_FGCONVEYORLIFT_H

#include "FG/ConveyorBelt.hh"
#include "FG/ObjectReference.hh"
#include "FG/Transform.hh"

#include <vector>

namespace FG {

  class ConveyorLift: public ConveyorBelt {
  public:
    ConveyorLift()=delete;
    ConveyorLift(EntityType _et, Reader& _reader, ObjectHeader& _fgoh, int32_t _throughput);
    virtual ~ConveyorLift();

    inline bool isReversed() {return c_mIsReversed;};
    inline Transform topTransform() {return c_mTopTransform;};
    inline std::vector<ObjectReference>& snappedPassthroughs() {return c_mSnappedPassthroughs;};

    virtual float length();

  private:
    std::vector<ObjectReference> c_mSnappedPassthroughs;
    bool c_mIsReversed;
    Transform c_mTopTransform;
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
