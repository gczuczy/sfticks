
#ifndef SFT_FGOilRefinery_H
#define SFT_FGOilRefinery_H

#include "FGIOUnit.hh"

namespace FG {

  class OilRefinery: public IOUnit {
  public:
    OilRefinery()=delete;
    OilRefinery(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~OilRefinery();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
