
#ifndef SFT_FGCONVEYORLIFTMK5_H
#define SFT_FGCONVEYORLIFTMK5_H

#include "FG/ConveyorLift.hh"

namespace FG {

  class ConveyorLiftMk5: public ConveyorLift {
  public:
    ConveyorLiftMk5()=delete;
    ConveyorLiftMk5(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorLiftMk5();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
