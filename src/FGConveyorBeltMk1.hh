
#ifndef SFT_FGCONVEYORBELTMK1_H
#define SFT_FGCONVEYORBELTMK1_H

#include "FGConveyorBelt.hh"

class FGConveyorBeltMk1: public FGConveyorBelt {
public:
  FGConveyorBeltMk1()=delete;
  FGConveyorBeltMk1(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorBeltMk1();

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
