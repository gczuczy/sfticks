
#ifndef SFT_FGCONVEYORBELTMK3_H
#define SFT_FGCONVEYORBELTMK3_H

#include "FGConveyorBelt.hh"

class FGConveyorBeltMk3: public FGConveyorBelt {
public:
  FGConveyorBeltMk3()=delete;
  FGConveyorBeltMk3(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorBeltMk3();

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
