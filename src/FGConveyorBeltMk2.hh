
#ifndef SFT_FGCONVEYORBELTMK2_H
#define SFT_FGCONVEYORBELTMK2_H

#include "FGConveyorBelt.hh"

class FGConveyorBeltMk2: public FGConveyorBelt {
public:
  FGConveyorBeltMk2()=delete;
  FGConveyorBeltMk2(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorBeltMk2();

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
