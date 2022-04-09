
#ifndef SFT_FGCONVEYORBELTMK4_H
#define SFT_FGCONVEYORBELTMK4_H

#include "FGConveyorBelt.hh"

namespace FG {

  class ConveyorBeltMk4: public ConveyorBelt {
  public:
    ConveyorBeltMk4()=delete;
    ConveyorBeltMk4(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorBeltMk4();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
