
#ifndef SFT_FGMANUFACTURERMK1_H
#define SFT_FGMANUFACTURERMK1_H

#include "FG/IOUnit.hh"

namespace FG {

  class ManufacturerMk1: public IOUnit {
  public:
    ManufacturerMk1()=delete;
    ManufacturerMk1(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~ManufacturerMk1();

    virtual void doTick(SFT::tickinfo_t& _tick);

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
