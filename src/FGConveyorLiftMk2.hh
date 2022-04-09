
#ifndef SFT_FGCONVEYORLIFTMK2_H
#define SFT_FGCONVEYORLIFTMK2_H

#include "FGConveyorLift.hh"

class FGConveyorLiftMk2: public FGConveyorLift {
public:
  FGConveyorLiftMk2()=delete;
  FGConveyorLiftMk2(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGConveyorLiftMk2();

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
