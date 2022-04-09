
#ifndef SFT_FGCONVEYORBELTMK1_H
#define SFT_FGCONVEYORBELTMK1_H

#include "FGConveyorBelt.hh"

namespace FG {

  class ConveyorBeltMk1: public ConveyorBelt {
  public:
    ConveyorBeltMk1()=delete;
    ConveyorBeltMk1(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorBeltMk1();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
