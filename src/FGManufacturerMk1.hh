
#ifndef SFT_FGMANUFACTURERMK1_H
#define SFT_FGMANUFACTURERMK1_H

#include "FGIOUnit.hh"

namespace FG {

  class ManufacturerMk1: public IOUnit {
  public:
    ManufacturerMk1()=delete;
    ManufacturerMk1(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ManufacturerMk1();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
