
#ifndef SFT_SAVEABLE_H
#define SFT_SAVEABLE_H

#include "Reader.hh"

class Saveable {
public:
  Saveable();
  virtual ~Saveable()=0;

public:
  virtual void deserialize(Reader &_reader)=0;
};

#endif
