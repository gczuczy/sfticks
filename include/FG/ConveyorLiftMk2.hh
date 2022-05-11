
#ifndef SFT_FGCONVEYORLIFTMK2_H
#define SFT_FGCONVEYORLIFTMK2_H

#include "FG/ConveyorLift.hh"

namespace FG {

  class ConveyorLiftMk2: public ConveyorLift {
  public:
    ConveyorLiftMk2()=delete;
    ConveyorLiftMk2(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorLiftMk2();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
