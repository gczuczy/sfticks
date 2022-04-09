
#ifndef SFT_FGPACKAGER_H
#define SFT_FGPACKAGER_H

#include "FGIOUnit.hh"

class FGPackager: public FGIOUnit {
public:
  FGPackager()=delete;
  FGPackager(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGPackager();

  static std::string objtypename;

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
