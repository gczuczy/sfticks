
#ifndef SFT_FGGENERATORNUCLEAR_H
#define SFT_FGGENERATORNUCLEAR_H

#include "FGGeneratorUnit.hh"

namespace FG {

  class GeneratorNuclear: public GeneratorUnit {
  public:
    GeneratorNuclear()=delete;
    GeneratorNuclear(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~GeneratorNuclear();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
