
#ifndef SFT_FGCONVEYORBELTMK5_H
#define SFT_FGCONVEYORBELTMK5_H

#include "FGConveyorBelt.hh"

namespace FG {

  class ConveyorBeltMk5: public ConveyorBelt {
  public:
    ConveyorBeltMk5()=delete;
    ConveyorBeltMk5(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorBeltMk5();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
