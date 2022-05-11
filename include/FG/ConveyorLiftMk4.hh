
#ifndef SFT_FGCONVEYORLIFTMK4_H
#define SFT_FGCONVEYORLIFTMK4_H

#include "FG/ConveyorLift.hh"

namespace FG {

  class ConveyorLiftMk4: public ConveyorLift {
  public:
    ConveyorLiftMk4()=delete;
    ConveyorLiftMk4(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorLiftMk4();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
