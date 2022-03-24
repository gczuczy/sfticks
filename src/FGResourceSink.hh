
#ifndef SFT_FGRESOURCESINK_H
#define SFT_FGRESOURCESINK_H

#include "FGIOUnit.hh"

class FGResourceSink: public FGIOUnit {
public:
  FGResourceSink()=delete;
  FGResourceSink(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGResourceSink();

private:
  //virtual void deserialize(Reader &_reader);
};

#endif
