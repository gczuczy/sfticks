
#ifndef SFT_FGBLENDER_H
#define SFT_FGBLENDER_H

#include "FGIOUnit.hh"

class FGBlender: public FGIOUnit {
public:
  FGBlender()=delete;
  FGBlender(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGBlender();

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
