
#ifndef SFT_FGCONVEYORBELTMK3_H
#define SFT_FGCONVEYORBELTMK3_H

#include "FG/ConveyorBelt.hh"

namespace FG {

  class ConveyorBeltMk3: public ConveyorBelt {
  public:
    ConveyorBeltMk3()=delete;
    ConveyorBeltMk3(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ConveyorBeltMk3();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
