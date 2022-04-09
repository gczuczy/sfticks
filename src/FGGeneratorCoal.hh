
#ifndef SFT_FGGENERATORCOAL_H
#define SFT_FGGENERATORCOAL_H

#include "FGGeneratorUnit.hh"

class FGGeneratorCoal: public FGGeneratorUnit {
public:
  FGGeneratorCoal()=delete;
  FGGeneratorCoal(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGGeneratorCoal();

  inline float& mCurrentSupplementalAmount() {return c_mCurrentSupplementalAmount;};
  inline bool& mHasSupplementalCached() {return c_mHasSupplementalCached;};

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
  float c_mCurrentSupplementalAmount;
  bool c_mHasSupplementalCached;
};

#endif
