
#ifndef SFT_FGHADRONCOLLIDER_H
#define SFT_FGHADRONCOLLIDER_H

#include "FGIOUnit.hh"

class FGHadronCollider: public FGIOUnit {
public:
  FGHadronCollider()=delete;
  FGHadronCollider(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGHadronCollider();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
