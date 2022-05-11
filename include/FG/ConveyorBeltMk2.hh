
#ifndef SFT_FGCONVEYORBELTMK2_H
#define SFT_FGCONVEYORBELTMK2_H

#include "FG/ConveyorBelt.hh"

namespace FG {

  class ConveyorBeltMk2: public ConveyorBelt {
  public:
    ConveyorBeltMk2()=delete;
    ConveyorBeltMk2(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorBeltMk2();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
