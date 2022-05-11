
#ifndef SFT_FGGENERATORFUEL_H
#define SFT_FGGENERATORFUEL_H

#include "FG/GeneratorUnit.hh"

namespace FG {

  class GeneratorFuel: public GeneratorUnit {
  public:
    GeneratorFuel()=delete;
    GeneratorFuel(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~GeneratorFuel();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
