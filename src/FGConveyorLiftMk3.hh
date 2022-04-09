
#ifndef SFT_FGCONVEYORLIFTMK3_H
#define SFT_FGCONVEYORLIFTMK3_H

#include "FGConveyorLift.hh"

namespace FG {

  class ConveyorLiftMk3: public ConveyorLift {
  public:
    ConveyorLiftMk3()=delete;
    ConveyorLiftMk3(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorLiftMk3();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
