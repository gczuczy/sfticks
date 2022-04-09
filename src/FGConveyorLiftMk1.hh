
#ifndef SFT_FGCONVEYORLIFTMK1_H
#define SFT_FGCONVEYORLIFTMK1_H

#include "FGConveyorLift.hh"

namespace FG {

  class ConveyorLiftMk1: public ConveyorLift {
  public:
    ConveyorLiftMk1()=delete;
    ConveyorLiftMk1(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorLiftMk1();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
